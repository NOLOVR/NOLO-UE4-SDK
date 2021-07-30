
#include "NibiruHMD.h"
#if WITH_EDITOR
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#endif
#if NIBIRUVRHMD_SUPPORTED_ANDROID_PLATFORMS
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#endif // NIBIRUVRHMD_SUPPORTED_ANDROID_PLATFORMS


#define pprint(text) { if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::White, text); }
#define perror(text) { if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Red, text); }
#define pinfo(text)  { if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 11.5f, FColor::Yellow, text); }

#define LOCTEXT_NAMESPACE "FNibiruHMDPlugin"

//---------------------------------------------------
// NibiruHMD Plugin Implementation
//---------------------------------------------------

// Only one HMD can be active at a time, so using file static to track this for transferring to game thread
static bool bBackDetected = false;
static bool bTriggerDetected = false;
static double BackbuttonPressTime;
static double PluginStartTime;

// 2s内禁止退出
static const double PLUGIN_EXIT_INTERVAL_TIME_MS = 2.0f;
static const double BACK_BUTTON_SHORT_PRESS_TIME = 1.0f;
void OnTriggerEvent(void* UserParam)
{
	UE_LOG(LogHMD, Log, TEXT("Trigger event detected"));

	bTriggerDetected = true;
}

#if NIBIRUVRHMD_SUPPORTED_ANDROID_PLATFORMS

// Note: Should probably be moved into AndroidJNI class
int64 CallLongMethod(JNIEnv* Env, jobject Object, jmethodID Method, ...)
{
	if (Method == NULL || Object == NULL)
	{
		return false;
	}

	va_list Args;
	va_start(Args, Method);
	jlong Return = Env->CallLongMethodV(Object, Method, Args);
	va_end(Args);

	return (int64)Return;
}

int AndroidThunkCpp_GetVerifyStatus()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv()) 
	{
		return FJavaWrapper::CallIntMethod(Env, FJavaWrapper::GameActivityThis,
				FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_GetVerifyStatus", "()I", false));
	}
	return -1;
}

long AndroidThunkCpp_GetNativeNVRApi()
{
	PluginStartTime = FPlatformTime::Seconds();
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_GetNativeNVRApi", "()J", false);
		return CallLongMethod(Env, FJavaWrapper::GameActivityThis, Method);
	}
	return 0;
}

bool AndroidThunkCpp_GetNativeISSupportDTR() {
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_GetNativeIsSupportDTR", "()Z", false);
		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, Method);
	}

	return false;
}

bool AndroidThunkCpp_GetNativeISDTR()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_GetNativeISDTR", "()Z", false);
		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, Method);
	}
	return false;
}
 
bool AndroidThunkCpp_GetNativeISDFT() {
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_GetNativeISDFT", "()Z", false);
		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, Method);
	}

	return false;
}

bool AndroidThunkCpp_GetNativeISDISTORTION() {
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_GetNativeISDISTORTION", "()Z", false);
		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, Method);
	}
	return false;
}

bool AndroidThunkCpp_GetIsInteractionSDKEnabled() {
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_GetIsInteractionSDKEnabled", "()Z", false);
		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, Method);
	}
	return false;
}

void AndroidThunkCpp_Quit() {
	double DiffS = FPlatformTime::Seconds() - PluginStartTime;
	if(DiffS < PLUGIN_EXIT_INTERVAL_TIME_MS) {
		UE_LOG(LogHMD, Log, TEXT("FNibiruHMD::AndroidThunkCpp_Quit Failed, %d MS < 2 S"), (int)DiffS);
		return;
	}
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_Quit", "()V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method);
	} 
}

#endif

class FNibiruHMDPlugin : public INibiruHMDPlugin
{
	virtual void StartupModule() override
	{
		IHeadMountedDisplayModule::StartupModule();
#if WITH_EDITOR
		// register settings
		ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>(FName("Settings"));

		if (SettingsModule != nullptr)
		{
			ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "NibiruHMD",
				LOCTEXT("NXRSDKSettingsName", "NibiruHMD"),
				LOCTEXT("NXRSDKSettingsDescription", "Configure the NXR SDK plug-in."),
				GetMutableDefault<UNXRSDKSettings>()
			);
		}
#endif // WITH_EDITOR
	}

	virtual void ShutdownModule() override
	{
		IHeadMountedDisplayModule::ShutdownModule();
#if WITH_EDITOR
		// unregister settings
		ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

		if (SettingsModule != nullptr)
		{
			SettingsModule->UnregisterSettings("Project", "Plugins", "NibiruHMD");
		}
#endif

	}

    /**
	* Always return true for NibiruHMD, when enabled, to allow HMD Priority to sort it out
	*/
	virtual bool IsHMDConnected() { return true; }
	
	/** IHeadMountedDisplayModule implementation */
	virtual TSharedPtr< class IXRTrackingSystem, ESPMode::ThreadSafe > CreateTrackingSystem() override;

	virtual FString GetModuleKeyName() const override
	{
		return FString(TEXT("NibiruHMD"));
	}
};

IMPLEMENT_MODULE(FNibiruHMDPlugin, NibiruHMD)

TSharedPtr< class IXRTrackingSystem, ESPMode::ThreadSafe > FNibiruHMDPlugin::CreateTrackingSystem()
{
	TSharedPtr< FNibiruHMD, ESPMode::ThreadSafe >  HMD = FSceneViewExtensions::NewExtension<FNibiruHMD>();
	if (HMD->IsInitialized())
	{
		return HMD;
	}
	return nullptr;
}


//---------------------------------------------------
// NibiruHMD IHeadMountedDisplay Implementation
//---------------------------------------------------
// ------  Called on Game Thread ------
bool FNibiruHMD::GetHMDDistortionEnabled(EShadingPath ShadingPath) const
{
#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	// Enable Unreal PostProcessing Distortion when not using NVR Distortion.
	bool enabled = !IsUsingNVRApiDistortionCorrection() && ShadingPath == EShadingPath::Mobile;
    // UE_LOG(LogHMD, Log, TEXT("FNibiruHMD::GetHMDDistortionEnabled=%d,%d"), enabled, (int) ShadingPath);
	return enabled;
#else
	return false;
#endif
}

bool FNibiruHMD::IsHMDEnabled() const
{
	return true;
}

void FNibiruHMD::EnableHMD(bool enable)
{
	EnableStereo(true);
}

bool FNibiruHMD::GetHMDMonitorInfo(MonitorInfo& MonitorDesc)
{
	if (!IsStereoEnabled())
	{
		return false;
	}

	#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	MonitorDesc.MonitorName = "NibiruHMDPlatform";
	MonitorDesc.MonitorId = 0;
	MonitorDesc.DesktopX = MonitorDesc.DesktopY = MonitorDesc.ResolutionX = MonitorDesc.ResolutionY = 0;
	MonitorDesc.WindowSizeX = MonitorDesc.WindowSizeY = 0;
	FPlatformRect Rect = FAndroidWindow::GetScreenRect();
	MonitorDesc.ResolutionX = Rect.Right - Rect.Left;
	MonitorDesc.ResolutionY = Rect.Bottom - Rect.Top;
	return true;
	#else
    MonitorDesc.MonitorName = "UnsupportedHMDPlatform";
	MonitorDesc.MonitorId = 0;
	MonitorDesc.DesktopX = MonitorDesc.DesktopY = MonitorDesc.ResolutionX = MonitorDesc.ResolutionY = 0;
	MonitorDesc.WindowSizeX = MonitorDesc.WindowSizeY = 0;
	#endif
	return false;
}

void FNibiruHMD::GetFieldOfView(float& OutHFOVInDegrees, float& OutVFOVInDegrees) const
{
	UE_LOG(LogHMD, Log, TEXT("FNibiruHMD::GetFieldOfView [0,0"));
	OutHFOVInDegrees = 0.0f;
	OutVFOVInDegrees = 0.0f;
}

