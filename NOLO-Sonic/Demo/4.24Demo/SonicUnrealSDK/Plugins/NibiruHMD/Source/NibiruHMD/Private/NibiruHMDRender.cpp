/* Copyright 2016 Nibiru Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "NibiruHMD.h"
#include "NibiruHMDPrivatePCH.h"
#include "ScreenRendering.h"
#if NIBIRUVRHMD_SUPPORTED_ANDROID_PLATFORMS
 #include "OpenGLDrvPrivate.h"
 #include "OpenGLResources.h"
#endif

#if ENGINE_MINOR_VERSION > 22
void FNibiruHMD::RenderTexture_RenderThread(FRHICommandListImmediate& RHICmdList, FRHITexture2D* BackBuffer, FRHITexture2D* SrcTexture, FVector2D WindowSize) const
#else
void FNibiruHMD::RenderTexture_RenderThread(FRHICommandListImmediate& RHICmdList, FTexture2DRHIParamRef BackBuffer, FTexture2DRHIParamRef SrcTexture, FVector2D WindowSize) const
#endif
{
	check(IsInRenderingThread());

	const uint32 ViewportWidth = BackBuffer->GetSizeX();
	const uint32 ViewportHeight = BackBuffer->GetSizeY();
	const uint32 TextureWidth = SrcTexture->GetSizeX();
	const uint32 TextureHeight = SrcTexture->GetSizeY();

	int* texture_id = reinterpret_cast<int*>(SrcTexture->GetNativeResource());
	// RenderTexture_RenderThread() Viewport:(1920, 1080) Texture:(2048, 1024)
#ifdef DEBUG_LOG_ENABLE
	UE_LOG(LogHMD, Log, TEXT("RenderTexture_RenderThread() Viewport:(%d, %d) Texture:(%d, %d) BackBuffer=%p SrcTexture=%p [TextureId %d] Window:(%f, %f)"), 
		ViewportWidth, ViewportHeight, TextureWidth, TextureHeight, BackBuffer, SrcTexture , *texture_id, WindowSize.X, WindowSize.Y);
#endif

#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	// When using distortion method in NVR SDK
	if (useDTRMode)
	{
		// Use native nvr distortion without async reprojection
		// Note that this method is not enabled by default.
	 
		//When use aysnc reprojection, the framebuffer submit is handled in CustomPresent->FinishRendering
		return;
	}
	else
#endif // NIBIRUVRHMD_SUPPORTED_PLATFORMS
		// Just render directly to output
	{
		FGraphicsPipelineStateInitializer GraphicsPSOInit;
		GraphicsPSOInit.BlendState = TStaticBlendState<>::GetRHI();
		GraphicsPSOInit.RasterizerState = TStaticRasterizerState<>::GetRHI();
		GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();

		FRHIRenderPassInfo RPInfo(BackBuffer, ERenderTargetActions::Load_Store);
		RHICmdList.BeginRenderPass(RPInfo, TEXT("NibiruVRHMD_RenderTexture"));
		{
			RHICmdList.ApplyCachedRenderTargets(GraphicsPSOInit);

			RHICmdList.SetViewport(0, 0, 0, ViewportWidth, ViewportHeight, 1.0f);

			const auto FeatureLevel = GMaxRHIFeatureLevel;
			auto ShaderMap = GetGlobalShaderMap(FeatureLevel);

			TShaderMapRef<FScreenVS> VertexShader(ShaderMap);
			TShaderMapRef<FScreenPS> PixelShader(ShaderMap);

			GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = GFilterVertexDeclaration.VertexDeclarationRHI;
#if ENGINE_MINOR_VERSION >= 25
			GraphicsPSOInit.BoundShaderState.VertexShaderRHI = VertexShader.GetVertexShader();
			GraphicsPSOInit.BoundShaderState.PixelShaderRHI = PixelShader.GetPixelShader();
#else
			GraphicsPSOInit.BoundShaderState.VertexShaderRHI = GETSAFERHISHADER_VERTEX(*VertexShader);
			GraphicsPSOInit.BoundShaderState.PixelShaderRHI = GETSAFERHISHADER_PIXEL(*PixelShader);
#endif
			GraphicsPSOInit.PrimitiveType = PT_TriangleList;

			SetGraphicsPipelineState(RHICmdList, GraphicsPSOInit);

			PixelShader->SetParameters(RHICmdList, TStaticSamplerState<SF_Bilinear>::GetRHI(), SrcTexture);

#if ENGINE_MINOR_VERSION >= 25
			RendererModule->DrawRectangle(
				RHICmdList,
				0, 0,
				ViewportWidth, ViewportHeight,
				0.0f, 0.0f,
				1.0f, 1.0f,
				FIntPoint(ViewportWidth, ViewportHeight),
				FIntPoint(1, 1),
				VertexShader,
				EDRF_Default);
#else
			RendererModule->DrawRectangle(
				RHICmdList,
				0, 0,
				ViewportWidth, ViewportHeight,
				0.0f, 0.0f,
				1.0f, 1.0f,
				FIntPoint(ViewportWidth, ViewportHeight),
				FIntPoint(1, 1),
				*VertexShader,
				EDRF_Default);
#endif
		}
		RHICmdList.EndRenderPass();
	}
}
 
FXRRenderBridge* FNibiruHMD::GetActiveRenderBridge_GameThread(bool /* bUseSeparateRenderTarget */)
{
	check(IsInGameThread());
#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	if (useDTRMode)
	{
		return CustomPresent;
	}
#endif // NIBIRUVRHMD_SUPPORTED_PLATFORMS
	return nullptr;
}