ESixDofMode FNibiruHMD::GetSixDofMode()
{
	return SixDofMode;
}

bool FNibiruHMD::DoesSupportPositionalTracking() const
{
	if (!IsSpt6DofDataApi)
	{
		return false;
	}
	bool IsSupportPositionalTracking = SixDofMode != ESixDofMode::Head_3DOF_Ctrl_3DOF;
	return IsSupportPositionalTracking;
}

//  
void FNibiruHMD::SetInterpupillaryDistance(float NewInterpupillaryDistance)
{
	// Nothing
}

//  
float FNibiruHMD::GetInterpupillaryDistance() const
{
 
#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	// For simplicity, the interpupillary distance is the distance to the left eye, doubled.
  
	return profileData[7];
#else //!NIBIRUVRHMD_SUPPORTED_PLATFORMS
	return 0.064f;
#endif
}

bool FNibiruHMD::GetCurrentPose(int32 DeviceId, FQuat& CurrentOrientation, FVector& CurrentPosition)
{
	if (DeviceId != HMDDeviceId)
	{
		return false;
	}
	

#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	// Update camera pose using cached head pose which we updated at the beginning of a frame.
	CurrentOrientation = BaseOrientation * CachedFinalHeadRotation;
	// Really need head 6dof, use the position data
	bool IsHead6Dof = SixDofMode == ESixDofMode::Head_6DOF_Ctrl_6DOF;
	CurrentPosition = BaseOrientation.RotateVector(IsHead6Dof ? CachedFinalHeadPosition : FVector::ZeroVector);
	if (FMath::Abs(CurrentPosition.X)>100.0f || FMath::Abs(CurrentPosition.Y) > 100.0f) {
		
		CurrentPosition = FVector::ZeroVector;
	}
	
#ifdef DEBUG_LOG_ENABLE
	UE_LOG(LogHMD, Log, TEXT("[F]--------------FNibiruHMD::GetCurrentPose : CurrentOrientation [%f,%f,%f] BaseOrientation [%f,%f,%f] CachedFinalHeadRotation [%f,%f,%f]"),
		CurrentOrientation.X, CurrentOrientation.Y, CurrentOrientation.Z,
		BaseOrientation.X, BaseOrientation.Y, BaseOrientation.Z,
		CachedFinalHeadRotation.X, CachedFinalHeadRotation.Y, CachedFinalHeadRotation.Z
	);
#endif

#else

	// very basic.  no head model, no prediction, using debuglocalplayer
	ULocalPlayer* Player = nullptr;
	if (GEngine)
	{
		Player = GEngine->GetDebugLocalPlayer();
	}
	float PreviewSensitivity = 1.0f;

	if (Player != NULL && Player->PlayerController != NULL && GWorld)
	{ 
		float MouseX = 0.0f;
		float MouseY = 0.0f;
		Player->PlayerController->GetInputMouseDelta(MouseX, MouseY);

		double CurrentTime = FApp::GetCurrentTime();
		double DeltaTime = GWorld->GetDeltaSeconds();

		PoseYaw += (FMath::RadiansToDegrees(MouseX * DeltaTime * 4.0f) * PreviewSensitivity);
		PosePitch += (FMath::RadiansToDegrees(MouseY * DeltaTime * 4.0f) * PreviewSensitivity);
		PosePitch = FMath::Clamp(PosePitch, -90.0f + KINDA_SMALL_NUMBER, 90.0f - KINDA_SMALL_NUMBER);

		// UE_LOG(LogHMD, Log, TEXT("--------------GetCurrentPose MouseX=%f,MouseY=%f,PosePitch=%f,PoseYaw=%f"), MouseX, MouseY,PosePitch, PoseYaw);

		CurrentOrientation = FQuat(FRotator(PosePitch, PoseYaw, 0.0f));
	}
	else
	{
		CurrentOrientation = FQuat(FRotator(0.0f, 0.0f, 0.0f));
	}
	// TODO: add neck model to the editor emulatation.
	CurrentPosition = FVector::ZeroVector;
#endif

	return true;
}

bool FNibiruHMD::IsChromaAbCorrectionEnabled() const
{
	// 如果色差校正关闭。
	return true;
}

// 左右眼偏移
bool FNibiruHMD::GetRelativeEyePose(int32 DeviceId, EStereoscopicPass Eye, FQuat & OutOrientation, FVector & OutPosition)
{
	OutOrientation = FQuat::Identity;
	OutPosition = FVector::ZeroVector;
#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	if (DeviceId == IXRTrackingSystem::HMDDeviceId && (Eye == eSSP_LEFT_EYE || Eye == eSSP_RIGHT_EYE))
	{
		OutPosition = FVector(0, (Eye == EStereoscopicPass::eSSP_LEFT_EYE ? -.5 : .5) * GetInterpupillaryDistance() * GetWorldToMetersScale(), 0);
		return true;
	}
	else
#endif
	{
		return false;
	}
}

void FNibiruHMD::ResetOrientationAndPosition(float yaw)
{
	UE_LOG(LogHMD, Log, TEXT("--------------ResetOrientationAndPosition=%f"), yaw);
	ResetOrientation(yaw);
	ResetPosition();
}

void FNibiruHMD::ResetOrientation(float Yaw)
{
	UE_LOG(LogHMD, Log, TEXT("--------------ResetOrientation=%f"), Yaw);
#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	NibiruImport::NibiruResetHeadPose();
	SetBaseOrientation(FRotator(0.0f, Yaw, 0.0f).Quaternion());
#endif
}

void FNibiruHMD::SetBaseRotation(const FRotator& BaseRot)
{
	//UE_LOG(LogHMD, Log, TEXT("--------------SetBaseRotation=%f"), BaseRot.Yaw);
	SetBaseOrientation(FRotator(0.0f, BaseRot.Yaw, 0.0f).Quaternion());
}

FRotator FNibiruHMD::GetBaseRotation() const
{
	return GetBaseOrientation().Rotator();
}

void FNibiruHMD::SetBaseOrientation(const FQuat& BaseOrient)
{
	UE_LOG(LogHMD, Log, TEXT("--------------SetBaseOrientation=%f"), BaseOrient.X);
	BaseOrientation = BaseOrient;
}

FQuat FNibiruHMD::GetBaseOrientation() const
{
	return BaseOrientation;
}

// use unreal draw with sdk's distortion method
void FNibiruHMD::DrawDistortionMesh_RenderThread(struct FRenderingCompositePassContext& Context, const FIntPoint& TextureSize)
{
	const FSceneView& View = Context.View;
	FRHICommandListImmediate& RHICmdList = Context.RHICmdList;
	const FSceneViewFamily& ViewFamily = *(View.Family);
	FIntPoint ViewportSize = ViewFamily.RenderTarget->GetSizeXY();
	
	// DrawDistortionMesh_RenderThread ViewportSizeX=1280,ViewportSizeY=720,Texture=1280,720_EYE 1
	//UE_LOG(LogHMD, Log, TEXT("--------------DrawDistortionMesh_RenderThread ViewportSizeX=%d,ViewportSizeY=%d,Texture=%d,%d_EYE %d"), ViewportSize.X, ViewportSize.Y,
	//	TextureSize.X, TextureSize.Y, View.StereoPass);

#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	if (View.StereoPass == eSSP_LEFT_EYE)
	{
		RHICmdList.SetViewport(0, 0, 0.0f, ViewportSize.X / 2, ViewportSize.Y, 1.0f);
        RHICmdList.SetStreamSource(0, DistortionMeshVerticesLeftEye, 0);
		RHICmdList.DrawIndexedPrimitive(DistortionMeshIndices, 0, 0, NumVerts, 0, NumTris, 1);		
	}
	else
	{
		RHICmdList.SetViewport(ViewportSize.X / 2, 0, 0.0f, ViewportSize.X, ViewportSize.Y, 1.0f);
		RHICmdList.SetStreamSource(0, DistortionMeshVerticesRightEye, 0);
		RHICmdList.DrawIndexedPrimitive(DistortionMeshIndices, 0, 0, NumVerts, 0, NumTris, 1);
	}
#else
	// Editor Preview: We are using a hardcoded quad mesh for now with no distortion applyed.
	// TODO: We will add preview using real viewer profile later.
	{
		static const uint32 LocalNumVertsPerEye = 4;
		static const uint32 LocalNumTrisPerEye = 2;

		static const FDistortionVertex Verts[4] =
		{
			{ FVector2D(-1.0f, -1.0f), FVector2D(0.0f, 1.0f), FVector2D(0.0f, 1.0f), FVector2D(0.0f, 1.0f), 1.0f, 0.0f },
			{ FVector2D(1.0f, -1.0f), FVector2D(1.0f, 1.0f), FVector2D(1.0f, 1.0f), FVector2D(1.0f, 1.0f), 1.0f, 0.0f },
			{ FVector2D(-1.0f,  1.0f), FVector2D(0.0f, 0.0f), FVector2D(0.0f, 0.0f), FVector2D(0.0f, 0.0f), 1.0f, 0.0f },
			{ FVector2D(1.0f,  1.0f), FVector2D(1.0f, 0.0f), FVector2D(1.0f, 0.0f), FVector2D(1.0f, 0.0f), 1.0f, 0.0f },
		};

		FRHIResourceCreateInfo CreateInfo;
		FVertexBufferRHIRef VertexBufferRHI = RHICreateVertexBuffer(sizeof(FDistortionVertex) * 4, BUF_Volatile, CreateInfo);
		void* VoidPtr = RHILockVertexBuffer(VertexBufferRHI, 0, sizeof(FDistortionVertex) * 4, RLM_WriteOnly);
		FPlatformMemory::Memcpy(VoidPtr, Verts, sizeof(FDistortionVertex) * 4);
		RHIUnlockVertexBuffer(VertexBufferRHI);

		const uint32 XBound = TextureSize.X / 2;
		if(View.StereoPass == eSSP_LEFT_EYE)
		{
			RHICmdList.SetViewport(0, 0, 0.0f, XBound, TextureSize.Y, 1.0f);
			RHICmdList.SetStreamSource(0, VertexBufferRHI, 0);
			RHICmdList.DrawIndexedPrimitive(GTwoTrianglesIndexBuffer.IndexBufferRHI, 0, 0, LocalNumVertsPerEye, 0, LocalNumTrisPerEye, 1);
		}
		else
		{
			RHICmdList.SetViewport(XBound, 0, 0.0f, TextureSize.X, TextureSize.Y, 1.0f);
			RHICmdList.SetStreamSource(0, VertexBufferRHI, 0);
			RHICmdList.DrawIndexedPrimitive(GTwoTrianglesIndexBuffer.IndexBufferRHI, 0, 0, LocalNumVertsPerEye, 0, LocalNumTrisPerEye, 1);
		}
		VertexBufferRHI.SafeRelease();
	}
#endif

}

bool FNibiruHMD::IsStereoEnabled() const
{
	// UE_LOG(LogHMD, Log, TEXT("--------------IsStereoEnabled"));
	return true;
}

bool FNibiruHMD::EnableStereo(bool stereo)
{
	return true;
}

bool FNibiruHMD::IsActiveThisFrame(class FViewport* InViewport) const
{
	// FSceneViewExtensionBase是否激活
	// We need to use GEngine->IsStereoscopic3D in case the current viewport disallows running in stereo.
	// 编辑器预览为false，运行为true
	//return GEngine && GEngine->IsStereoscopic3D(InViewport);
	return false;
}

void FNibiruHMD::AdjustViewRect(EStereoscopicPass StereoPass, int32& X, int32& Y, uint32& SizeX, uint32& SizeY) const
{
#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	// AdjustViewRect SizeX=1920,SizeY=1080,X=0,Y=0
    // UE_LOG(LogHMD, Log, TEXT("--------------AdjustViewRect SizeX=%d,SizeY=%d,X=%d,Y=%d") , SizeX , SizeY , X , Y);
	SizeX = NVRRenderTargetSize.X / 2;
	SizeY = NVRRenderTargetSize.Y;
	if (StereoPass == eSSP_RIGHT_EYE)
	{
		X += SizeX;
	}
#else
  SizeX = SizeX / 2;
  if (StereoPass == eSSP_RIGHT_EYE)
  {
	  X += SizeX;
  }
#endif
}
 
FMatrix FNibiruHMD::GetPreviewViewerStereoProjectionMatrix(enum EStereoscopicPass StereoPass)
{
	if (StereoPass == eSSP_LEFT_EYE) 
	{
		const FMatrix LeftStereoProjectionMatrix = FMatrix(
			FPlane(1.213739f, 0.0f, 0.0f, 0.0f),
			FPlane(0.0f, 1.191754f, 0.0f, 0.0f),
			FPlane(-0.018448f, 0.000000f, 0.0f, 1.0f),
			FPlane(0.0f, 0.0f, 10.000000f, 0.0f)
		);
		return LeftStereoProjectionMatrix;
	} 
	else
	{
		const FMatrix RightStereoProjectionMatrix = FMatrix(
			FPlane(1.213739f, 0.0f, 0.0f, 0.0f),
			FPlane(0.0f, 1.191754f, 0.0f, 0.0f),
			FPlane(0.018448f, 0.000000f, 0.0f, 1.0f),
			FPlane(0.0f, 0.0f, 10.000000f, 0.0f)
		);
		return RightStereoProjectionMatrix;
	}
}

FMatrix FNibiruHMD::GetStereoProjectionMatrix(const enum EStereoscopicPass StereoPassType) const
{
	// projection matrix
#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	// Have to flip left/right and top/bottom to match UE4 expectations
	float ZNear = GNearClippingPlane;

	float Right = FPlatformMath::Tan(FMath::DegreesToRadians(profileData[0]));
	float Left = -FPlatformMath::Tan(FMath::DegreesToRadians(profileData[1]));
	float Bottom = -FPlatformMath::Tan(FMath::DegreesToRadians(profileData[2]));
	float Top = FPlatformMath::Tan(FMath::DegreesToRadians(profileData[3]));

	float SumRL = (Right + Left);
	float SumTB = (Top + Bottom);
	float InvRL = (1.0f / (Right - Left));
	float InvTB = (1.0f / (Top - Bottom));

	// UE_LOG(LogHMD, Log, TEXT("GetStereoProjectionMatrix : R.%f, L.%f, B.%f, T.%f. Near.%f"), Right, Left, Bottom, Top, ZNear);

	FPlane Plane0 = FPlane((2.0f * InvRL), 0.0f, 0.0f, 0.0f);
	FPlane Plane1 = FPlane(0.0f, (2.0f * InvTB), 0.0f, 0.0f);
	FPlane Plane2 = FPlane((SumRL * InvRL), (SumTB * InvTB), 0.0f, 1.0f);
	FPlane Plane3 = FPlane(0.0f, 0.0f, ZNear, 0.0f);

#if LOG_VIEWER_DATA_FOR_GENERATION 
	const TCHAR* EyeString = StereoPassType == eSSP_LEFT_EYE ? TEXT("Left") : TEXT("Right");
	UE_LOG(LogHMD, Log, TEXT("===== Begin Projection Matrix Eye %s"), EyeString);
	UE_LOG(LogHMD, Log, TEXT("const FMatrix %sStereoProjectionMatrix = FMatrix("), EyeString);
	UE_LOG(LogHMD, Log, TEXT("ZNear %f , Right %f , Left %f , Bottom %f , Top %f"), ZNear, Right, Left , Bottom , Top);
	UE_LOG(LogHMD, Log, TEXT("ProfileData %f_%f_%f_%f"), profileData[0], profileData[1], profileData[2], profileData[3]);
	UE_LOG(LogHMD, Log, TEXT("FPlane(%ff,  0.0f, 0.0f, 0.0f),"), Plane0.X);
	UE_LOG(LogHMD, Log, TEXT("FPlane(0.0f, %ff,  0.0f, 0.0f),"), Plane1.Y);
	UE_LOG(LogHMD, Log, TEXT("FPlane(%ff,  %ff,  0.0f, 1.0f),"), Plane2.X, Plane2.Y);
	UE_LOG(LogHMD, Log, TEXT("FPlane(0.0f, 0.0f, %ff,  0.0f)"), Plane3.Z);
	UE_LOG(LogHMD, Log, TEXT(");"));
	UE_LOG(LogHMD, Log, TEXT("===== End Projection Matrix Eye"));
#endif

	return FMatrix(
		Plane0,
		Plane1,
		Plane2,
		Plane3
	);

#else //!NIBIRUVRHMD_SUPPORTED_PLATFORMS
	{
		//UE_LOG(LogHMD, Log, TEXT("--------------GetStereoProjectionMatrix"));
		return GetPreviewViewerStereoProjectionMatrix(StereoPassType);
	}
#endif

}