bool FNibiruHMD::AllocateRenderTargetTexture(uint32 Index, uint32 SizeX, uint32 SizeY, uint8 Format, uint32 NumMips, uint32 InFlags, uint32 TargetableTextureFlags, FTexture2DRHIRef& OutTargetableTexture, FTexture2DRHIRef& OutShaderResourceTexture, uint32 NumSamples)
{
	//-AllocateRenderTargetTexture: Index[0] Size[2048,1024]
	// UE_LOG(LogHMD, Log, TEXT("AllocateRenderTargetTexture Begin ,  Index[%d] ,Size[%d,%d]"), Index, SizeX, SizeY);
	check(Index == 0);
	check(SizeX != 0 && SizeY != 0);
	check(IsInGameThread() && IsInRenderingThread()); // checking if rendering thread is suspended

#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	if (CustomPresent)
	{   
		bool Success = static_cast<FNibiruVRHMDCustomPresent*>(CustomPresent)->AllocateRenderTargetTexture(Index, SizeX, SizeY, Format, NumMips, InFlags, TargetableTextureFlags, OutTargetableTexture, OutShaderResourceTexture, NumSamples);
		return Success;
	} else {
		UE_LOG(LogHMD, Error, TEXT("AllocateRenderTargetTexture Failed , CustomPresent is NULL , Index[%d] ,Size[%d,%d]"), Index, SizeX, SizeY);
	}
#endif

	return false;
}


#if NIBIRUVRHMD_SUPPORTED_PLATFORMS