void FNibiruHMD::GetEyeRenderParams_RenderThread(const FRenderingCompositePassContext& Context, FVector2D& EyeToSrcUVScaleValue, FVector2D& EyeToSrcUVOffsetValue) const
{
	if (Context.View.StereoPass == eSSP_LEFT_EYE)
	{
		EyeToSrcUVOffsetValue.X = 0.0f;
		EyeToSrcUVOffsetValue.Y = 0.0f;

		EyeToSrcUVScaleValue.X = 0.5f;
		EyeToSrcUVScaleValue.Y = 1.0f;
	}
	else
	{
		EyeToSrcUVOffsetValue.X = 0.5f;
		EyeToSrcUVOffsetValue.Y = 0.0f;

		EyeToSrcUVScaleValue.X = 0.5f;
		EyeToSrcUVScaleValue.Y = 1.0f;
	}
}



bool FNibiruHMD::ShouldUseSeparateRenderTarget() const
{
	check(IsInGameThread());
	return IsStereoEnabled() && useDTRMode;
}

// called when IsActiveThisFrame return true
void FNibiruHMD::SetupViewFamily(FSceneViewFamily& InViewFamily)
{
	// UE_LOG(LogHMD, Log, TEXT("FNibiruHMD::SetupViewFamily %d"), useDTRMode);
	InViewFamily.EngineShowFlags.MotionBlur = 0;
	// use dtr mode need disable HMDDistortion flag
	InViewFamily.EngineShowFlags.HMDDistortion = !useDTRMode;
	InViewFamily.EngineShowFlags.ScreenPercentage = false;
	InViewFamily.EngineShowFlags.StereoRendering = IsStereoEnabled();
	// TODO: Move this to EnableStereo
	// Uncap fps to enable FPS higher than 62
	if (GEngine)
	{
		GEngine->bForceDisableFrameRateSmoothing = true;
	}	
#ifdef DEBUG_LOG_ENABLE
	UE_LOG(LogHMD, Log, TEXT("FNibiruHMD::SetupViewFamily"));
#endif
}

// called when IsActiveThisFrame return true
void FNibiruHMD::SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView)
{
#ifdef DEBUG_LOG_ENABLE
	UE_LOG(LogHMD, Log, TEXT("FNibiruHMD::SetupView"));
#endif
    // do nothing
}

// called when IsActiveThisFrame return true
void FNibiruHMD::PreRenderView_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneView& InView)
{
	// do nothing
#ifdef DEBUG_LOG_ENABLE
	UE_LOG(LogHMD, Log, TEXT("FNibiruHMD::PreRenderView_RenderThread"));
#endif
}

// called when IsActiveThisFrame return true
void FNibiruHMD::BeginRenderViewFamily(FSceneViewFamily& InViewFamily)
{
	// do nothing
#ifdef DEBUG_LOG_ENABLE
	UE_LOG(LogHMD, Log, TEXT("FNibiruHMD::BeginRenderViewFamily"));
#endif
}

// called when IsActiveThisFrame return true
void FNibiruHMD::PreRenderViewFamily_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneViewFamily& InViewFamily)
{
#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
#ifdef DEBUG_LOG_ENABLE
	UE_LOG(LogHMD, Log, TEXT("FNibiruHMD::PreRenderViewFamily_RenderThread"));
#endif
#endif
}

// ------  Called on Render Thread ------

void FNibiruHMD::OnBeginRendering_GameThread()
{
#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	// Note that we force not enqueue the CachedHeadPose when start loading a map until a new game frame started.
	// This is for solving the one frame flickering issue when load another level due to that there is one frame
	// the scene is rendered before the camera is updated.
	// TODO: We need to investigate a better solution here.
#ifdef DEBUG_LOG_ENABLE
	UE_LOG(LogHMD, Log, TEXT("FNibiruHMD::OnBeginRendering_GameThread"));
#endif

#endif
}

// ------  Called on Render Thread ------
void FNibiruHMD::OnBeginRendering_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneViewFamily& ViewFamily)
{
#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	if(useDTRMode) {
		if (bBeginFrame) return;
		bBeginFrame = true;
#ifdef DEBUG_LOG_ENABLE
		UE_LOG(LogHMD, Log, TEXT("[F] FNibiruHMD::OnBeginRendering_RenderThread"));
#endif
		if (CustomPresent)
		{   
			// UpdateNibiruHeadPose();
			static_cast<FNibiruVRHMDCustomPresent*>(CustomPresent)->BeginRendering(ViewFamily.FrameNumber, CachedHeadPose);
		}
   }

#endif

}

FIntPoint FNibiruHMD::GetNVRHMDRenderTargetSize()
{
	return NVRRenderTargetSize;
}

FIntPoint FNibiruHMD::SetRenderTargetSizeToDefault()
{
	NVRRenderTargetSize = FIntPoint::ZeroValue;
#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	if (useDTRMode)
	{
		NVRRenderTargetSize.X = profileData[15] > 0 ? 2 * (int)profileData[15] : NVR_DEFAULT_EYE_RENDER_TARGET_WIDTH * 2;
		NVRRenderTargetSize.Y = profileData[16] > 0 ? (int)profileData[16] : NVR_DEFAULT_EYE_RENDER_TARGET_HEIGHT;
	}
	else
	{
		FPlatformRect Rect = FAndroidWindow::GetScreenRect();
		NVRRenderTargetSize.X = Rect.Right;
		NVRRenderTargetSize.Y = Rect.Bottom;
	}
	/*if (NVRRenderTargetSize.Y > 1440) {//NOLO 4K 1920*1080
		NVRRenderTargetSize.X = 960 * 2;
		NVRRenderTargetSize.Y = 1080;
	}*/
#endif
	return NVRRenderTargetSize;
}

// onResume
void FNibiruHMD::ApplicationResumeDelegate()
{
#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	// check(CustomPresent); samsung7420 crash
	if (!useDTRMode) {
		// dft mode
		nvrModeParms parms;
		NibiruImport::NibiruEnterVRMode(&parms);
		return;
	}

	if (!CustomPresent) 
	{
		FPlatformMisc::LowLevelOutputDebugStringf(TEXT("+++++++ EnterVRMode ++++++, CustomPresent is NULL , Please Check it !"), gettid());
	}

	if (IsInRenderingThread())
	{
		FPlatformMisc::LowLevelOutputDebugStringf(TEXT("+++++++ EnterVRMode ++++++, On RT! tid = %d"), gettid());
		if (CustomPresent) { 
			static_cast<FNibiruVRHMDCustomPresent*>(CustomPresent)->EnterVRMode_RenderThread();
		}
	}
	else
	{
		FPlatformMisc::LowLevelOutputDebugStringf(TEXT("+++++++ EnterVRMode ++++++, tid = %d"), gettid());
		FNibiruVRHMDCustomPresent* This = static_cast<FNibiruVRHMDCustomPresent*>(CustomPresent);

		ENQUEUE_RENDER_COMMAND(ApplicationResumeDelegate)(
		[This](FRHICommandListImmediate& RHICmdList)
		{
		    if(This) This->EnterVRMode_RenderThread();
		});

	}
#endif
}

// onPause
void FNibiruHMD::ApplicationPauseDelegate()
{
#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	//check(CustomPresent);
	if (!useDTRMode) {
		// dft mode
		NibiruImport::NibiruLeaveVRMode();
		return;
	}

	if (!CustomPresent)
	{
		FPlatformMisc::LowLevelOutputDebugStringf(TEXT("+++++++ LeaveVRMode ++++++, CustomPresent is NULL , Please Check it !"), gettid());
	}

	if (IsInRenderingThread())
	{
		FPlatformMisc::LowLevelOutputDebugStringf(TEXT("+++++++ LeaveVRMode ++++++, On RT! tid = %d"), gettid());
		if (CustomPresent) {
			static_cast<FNibiruVRHMDCustomPresent*>(CustomPresent)->LeaveVRMode_RenderThread();
		}
	}
	else
	{
		FPlatformMisc::LowLevelOutputDebugStringf(TEXT("+++++++ LeaveVRMode ++++++, tid = %d"), gettid());
		FNibiruVRHMDCustomPresent* This = static_cast<FNibiruVRHMDCustomPresent*>(CustomPresent);
		ENQUEUE_RENDER_COMMAND(ApplicationPauseDelegate)(
		[This](FRHICommandListImmediate& RHICmdList)
		{
		   if(This) This->LeaveVRMode_RenderThread();
		});
	} 
#endif
}

////////////////////
// FNibiruHMD //
////////////////////
FNibiruHMD::FNibiruHMD(const FAutoRegister& AutoRegister) : FHeadMountedDisplayBase(nullptr)
	,FSceneViewExtensionBase(AutoRegister)
#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	,CustomPresent(nullptr)
#endif	
	, useDTRMode(false)
	, PosePitch(0.0f)
	, PoseYaw(0.0f)
	, DistortionPointsX(40)
	, DistortionPointsY(40)
	, NumVerts(0)
	, NumTris(0)
	, NumIndices(0)
	, BaseOrientation(FQuat::Identity)
	, RendererModule(nullptr)
	, DistortionMeshIndices(nullptr)
	, DistortionMeshVerticesLeftEye(nullptr)
	, DistortionMeshVerticesRightEye(nullptr)
	, CurHmdOrientation(FQuat::Identity)
	, CurHmdPosition(FVector::ZeroVector)
	, LastSensorTime(-1.0)
	, bUseNVRApiDistortionCorrection(false)
	// true 开启dtr，false 使用dft
	,bEnableMultiView(false)
{
	//SixDofMode = GetDefault<UNXRSDKSettings>()->SixDofMode;
	SixDofMode = ESixDofMode::Head_6DOF_Ctrl_6DOF;
	UE_LOG(LogHMD, Log, TEXT("NibiruHMD Plugin Create [SixDofMode.%d] ! "), (int) SixDofMode);
	IsSpt6DofDataApi = false;

#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	CachedFinalHeadPosition = FVector::ZeroVector;
    // set to identity
	CachedHeadPose = 	{ { { 1.0f, 0.0f, 0.0f, 0.0f },
						{ 0.0f, 1.0f, 0.0f, 0.0f },
						{ 0.0f, 0.0f, 1.0f, 0.0f },
						{ 0.0f, 0.0f, 0.0f, 1.0f } } };

	jobject thisActivity = FJavaWrapper::GameActivityThis;
	long pointer = AndroidThunkCpp_GetNativeNVRApi();
    //  dtr
	useDTRMode = AndroidThunkCpp_GetNativeISDTR();

	VerifyStatus = AndroidThunkCpp_GetVerifyStatus();
    if(useDTRMode)
    {
    	if (GEngine)
		{
    		// Uncap fps to enable FPS higher than 62
    		GEngine->bSmoothFrameRate = false;
		}

        // disable vsync
		IConsoleVariable* CVSyns = IConsoleManager::Get().FindConsoleVariable(TEXT("r.VSync"));
		CVSyns->Set(0.0f);

		// ALWAYS SET r.FinishCurrentFrame to 0! Otherwise the perf might be poor.
		IConsoleVariable* CFCFVar = IConsoleManager::Get().FindConsoleVariable(TEXT("r.FinishCurrentFrame"));
		CFCFVar->Set(0.0f);

        // 缩放效果
		IConsoleVariable* CMobSFVar = IConsoleManager::Get().FindConsoleVariable(TEXT("r.MobileContentScaleFactor"));
		CMobSFVar->Set(0.0f);

 

    }
    // bUseNVRApiDistortionCorrection: true=native so distortion, false=ue4 PostProcessHMD
    SetDistortionCorrectionMethod(useDTRMode);
	//  
	NibiruImport::Init(); 
	IsSpt6DofDataApi = NibiruImport::DoesSupport6DofData();

	nvrModeParms parms;

	nvrJava JavaVM;
	JavaVM.Vm = GJavaVM;
	JavaVM.ActivityObject = thisActivity;
	GJavaVM->AttachCurrentThread(&JavaVM.Env, nullptr);

	parms.Java = JavaVM;
	parms.Display = (size_t)AndroidEGL::GetInstance()->GetDisplay();
	parms.WindowSurface = (size_t)AndroidEGL::GetInstance()->GetNativeWindow();
	parms.ShareContext = (size_t)AndroidEGL::GetInstance()->GetRenderingContext()->eglContext;

	nvr_init_info nvrInfo = NibiruImport::NibiruInit(PLUGIN_SDK_VERSION, pointer, &parms);

	UE_LOG(LogHMD, Log, TEXT("NibiruXR UNREAL SDK VERSION IS %d , %d , DTR MODE %d ,[%d,%d,%d], Spt6DofApi.%d, %ld, GRHISupportsRHIThread.%d,VerifyStatus.%d !"), PLUGIN_SDK_VERSION , nvrInfo.sdk_version, 
		useDTRMode, AndroidThunkCpp_GetNativeISDTR(), AndroidThunkCpp_GetNativeISSupportDTR(), AndroidThunkCpp_GetNativeISDFT(), IsSpt6DofDataApi, pointer, 
		GRHISupportsRHIThread, VerifyStatus);

	// mesh 
	DistortionPointsX = nvrInfo.mesh_x;
	DistortionPointsY = nvrInfo.mesh_y;

	// nvr config data
	NibiruImport::NibiruGetNVRConfig(profileData);

	if (useDTRMode) {
		// Create custom present class
		CustomPresent = new FNibiruVRHMDCustomPresent(this);
	}
	// Refresh delegate
	FCoreDelegates::ApplicationHasEnteredForegroundDelegate.AddRaw(this, &FNibiruHMD::ApplicationResumeDelegate);
	FCoreDelegates::ApplicationWillEnterBackgroundDelegate.AddRaw(this, &FNibiruHMD::ApplicationPauseDelegate);

	//Get mobile multi view state
	/*static const auto CVarMobileMultiView = IConsoleManager::Get().FindTConsoleVariableDataInt(TEXT("vr.MobileMultiView"));
	static const auto CVarMobileHDR = IConsoleManager::Get().FindTConsoleVariableDataInt(TEXT("r.MobileHDR"));
	const bool bIsMobileMultiViewEnabled = (CVarMobileMultiView && CVarMobileMultiView->GetValueOnAnyThread() != 0);
	const bool bIsUsingMobileMultiView = bIsMobileMultiViewEnabled;// && GSupportsMobileMultiView;
	const bool bMobileHDR = CVarMobileHDR && CVarMobileHDR->GetValueOnAnyThread() == 1;

	if (bMobileHDR)
	{
		bEnableMultiView = false;
	}else
	{
		bEnableMultiView = bIsUsingMobileMultiView;
	}*/

	
#endif
	
	// Get renderer module
	static const FName RendererModuleName("Renderer");
	RendererModule = FModuleManager::GetModulePtr<IRendererModule>(RendererModuleName);
	check(RendererModule);
	
	// Set the default rendertarget size to the default size in UE4
	SetRenderTargetSizeToDefault();

	// Enabled by default
	EnableHMD(true);
	EnableStereo(true);

	// Initialize distortion mesh and indices
	SetNumOfDistortionPoints(DistortionPointsX, DistortionPointsY); 

	SetGazeEnabled(false);
	UE_LOG(LogHMD, Log, TEXT("FNibiruHMD::Create()"));

}