FNibiruVRHMDTexture2DSet::FNibiruVRHMDTexture2DSet(
	class FOpenGLDynamicRHI* InGLRHI,
	GLenum InTarget,
	GLenum InAttachment,
	uint32 InSizeX,
	uint32 InSizeY,
	uint32 InSizeZ,
	uint32 InNumMips,
	uint32 InNumSamples,
	uint32 InNumSamplesTileMem,
	uint32 InArraySize,
	EPixelFormat InFormat,
	bool bInCubemap,
	bool bInAllocatedStorage,
	uint32 InFlags,
	uint8* InTextureRange,
	uint32 InTargetableTextureFlags
) : FOpenGLTexture2D(
	InGLRHI,
	0,
	InTarget,
	InAttachment,
	InSizeX,
	InSizeY,
	InSizeZ,
	InNumMips,
	InNumSamples,
	InNumSamplesTileMem,
	InArraySize,
	InFormat,
	bInCubemap,
	bInAllocatedStorage,
	InFlags,
	InTextureRange,
	FClearValueBinding::Black)
{
	FRHIResourceCreateInfo CreateInfo;
	bool bArrayTexture = (InArraySize > 1);
	int ids[mkRenderTargetTextureNum];

	for (int i = 0; i < mkRenderTargetTextureNum; ++i)
	{
		GLuint TextureID = 0;
		FOpenGL::GenTextures(1, &TextureID);

		const bool bSRGB = (InTargetableTextureFlags & TexCreate_SRGB) != 0;
		const FOpenGLTextureFormat& GLFormat = GOpenGLTextureFormats[InFormat];
		if (GLFormat.InternalFormat[bSRGB] == GL_NONE)
		{
			UE_LOG(LogHMD, Fatal, TEXT("Nvr_UE Texture format '%s' not supported (sRGB=%d)."), GPixelFormats[InFormat].Name, bSRGB);
		}

		FOpenGLContextState& ContextState = InGLRHI->GetContextStateForCurrentContext();

		// Make sure PBO is disabled
		InGLRHI->CachedBindPixelUnpackBuffer(ContextState, 0);

		// Use a texture stage that's not likely to be used for draws, to avoid waiting
		InGLRHI->CachedSetupTextureStage(ContextState, FOpenGL::GetMaxCombinedTextureImageUnits() - 1, InTarget, TextureID, 0, 1);

		if (bArrayTexture)
		{
			UE_LOG(LogHMD, Log, TEXT("FOpenGL::TexStorage3D"));
			FOpenGL::TexStorage3D(InTarget, 1, GLFormat.InternalFormat[bSRGB], InSizeX, InSizeY, InArraySize, GLFormat.Format, GLFormat.Type);
			mRenderTargetTextureRHIRef[i] = InGLRHI->RHICreateTexture2DArrayFromResource((EPixelFormat)InFormat, InSizeX, InSizeY, InArraySize, InNumMips, InNumSamples, InNumSamplesTileMem, FClearValueBinding::Black, TextureID, InTargetableTextureFlags);
		
		}
		else //if (!FOpenGL::TexStorage2D(InTarget, 1, GLFormat.SizedInternalFormat[bSRGB], InSizeX, InSizeY, GLFormat.Format, GLFormat.Type, InTargetableTextureFlags))
		{
			//glTexImage2D(InTarget, 0, GLFormat.InternalFormat[bSRGB], InSizeX, InSizeY, 0, GLFormat.Format, GLFormat.Type, NULL);
			mRenderTargetTextureRHIRef[i] = InGLRHI->RHICreateTexture2D(InSizeX, InSizeY, (EPixelFormat)InFormat, InNumMips, InNumSamples, InTargetableTextureFlags, CreateInfo);
		}
		ids[i] = *(GLuint*)mRenderTargetTextureRHIRef[i]->GetNativeResource();
		UE_LOG(LogHMD, Log, TEXT("Index.%d, GenTextures.%d, RealTextureId.%d, Format.%d, InNumMips.%d, InNumSamples.%d, Flags.%d)."),
			i, TextureID, ids[i], (EPixelFormat)InFormat, InNumMips, InNumSamples, InTargetableTextureFlags);
	}

	// notify sdk that textures has gen success
	NibiruImport::NibiruCreateTextures(ids);

	mRenderTargetTextureRHIRefIndex = 0;
	SetIndexAsCurrentRenderTarget();
}

FNibiruVRHMDTexture2DSet* FNibiruVRHMDTexture2DSet::CreateTexture2DSet(
	FOpenGLDynamicRHI* InGLRHI,
	GLenum InTarget,
	uint32 SizeX,
	uint32 SizeY,
	uint32 InNumSamples,
	uint32 InNumSamplesTileMem,
	uint32 InArraySize,
	EPixelFormat InFormat,
	uint32 InFlags,
	uint32 InTargetableTextureFlags,
	FTexture2DRHIRef& OutTargetableTexture,
	FTexture2DRHIRef& OutShaderResourceTexture)
{
	FNibiruVRHMDTexture2DSet* TextureSetProxy = new FNibiruVRHMDTexture2DSet(InGLRHI, InTarget, GL_NONE, SizeX, SizeY, 0, 1, InNumSamples, InNumSamplesTileMem, InArraySize, InFormat, false, false, InFlags, nullptr, InTargetableTextureFlags);
	OutTargetableTexture = OutShaderResourceTexture = TextureSetProxy->GetTexture2D();
	return TextureSetProxy;
}

FNibiruVRHMDTexture2DSet::~FNibiruVRHMDTexture2DSet()
{
	this->SetMemorySize(0);
}