void FNibiruHMD::Shutdown()
{
	#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	// destory
	if (IsInRenderingThread())
	{
		NibiruImport::NibiruDestory();
		NibiruImport::Uninit();
	} else {
		FNibiruHMD * const Self = this;
		ENQUEUE_RENDER_COMMAND(Shutdown)([Self](FRHICommandListImmediate& RHICmdList)
		 { 
				NibiruImport::NibiruDestory();
		        NibiruImport::Uninit();
		 }
		);
		FlushRenderingCommands();
	}
	UE_LOG(LogHMD, Log, TEXT("NibiruVR shutdown."));
	#endif
}

FNibiruHMD::~FNibiruHMD()
{
	UE_LOG(LogHMD, Log, TEXT("FNibiruHMD::~"));
	DistortionMeshIndices.SafeRelease();
	DistortionMeshVerticesLeftEye.SafeRelease();
	DistortionMeshVerticesRightEye.SafeRelease();
	
	#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	if (CustomPresent) {
		static_cast<FNibiruVRHMDCustomPresent*>(CustomPresent)->Shutdown();
		CustomPresent = nullptr;
	}
	Shutdown();
	#endif
}

bool FNibiruHMD::IsInitialized() const
{
	UE_LOG(LogHMD, Log, TEXT("FNibiruHMD::IsInitialized"));
	return true;
}

void FNibiruHMD::CalculateRenderTargetSize(const class FViewport& Viewport, uint32& InOutSizeX, uint32& InOutSizeY)
{
	check(IsInGameThread());

	// CalculateRenderTargetSize 1920,1080 [2048,1024]
    //UE_LOG(LogHMD, Log, TEXT("FNibiruHMD::CalculateRenderTargetSize %d,%d [%d,%d]"),InOutSizeX,InOutSizeY,NVRRenderTargetSize.X,NVRRenderTargetSize.Y);

	// Change the render target size when it is valid
	if (NVRRenderTargetSize.X != 0 && NVRRenderTargetSize.Y != 0)
	{
		InOutSizeX = NVRRenderTargetSize.X;
		InOutSizeY = NVRRenderTargetSize.Y;
	}else {
		UE_LOG(LogHMD, Log, TEXT("FNibiruHMD::CalculateRenderTargetSize Failed %d,%d"),NVRRenderTargetSize.X, NVRRenderTargetSize.Y);
	}
}

float FNibiruHMD::GetWorldToMetersScale() const
{
	if (IsInGameThread() &&  GWorld != nullptr)
	{
		return GWorld->GetWorldSettings()->WorldToMeters;
	}

	// Default value, assume Unreal units are in centimeters
	return 100.0f;
}

void FNibiruHMD::UpdateNibiruHeadPose()
{
#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	// Update CachedHeadPose
	FMatrix FinalHeadPoseInverseUnreal;
	// Convert the final pose into Unreal data type
	FMatrix FinalHeadPoseUnreal;

	if (IsSpt6DofDataApi)
	{
		float position[3];
		CachedHeadPose = NibiruImport::NibiruGetSensorDataWithPosition(&viewNumber, position);
		memcpy(FinalHeadPoseUnreal.M[0], CachedHeadPose.m[0], 4 * 4 * sizeof(float));
		// Inverse the view matrix so we can get the world position of the pose
		FinalHeadPoseInverseUnreal = FinalHeadPoseUnreal.Inverse();

		if (SixDofMode != ESixDofMode::Head_3DOF_Ctrl_3DOF)
		{
			FinalHeadPoseInverseUnreal.M[0][3] = position[0];
			FinalHeadPoseInverseUnreal.M[1][3] = position[1];
			FinalHeadPoseInverseUnreal.M[2][3] = position[2];
		}
	}
	else 
	{
		CachedHeadPose = NibiruImport::NibiruGetSensorData(&viewNumber);
		memcpy(FinalHeadPoseUnreal.M[0], CachedHeadPose.m[0], 4 * 4 * sizeof(float));	
		// Inverse the view matrix so we can get the world position of the pose
		FinalHeadPoseInverseUnreal = FinalHeadPoseUnreal.Inverse();
	}

	// Number of Unreal Units per meter.
	const float WorldToMetersScale = GetWorldToMetersScale();

	// nvr is using a openGl Right Handed coordinate system, UE is left handed.
	// The following code is converting the gvr coordinate system to UE coordinates.

	// nvr: Negative Z is Forward, UE: Positive X is Forward.
	CachedFinalHeadPosition.X = -FinalHeadPoseInverseUnreal.M[2][3] * WorldToMetersScale;

	// nvr: Positive X is Right, UE: Positive Y is Right.
	CachedFinalHeadPosition.Y = FinalHeadPoseInverseUnreal.M[0][3] * WorldToMetersScale;

	// nvr: Positive Y is Up, UE: Positive Z is Up
	CachedFinalHeadPosition.Z = FinalHeadPoseInverseUnreal.M[1][3] * WorldToMetersScale;

	// Convert nvr right handed coordinate system rotation into UE left handed coordinate system.
	CachedFinalHeadRotation = FQuat(FinalHeadPoseUnreal);
	CachedFinalHeadRotation = FQuat(-CachedFinalHeadRotation.Z, CachedFinalHeadRotation.X, CachedFinalHeadRotation.Y, -CachedFinalHeadRotation.W);
 
#ifdef DEBUG_LOG_ENABLE
	UE_LOG(LogHMD, Log, TEXT("FNibiruHMD::UpdateNibiruHeadPose.viewNumber=%d,CachedFinalHeadRotation [%f,%f,%f]"), viewNumber, 
		CachedFinalHeadRotation.X, CachedFinalHeadRotation.Y, CachedFinalHeadRotation.Z);
#endif


#endif
}

/**
* This method is called when new game frame begins (called on a game thread).
*/
bool FNibiruHMD::OnStartGameFrame(FWorldContext& WorldContext)
{
	// UE_LOG(LogHMD, Log, TEXT("Start Game Frame!!!"));
	// Handle back coming from viewer magnet clickers or ui layer
	if (bBackDetected)
	{
		HandleNVRBackEvent();
		bBackDetected = false;
	}
#if WITH_ENGINE
#ifdef DEBUG_LOG_ENABLE
	UE_LOG(LogHMD, Log, TEXT("FNibiruHMD::OnStartGameFrame"));
#endif
#endif

    // DFT模式更新头部Pose
	if(!useDTRMode) {
	   // Update the head pose at the begnning of a frame. This headpose will be used for both simulation and rendering.
	   UpdateNibiruHeadPose();
	}
	return true;
}

bool FNibiruHMD::OnEndGameFrame(FWorldContext& WorldContext)
{
#if WITH_ENGINE 
#ifdef DEBUG_LOG_ENABLE
	UE_LOG(LogHMD, Log, TEXT("FNibiruHMD::OnEndGameFrame"));
#endif
#endif
	return true;
}

FString FNibiruHMD::GetVersionString() const
{
	FString s = FString::Printf(TEXT("NibiruVR - %s, VrLib: %s, built %s, %s"), *FEngineVersion::Current().ToString(), TEXT("NVR"),
		UTF8_TO_TCHAR(__DATE__), UTF8_TO_TCHAR(__TIME__));
	return s;
}

void FNibiruHMD::SetDistortionCorrectionMethod(bool bInUseNVRApiDistortionCorrection)
{
	UE_LOG(LogHMD, Log, TEXT("SetDistortionCorrectionMethod()  %d"), bInUseNVRApiDistortionCorrection);
	bUseNVRApiDistortionCorrection = bInUseNVRApiDistortionCorrection;
}

bool FNibiruHMD::IsUsingNVRApiDistortionCorrection() const
{
	return bUseNVRApiDistortionCorrection;
}


void FNibiruHMD::SetDistortionMeshSize(EDistortionMeshSizeEnum MeshSize)
{
#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	switch (MeshSize)
	{
	case EDistortionMeshSizeEnum::DMS_VERYSMALL:
		SetNumOfDistortionPoints(20, 20);
		break;
	case EDistortionMeshSizeEnum::DMS_SMALL:
		SetNumOfDistortionPoints(40, 40);
		break;
	case EDistortionMeshSizeEnum::DMS_MEDIUM:
		SetNumOfDistortionPoints(60, 60);
		break;
	case EDistortionMeshSizeEnum::DMS_LARGE:
		SetNumOfDistortionPoints(80, 80);
		break;
	case EDistortionMeshSizeEnum::DMS_VERYLARGE:
		SetNumOfDistortionPoints(100, 100);
		break;
	}
#endif
}

void FNibiruHMD::SetNumOfDistortionPoints(int32 XPoints, int32 YPoints)
{
	UE_LOG(LogHMD, Log, TEXT("SetNumOfDistortionPoints(%d * %d)"), XPoints, YPoints);
	// Force non supported platform distortion mesh be 40 x 40
#if !NIBIRUVRHMD_SUPPORTED_PLATFORMS
	XPoints = 40;
	YPoints = 40;
#endif

	// clamp values
	if (XPoints < 2)
	{
		XPoints = 2;
	}
	else if (XPoints > 200)
	{
		XPoints = 200;
	}

	if (YPoints < 2)
	{
		YPoints = 2;
	}
	else if (YPoints > 200)
	{
		YPoints = 200;
	}

	// calculate our values
	DistortionPointsX = XPoints;
	DistortionPointsY = YPoints;
	NumVerts = DistortionPointsX * DistortionPointsY;
	NumTris = (DistortionPointsX - 1) * (DistortionPointsY - 1) * 2;
	NumIndices = NumTris * 3;

	// generate the distortion mesh
	FNibiruHMD * const Self = this;
	ENQUEUE_RENDER_COMMAND(GenerateDistortionCorrectionCmd)([Self](FRHICommandListImmediate& RHICmdList)
	{
		Self->GenerateDistortionCorrectionIndexBuffer();
		Self->GenerateDistortionCorrectionVertexBuffer(eSSP_LEFT_EYE);
		Self->GenerateDistortionCorrectionVertexBuffer(eSSP_RIGHT_EYE);
	});
}

void FNibiruHMD::GenerateDistortionCorrectionIndexBuffer()
{
	FRHIResourceCreateInfo CreateInfo;
	DistortionMeshIndices = RHICreateIndexBuffer(sizeof(uint16), sizeof(uint16) * 6 * DistortionPointsX * DistortionPointsY, BUF_Static, CreateInfo);
	void* VoidPtr = RHILockIndexBuffer(DistortionMeshIndices, 0, sizeof(uint16) * 6 * DistortionPointsX * DistortionPointsY, RLM_WriteOnly);
	uint16* DistortionMeshIndicesPtr = reinterpret_cast<uint16*>(VoidPtr);

	uint32 InsertIndex = 0;
	for (uint32 y = 0; y < DistortionPointsY - 1; ++y)
	{
		for (uint32 x = 0; x < DistortionPointsX - 1; ++x)
		{
			// Calculate indices for the triangle
			const uint16 BottomLeft = (y * DistortionPointsX) + x + 0;
			const uint16 BottomRight = (y * DistortionPointsX) + x + 1;
			const uint16 TopLeft = (y * DistortionPointsX) + x + 0 + DistortionPointsX;
			const uint16 TopRight = (y * DistortionPointsX) + x + 1 + DistortionPointsX;

			// Insert indices
			DistortionMeshIndicesPtr[InsertIndex + 0] = BottomLeft;
			DistortionMeshIndicesPtr[InsertIndex + 1] = BottomRight;
			DistortionMeshIndicesPtr[InsertIndex + 2] = TopRight;
			DistortionMeshIndicesPtr[InsertIndex + 3] = BottomLeft;
			DistortionMeshIndicesPtr[InsertIndex + 4] = TopRight;
			DistortionMeshIndicesPtr[InsertIndex + 5] = TopLeft;
			InsertIndex += 6;
		}
	}
    RHIUnlockIndexBuffer(DistortionMeshIndices);
	check(InsertIndex == NumIndices);
}

void FNibiruHMD::GenerateDistortionCorrectionVertexBuffer(EStereoscopicPass Eye)
{
	FVertexBufferRHIRef& DistortionMeshVertices = (Eye == eSSP_LEFT_EYE) ? DistortionMeshVerticesLeftEye : DistortionMeshVerticesRightEye;
	FRHIResourceCreateInfo CreateInfo;
	DistortionMeshVertices = RHICreateVertexBuffer(sizeof(FDistortionVertex) * NumVerts, BUF_Static, CreateInfo);
	void* VoidPtr = RHILockVertexBuffer(DistortionMeshVertices, 0, sizeof(FDistortionVertex) * NumVerts, RLM_WriteOnly);
	FDistortionVertex* Verts = reinterpret_cast<FDistortionVertex*>(VoidPtr);

#if NIBIRUVRHMD_SUPPORTED_PLATFORMS

	// Fill out distortion vertex info, using NVR Api to calculate transformation coordinates
	const nvr_eye Type = (Eye == eSSP_RIGHT_EYE) ? NVR_RIGHT_EYE : NVR_LEFT_EYE;
	const float XPosOffset = (Type == NVR_LEFT_EYE) ? -1.0f : 0.0f;
	uint32 VertexIndex = 0;
	for (uint32 y = 0; y < DistortionPointsY; ++y)
	{
		for (uint32 x = 0; x < DistortionPointsX; ++x)
		{
			nvr_vec2f UndistortedCoord = nvr_vec2f{ float(x) / float(DistortionPointsX - 1), float(y) / float(DistortionPointsY - 1) };
			nvr_vec2f DistortedCoords[3];
			NibiruImport::NibiruComputeDistortedPoint(Type, UndistortedCoord, DistortedCoords);

			float ScreenYDirection = -1.0f;
 
			const FVector2D ScreenPos = FVector2D(UndistortedCoord.x * 2.0f - 1.0f, (UndistortedCoord.y * 2.0f - 1.0f) * ScreenYDirection);

			const FVector2D UndistortedUV = FVector2D(UndistortedCoord.x, UndistortedCoord.y);
			const FVector2D OrigRedUV = FVector2D(DistortedCoords[0].x, DistortedCoords[0].y);
			const FVector2D OrigGreenUV = FVector2D(DistortedCoords[1].x, DistortedCoords[1].y);
			const FVector2D OrigBlueUV = FVector2D(DistortedCoords[2].x, DistortedCoords[2].y);

			// Final distorted UVs
			FVector2D FinalRedUV = OrigRedUV;
			FVector2D FinalGreenUV = OrigGreenUV;
			FVector2D FinalBlueUV = OrigBlueUV;
 
			FDistortionVertex FinalVertex = FDistortionVertex{ ScreenPos, FinalRedUV, FinalGreenUV, FinalBlueUV, 1.0f, 0.0f };
			Verts[VertexIndex++] = FinalVertex;

#if LOG_VIEWER_DATA_FOR_GENERATION
			UE_LOG(LogHMD, Log, TEXT("\tFDistortionVertex{ FVector2D(%ff, %ff), FVector2D(%ff, %ff), FVector2D(%ff, %ff), FVector2D(%ff, %ff), 1.0f, 0.0f }%s"),
				ScreenPos.X, ScreenPos.Y,
				FinalRedUV.X, FinalRedUV.Y,
				FinalGreenUV.X, FinalGreenUV.Y,
				FinalBlueUV.X, FinalBlueUV.Y,
				VertexIndex != NumVerts ? TEXT(",") : TEXT(""));
#endif // LOG_VIEWER_DATA_FOR_GENERATION
		}
	}

	check(VertexIndex == NumVerts);
#endif

	RHIUnlockVertexBuffer(DistortionMeshVertices);
}