void FNibiruVRHMDTexture2DSet::SwitchToNextElement()
{
	mRenderTargetTextureRHIRefIndex = ((mRenderTargetTextureRHIRefIndex + 1) % mkRenderTargetTextureNum);
	SetIndexAsCurrentRenderTarget();
}

void FNibiruVRHMDTexture2DSet::SetIndexAsCurrentRenderTarget()
{
	Resource = GetRenderTargetResource();
	// UE_LOG(LogHMD, Log, TEXT("SetIndexAsCurrentRenderTarget: Index.%d,TextureId.%d"), mRenderTargetTextureRHIRefIndex, Resource);
}

GLuint FNibiruVRHMDTexture2DSet::GetRenderTargetResource()
{
	return *(GLuint*)mRenderTargetTextureRHIRef[mRenderTargetTextureRHIRefIndex]->GetNativeResource();
}

FNibiruVRHMDCustomPresent::FNibiruVRHMDCustomPresent(FNibiruHMD* InHMD)
	: FXRRenderBridge()
	, CurrentFrame(nullptr)
	, HMD(InHMD)
	, CurrentFrameViewportList(nullptr)
	, bUsesArrayTexture(false)
{
	UE_LOG(LogHMD, Log, TEXT("chao::FNibiruVRHMDCustomPresent-init"));
	// set to identity
	CurrentFrameRenderHeadPose =	{ { { 1.0f, 0.0f, 0.0f, 0.0f },
									{ 0.0f, 1.0f, 0.0f, 0.0f },
									{ 0.0f, 0.0f, 1.0f, 0.0f },
									{ 0.0f, 0.0f, 0.0f, 1.0f } } };

}

FNibiruVRHMDCustomPresent::~FNibiruVRHMDCustomPresent()
{ 
	Shutdown();
}

void FNibiruVRHMDCustomPresent::Shutdown()
{ 
	UE_LOG(LogHMD, Log, TEXT("chao::FNibiruVRHMDCustomPresent-Shutdown"));
}

bool FNibiruVRHMDCustomPresent::AllocateRenderTargetTexture(uint32 Index, uint32 SizeX, uint32 SizeY, uint8 Format, uint32 NumMips, uint32 InFlags, uint32 TargetableTextureFlags, FTexture2DRHIRef& OutTargetableTexture, FTexture2DRHIRef& OutShaderResourceTexture, uint32 NumSamples)
{
	//FNibiruVRHMDTexture2DSet of size (2048, 1024), NewTextureSet [0x8cf290e0]
	UE_LOG(LogHMD, Log, TEXT("chao::FNibiruVRHMDCustomPresent-AllocateRenderTargetTexture: Format[%d] Index[%d] Size[%d,%d]"), Format, Index,SizeX,SizeY);

	FOpenGLDynamicRHI* OpenGLDynamicRHI = static_cast<FOpenGLDynamicRHI*>(GDynamicRHI);

	static const int32 MaxMSAALevelSupported = FOpenGL::GetMaxMSAASamplesTileMem();
	static const int32 MSAASettingLevel = IConsoleManager::Get().FindTConsoleVariableDataInt(TEXT("r.MobileMSAA"))->GetValueOnAnyThread();
	static const int32 MobileMSAAValue = FMath::Min(MSAASettingLevel, MaxMSAALevelSupported);

	GLenum Target = GL_TEXTURE_2D;
	uint32 Layers = 1;
	if (bUsesArrayTexture)
	{
		Target = GL_TEXTURE_2D_ARRAY;
		Layers = 2;
	}

	//Allocate the RenderTarget Textures
	uint32 textureWidth = SizeX; // 除2=single eye size * single eye size * 4  [720*720*4]
	uint32 textureHeight = SizeY;
	int useSmallTexture = NibiruImport::NibiruGetIntValue("small_texture_size", 0);
	if (useSmallTexture == 1) {
		textureWidth = textureWidth / 2;
	}
	
	UE_LOG(LogHMD, Log, TEXT("Created FNibiruVRHMDTexture2DSet of size (%d, %d) MSAA (%d)"), textureWidth, SizeY, MobileMSAAValue);

	mTextureSet = TRefCountPtr<FNibiruVRHMDTexture2DSet>(FNibiruVRHMDTexture2DSet::CreateTexture2DSet(OpenGLDynamicRHI, Target, textureWidth, SizeY, NumSamples, MobileMSAAValue, Layers, EPixelFormat(Format), InFlags, TargetableTextureFlags, OutTargetableTexture, OutShaderResourceTexture));

	if (!mTextureSet.IsValid())
	{
		UE_LOG(LogHMD, Log, TEXT("Created FNibiruVRHMDTexture2DSet Failed, mTextureSet Is InValid !!!"));
		return false;
	}

	// NVR_GL_CHECK("AllocateRenderTargetTexture");
	return true;
}

void FNibiruVRHMDCustomPresent::BeginRendering(uint32 frameNum, const nvr_mat4f& RenderingHeadPose)
{
    NibiruImport::NibiruSetIntValue(NIB_KEY_BEGIN_FRAME_NUM,(int)frameNum);
    // Cache the render headpose we use for this frame
    CurrentFrameRenderHeadPose = RenderingHeadPose;
}

void FNibiruVRHMDCustomPresent::FinishRendering()
{
	check(IsInRenderingThread());

    if (HMD && mTextureSet) {
		auto RTTextureId = mTextureSet->GetRenderTargetResource();
        //UE_LOG(LogHMD, Log, TEXT("chao::FinishRendering TextureSet.%d"), TexId);
 
        // TEST
        // API returns framebuffer resource, but we need the texture resource for the pipeline
		//check(PLATFORM_USES_ES2); // Some craziness will only work on OpenGL platforms.
		//GLint TextureId = 0;
		//glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &TextureId);
		//override the texture set in custom present to the texture id we just bind so that unreal could render to it.
		//UE_LOG(LogHMD, Log, TEXT("chao::FinishRendering Currently FBO .%d"), TextureId);
        // TEST

        // 把cache的headpose传递给SDK
        NibiruImport::NibiruSetTexture(reinterpret_cast<void*> (RTTextureId), HMD->GetViewNum());
 
		mTextureSet->SwitchToNextElement();

		HMD->bBeginFrame = false;

#ifdef DEBUG_LOG_ENABLE
		UE_LOG(LogHMD, Log, TEXT("FNibiruVRHMDCustomPresent::FinishRendering %d"), backBufferTextureId);
#endif

    }else if(!mTextureSet) {
        UE_LOG(LogHMD, Log, TEXT("chao::FinishRendering TextureSet is NULL"));
    }
}

bool FNibiruVRHMDCustomPresent::NeedsNativePresent()
{
	//D3D12 only now, not mobile.
	return false;
}

bool FNibiruVRHMDCustomPresent::Present(int32& InOutSyncInterval)
{
	FinishRendering();
	// Note: true causes normal swapbuffers(), false prevents normal swapbuffers()
 
    if(HMD)
    {
    	HMD->UpdateNibiruHeadPose();
    }

	// true=>SwapBuffers
	// false=>do nothing

	// NVR_GL_CHECK("Present");
#ifdef DEBUG_LOG_ENABLE
	UE_LOG(LogHMD, Log, TEXT("FNibiruVRHMDCustomPresent::Present"));
#endif
	return false;
 
}

void FNibiruVRHMDCustomPresent::OnBackBufferResize()
{
	UE_LOG(LogHMD, Log, TEXT("chao::OnBackBufferResize"));
}

void FNibiruVRHMDCustomPresent::EnterVRMode_RenderThread() 
{
	check(IsInRenderingThread());
	nvrModeParms parms; 
	parms.Display = (size_t)AndroidEGL::GetInstance()->GetDisplay();
	parms.WindowSurface = (size_t)AndroidEGL::GetInstance()->GetNativeWindow();
	parms.ShareContext = (size_t)AndroidEGL::GetInstance()->GetRenderingContext()->eglContext;
	NibiruImport::NibiruEnterVRMode(&parms);
	UE_LOG(LogHMD, Log, TEXT("EnterVRMode_RenderThread.GUseThreadedRendering=%d"), GUseThreadedRendering);
}

void FNibiruVRHMDCustomPresent::LeaveVRMode_RenderThread() 
{
	check(IsInRenderingThread());
	NibiruImport::NibiruLeaveVRMode();
	UE_LOG(LogHMD, Log, TEXT("LeaveVRMode_RenderThread"));
}

#endif // NIBIRUVRHMD_SUPPORTED_PLATFORMS