void FNibiruHMD::HandleNVRBackEvent()
{
	if (GEngine &&
		GEngine->GameViewport &&
		GEngine->GameViewport->Viewport &&
		GEngine->GameViewport->Viewport->GetClient())
	{
#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
		GEngine->GameViewport->Viewport->GetClient()->InputKey(GEngine->GameViewport->Viewport, 0, EKeys::Android_Back, EInputEvent::IE_Pressed);
		GEngine->GameViewport->Viewport->GetClient()->InputKey(GEngine->GameViewport->Viewport, 0, EKeys::Android_Back, EInputEvent::IE_Released);
#endif
	}
}

// This is called from nativeKeyEvent in GameActivity
#if PLATFORM_ANDROID
JNI_METHOD void Java_com_epicgames_ue4_GameActivity_nativeKeyEvent(JNIEnv* jenv, jobject thiz, jint keycode, jint keyaction)
{
	if (FTaskGraphInterface::IsRunning() &&GEngine)
	{
		FGraphEventRef KeyEvent = FFunctionGraphTask::CreateAndDispatchWhenReady([keycode, keyaction]()
		{
			FNibiruHMD* hmd = static_cast<FNibiruHMD *>(GEngine->XRSystem->GetHMDDevice());
			if (hmd)
			{
				hmd->NotifyKeyEvent(keycode, keyaction);
			}
		}, TStatId(), NULL, ENamedThreads::GameThread);
	}
}

JNI_METHOD void Java_com_epicgames_ue4_GameActivity_nativeUpdateVerifyStatus(JNIEnv* jenv, jobject thiz, jint status)
{
	if (FTaskGraphInterface::IsRunning()&&GEngine)
	{
		FGraphEventRef KeyEvent = FFunctionGraphTask::CreateAndDispatchWhenReady([status]()
		{
			FNibiruHMD* hmd = static_cast<FNibiruHMD *>(GEngine->XRSystem->GetHMDDevice());
			if (hmd)
			{
				hmd->UpdateVerifyStatus(status);
			}
		}, TStatId(), NULL, ENamedThreads::GameThread);
	}
}

#endif

void FNibiruHMD::UpdateVerifyStatus(int status)
{
	VerifyStatus = status;
	UE_LOG(LogHMD, Log, TEXT("UpdateVerifyStatus: %d"), VerifyStatus);
}

int FNibiruHMD::GetVerifyStatus()
{
	return VerifyStatus;
}

void FNibiruHMD::NotifyKeyEvent(int keyCode, int keyAction)
{
	UE_LOG(LogHMD, Log, TEXT("NotifyKeyEvent: Code.%d,Action.%d"), keyCode, keyAction);
	myNibiruKeyEventCallback.ExecuteIfBound(keyCode, keyAction);
}
 
/**
* Passing key events to HMD.
* If returns 'false' then key will be handled by PlayerController;
* otherwise, key won't be handled by the PlayerController.
*/
bool FNibiruHMD::HandleInputKey(UPlayerInput* input, const struct FKey& Key, enum EInputEvent EventType, float AmountDepressed, bool bGamepad)
{
    UE_LOG(LogHMD, Log, TEXT("HandleInputKey: KEY %s evt, evttype %d, gamepad %d"), *Key.ToString(), (int)EventType, int(bGamepad));
 
	int nibiruKeyCode = NIBIRU_KEY_NON_NVR;
	if (Key == EKeys::Gamepad_DPad_Up) {
		nibiruKeyCode = NIBIRU_KEY_UP;
	}
	else if (Key == EKeys::Gamepad_DPad_Down) {
		nibiruKeyCode = NIBIRU_KEY_DOWN;
     }
	else if (Key == EKeys::Gamepad_DPad_Left) {
		nibiruKeyCode = NIBIRU_KEY_LEFT;
	}
	else if (Key == EKeys::Gamepad_DPad_Right) {
		nibiruKeyCode = NIBIRU_KEY_RIGHT;
	}
	else if (Key == EKeys::Gamepad_FaceButton_Bottom || Key == EKeys::Enter) {
		// button ok 
		nibiruKeyCode = NIBIRU_KEY_ENTER;
	}
	else if (Key == EKeys::Android_Back) {
		nibiruKeyCode = NIBIRU_KEY_BACK;
	}
	int nibiruKeyAction = EventType == IE_Pressed ? 0 :1 ;


#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	// Execute Delegate 
	myNibiruKeyEventCallback.ExecuteIfBound(nibiruKeyCode, nibiruKeyAction);

	if (Key == EKeys::Android_Back)
	{
		if (EventType == IE_Pressed)
		{
			BackbuttonPressTime = FPlatformTime::Seconds();
		}
		else if (EventType == IE_Released)
		{
			if (FPlatformTime::Seconds() - BackbuttonPressTime < BACK_BUTTON_SHORT_PRESS_TIME)
			{
				// activity->finish
				AndroidThunkCpp_Quit();
			}
		}
		return true;
	}
#else
	myNibiruKeyEventCallback.ExecuteIfBound((int)EventType, nibiruKeyAction);
#endif
	return false;
}


void FNibiruHMD::RegisterNibiruKeyEventCallBack(FNibiruKeyEventCallbackDelegate OnNibiruKeyEventCallback) 
{
	UE_LOG(LogHMD, Log, TEXT("------------------RegisterNibiruKeyEventCallBack-----Success"));

	myNibiruKeyEventCallback = OnNibiruKeyEventCallback;
}

void FNibiruHMD::SetGazeEnabled(bool enabled) {
	// UE_LOG(LogHMD, Log, TEXT("------------------SetGazeEnabled-----%d"), enabled);
#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	/*NibiruImport::NibiruSetIntValue(NIB_KEY_ENABLE_POINT, enabled?1:0);*/
	NibiruImport::NibiruSetIntValue(NIB_KEY_ENABLE_POINT, 0);
#endif
}

void FNibiruHMD::SetGazePosZ(float z) {
	// UE_LOG(LogHMD, Log, TEXT("------------------SetGazePosZ-----%f"), z);
#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	//NibiruImport::NibiruSetFloatValue(NIB_KEY_ENABLE_POINT, z);
#endif
}

bool FNibiruHMD::EnumerateTrackedDevices(TArray<int32>& OutDevices, EXRTrackedDeviceType Type /*= EXRTrackedDeviceType::Any*/)
{
	if (Type == EXRTrackedDeviceType::Any || Type == EXRTrackedDeviceType::HeadMountedDisplay)
	{
		OutDevices.Add(IXRTrackingSystem::HMDDeviceId);
		return true;
	}
	return false;
}

void FNibiruHMD::RequestQuitGame()
{
#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	// activity->finish
	AndroidThunkCpp_Quit();
#endif
}