// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "NibiruHMDPrivatePCH.h"
#include "NibiruHMDFunctionLibrary.h"

#include "HeadMountedDisplay.h"
#include "HeadMountedDisplayBase.h"
#include "SceneViewExtension.h"
#include "RHIStaticStates.h"
#include "Slate/SceneViewport.h"
#include "RendererPrivate.h"
#include "ScenePrivate.h"
#include "PostProcess/PostProcessHMD.h"
#include "XRRenderTargetManager.h"
#include "XRRenderBridge.h"
#include "IXRInput.h"
#include "NXRSDKSettings.h"

#if NIBIRUVRHMD_SUPPORTED_ANDROID_PLATFORMS
#include "NibiruImport.h"
// #define DEBUG_LOG_ENABLE
#include "Android/AndroidEGL.h"
#include "OpenGLDrvPrivate.h"
#include "OpenGLResources.h"
#endif
// V2.1.0 base 20200923
#define PLUGIN_SDK_VERSION 210200923

#define NVR_DEFAULT_EYE_RENDER_TARGET_WIDTH		1024
#define NVR_DEFAULT_EYE_RENDER_TARGET_HEIGHT	1024

#define LOG_VIEWER_DATA_FOR_GENERATION 0

#if NIBIRUVRHMD_SUPPORTED_PLATFORMS


#include <GLES2/gl2.h>

  
//#include "OpenGLDrvPrivate.h"
//#include "OpenGLResources.h"
 
 

#endif

// define key code
#define NIBIRU_KEY_ENTER		23
#define NIBIRU_KEY_LEFT		    21
#define NIBIRU_KEY_RIGHT		22
#define NIBIRU_KEY_UP			19
#define NIBIRU_KEY_DOWN		    20
#define NIBIRU_KEY_BACK		    4
#define NIBIRU_KEY_NKEY		    110
#define NIBIRU_KEY_NON_NVR		-1

enum class EDistortionMeshSizeEnum : uint8
{
	DMS_VERYSMALL	UMETA(DisplayName = "Distortion Mesh Size Very Small 20x20"),
	DMS_SMALL		UMETA(DisplayName = "Distortion Mesh Size Small 40x40"),
	DMS_MEDIUM		UMETA(DisplayName = "Distortion Mesh Size Medium 60x60"),
	DMS_LARGE		UMETA(DisplayName = "Distortion Mesh Size Large 80x80"),
	DMS_VERYLARGE	UMETA(DisplayName = "Distortion Mesh Size Very Large 100x100")
};
#if NIBIRUVRHMD_SUPPORTED_ANDROID_PLATFORMS

// custom present
// Forward decl
class FNibiruHMD;

class FNibiruVRHMDTexture2DSet : public FOpenGLTexture2D
{

private:
	enum
	{
		TEXTURE_NUM = 3, // swap with 3 textures 
		//TEXTURE_WIDTH =  NVR_DEFAULT_EYE_RENDER_TARGET_WIDTH,
		//TEXTURE_HEIGHT = NVR_DEFAULT_EYE_RENDER_TARGET_HEIGHT,
	};

public:
	static FNibiruVRHMDTexture2DSet* CreateTexture2DSet(
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
		FTexture2DRHIRef& OutShaderResourceTexture);

	FNibiruVRHMDTexture2DSet(
		class FOpenGLDynamicRHI* InGLRHI,
		//GLuint InResource,
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
		uint32 InTargetableTexureFlags
	);

	virtual ~FNibiruVRHMDTexture2DSet();

	void SwitchToNextElement();
	void SetIndexAsCurrentRenderTarget();
	GLuint GetRenderTargetResource();

protected:
	FNibiruVRHMDTexture2DSet(const FNibiruVRHMDTexture2DSet &) = delete;
	FNibiruVRHMDTexture2DSet(FNibiruVRHMDTexture2DSet &&) = delete;
	FNibiruVRHMDTexture2DSet &operator=(const FNibiruVRHMDTexture2DSet &) = delete;

	enum { mkRenderTargetTextureNum = 3 };
	FTextureRHIRef    mRenderTargetTextureRHIRef[mkRenderTargetTextureNum];
	int                 mRenderTargetTextureRHIRefIndex;
};

class FNibiruVRHMDCustomPresent : public FXRRenderBridge
{
public:

	FNibiruVRHMDCustomPresent(FNibiruHMD* HMD);
	virtual ~FNibiruVRHMDCustomPresent();

	void Shutdown();

	nvr_frame* CurrentFrame;
	TRefCountPtr<FNibiruVRHMDTexture2DSet>   mTextureSet;
private:
	bool bUsesArrayTexture;
	FNibiruHMD* HMD;

	TQueue<nvr_mat4f> RenderingHeadPoseQueue;

	nvr_mat4f CurrentFrameRenderHeadPose;
	const nvr_buffer_viewport_list* CurrentFrameViewportList;
protected:
	FThreadSafeCounter						SubmitFrameLocker;
public:

	/**
	* Allocates a render target texture.
	*
	* @param Index			(in) index of the buffer, changing from 0 to GetNumberOfBufferedFrames()
	* @return				true, if texture was allocated; false, if the default texture allocation should be used.
	*/
	bool AllocateRenderTargetTexture(uint32 Index, uint32 SizeX, uint32 SizeY, uint8 Format, uint32 NumMips, uint32 InFlags, uint32 TargetableTextureFlags, FTexture2DRHIRef& OutTargetableTexture, FTexture2DRHIRef& OutShaderResourceTexture, uint32 NumSamples);

	void BeginRendering(uint32 frameNum, const nvr_mat4f& RenderingHeadPose);
	void FinishRendering();

	void EnterVRMode_RenderThread();
	void LeaveVRMode_RenderThread();

public:

	///////////////////////////////////////
	// Begin FRHICustomPresent Interface //
	///////////////////////////////////////

	// Called when viewport is resized.
	virtual void OnBackBufferResize() override;

	// Called from render thread to see if a native present will be requested for this frame.
	// @return	true if native Present will be requested for this frame; false otherwise.  Must
	// match value subsequently returned by Present for this frame.
	virtual bool NeedsNativePresent() override;

	// @param InOutSyncInterval - in out param, indicates if vsync is on (>0) or off (==0).
	// @return	true if normal Present should be performed; false otherwise. If it returns
	// true, then InOutSyncInterval could be modified to switch between VSync/NoVSync for the normal Present.
	virtual bool Present(int32& InOutSyncInterval) override;
};
// custom present
#endif

/**
 * Nibiru Head Mounted Display
 */
class FNibiruHMD : public FHeadMountedDisplayBase, public FXRRenderTargetManager, public IXRInput, public FSceneViewExtensionBase
{
public:

	/** Get preview viewer stereo projection matrix */
	static FMatrix GetPreviewViewerStereoProjectionMatrix(enum EStereoscopicPass StereoPass);

	/** IHeadMountedDisplay interface */
	virtual FName GetSystemName() const override
	{
		static FName DefaultName(TEXT("FNibiruHMD"));
		return DefaultName;
	}

	/**
	* Allocates a render target texture.
	*
	* @param Index			(in) index of the buffer, changing from 0 to GetNumberOfBufferedFrames()
	* @return				true, if texture was allocated; false, if the default texture allocation should be used.
	*/
	virtual bool AllocateRenderTargetTexture(uint32 Index, uint32 SizeX, uint32 SizeY, uint8 Format, uint32 NumMips, uint32 Flags, uint32 TargetableTextureFlags, FTexture2DRHIRef& OutTargetableTexture, FTexture2DRHIRef& OutShaderResourceTexture, uint32 NumSamples = 1) override;
	virtual uint32 GetNumberOfBufferedFrames() const { return 1; }

	// IHeadMountedDisplay
	/**
	 * Returns whether HMDDistortion post processing should be enabled or not.
	 */
	virtual bool GetHMDDistortionEnabled(EShadingPath ShadingPath) const override;
	virtual bool IsHMDConnected() override { return true; }
	virtual bool IsHMDEnabled() const override;
	virtual void EnableHMD(bool allow = true) override;
	virtual bool GetHMDMonitorInfo(MonitorInfo&) override;

	virtual void GetFieldOfView(float& OutHFOVInDegrees, float& OutVFOVInDegrees) const override;

	// IXRTrackingSystem
	/**
	 * If the device id represents a head mounted display, fetches the relative position of the given eye relative to the eye.
	 * If the device is does not represent a stereoscopic tracked camera, orientation and position should be identity and zero and the return value should be false.
	 *
	 * @param DeviceId the device to request the eye pose for.
	 * @param Eye the eye the pose should be requested for, if passing in any other value than eSSP_LEFT_EYE or eSSP_RIGHT_EYE, the method should return a zero offset.
	 * @param OutOrientation The orientation of the eye relative to the device orientation.
	 * @param OutPosition The position of the eye relative to the tracked device
	 * @return true if the pose is valid or not. If the device is not a stereoscopic device, return false.
	 */
	virtual bool GetRelativeEyePose(int32 DeviceId, EStereoscopicPass Eye, FQuat& OutOrientation, FVector& OutPosition) override;

	virtual bool DoesSupportPositionalTracking() const override;

	virtual void SetInterpupillaryDistance(float NewInterpupillaryDistance) override;
	virtual float GetInterpupillaryDistance() const override;

	virtual bool IsChromaAbCorrectionEnabled() const override;

	virtual void ResetOrientationAndPosition(float yaw = 0.f) override;
	virtual void ResetOrientation(float Yaw = 0.f) override;

	virtual void SetBaseRotation(const FRotator& BaseRot) override;
	virtual FRotator GetBaseRotation() const override;

	virtual void SetBaseOrientation(const FQuat& BaseOrient) override;
	virtual FQuat GetBaseOrientation() const override;

	virtual void DrawDistortionMesh_RenderThread(struct FRenderingCompositePassContext& Context, const FIntPoint& TextureSize) override;

	/**
	* This method is called when new game frame begins (called on a game thread).
	*/
	virtual bool OnStartGameFrame(FWorldContext& WorldContext) override;
	virtual bool OnEndGameFrame(FWorldContext& WorldContext) override;

	/**
	 * Called on the game thread when view family is about to be rendered.
	 */
	virtual void OnBeginRendering_GameThread() override;

	/**
	 * Called on the render thread at the start of rendering.
	 */
	virtual void OnBeginRendering_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneViewFamily& ViewFamily) override;

	// Begin IStereoRendering Virtual Interface //

	/** IStereoRendering interface */
	virtual bool IsStereoEnabled() const override;
	virtual bool EnableStereo(bool stereo = true) override;
	virtual void AdjustViewRect(EStereoscopicPass StereoPass, int32& X, int32& Y, uint32& SizeX, uint32& SizeY) const override;
 
	/**
	* Gets a projection matrix for the device, given the specified eye setup
	*/
	virtual FMatrix GetStereoProjectionMatrix(const enum EStereoscopicPass StereoPassType) const override;

	virtual void GetEyeRenderParams_RenderThread(const struct FRenderingCompositePassContext& Context, FVector2D& EyeToSrcUVScaleValue, FVector2D& EyeToSrcUVOffsetValue) const override;

    // Whether separate render target should be used or not.
	virtual bool ShouldUseSeparateRenderTarget() const override;
	
	// Renders texture into a backbuffer. Could be empty if no rendertarget texture is used, or if direct-rendering
	// through RHI bridge is implemented.
#if ENGINE_MINOR_VERSION >= 24
	virtual void RenderTexture_RenderThread(FRHICommandListImmediate& RHICmdList, FRHITexture2D* BackBuffer, FRHITexture2D* SrcTexture, FVector2D WindowSize) const override;
#else
	virtual void RenderTexture_RenderThread(FRHICommandListImmediate& RHICmdList, FTexture2DRHIParamRef BackBuffer, FTexture2DRHIParamRef SrcTexture, FVector2D WindowSize) const override;
#endif

	virtual IStereoRenderTargetManager* GetRenderTargetManager() override { return this; }

	/**
	* Calculates dimensions of the render target texture for direct rendering of distortion.
	*/
	virtual void CalculateRenderTargetSize(const class FViewport& Viewport, uint32& InOutSizeX, uint32& InOutSizeY) override;
	
	//Unreal Engine version 4.22.3
	//////////////////////////////////////////////////////
	// Begin IXRTrackingSystem Pure-Virtual Interface //
	//////////////////////////////////////////////////////

	virtual bool EnumerateTrackedDevices(TArray<int32>& OutDevices, EXRTrackedDeviceType Type = EXRTrackedDeviceType::Any) override;

	//////////////////////////////////////////////////////
	// Begin IHeadMountedDisplay Pure-Virtual Interface //
	//////////////////////////////////////////////////////

	virtual class IHeadMountedDisplay* GetHMDDevice() override { return this; }

	/**
	 * Access optional HMD input override interface.
	 *
	 * @return a IXRInput pointer or a nullptr if not supported
	*/
	virtual IXRInput* GetXRInput() { return this; }

	/**
	 * Passing key events to HMD.
	 * If returns 'false' then key will be handled by PlayerController;
	 * otherwise, key won't be handled by the PlayerController.
	*/
	virtual bool HandleInputKey(class UPlayerInput*, const struct FKey& Key, enum EInputEvent EventType, float AmountDepressed, bool bGamepad) override;

	/**
	 * Passing touch events to HMD.
	 * If returns 'false' then touch will be handled by PlayerController;
	 * otherwise, touch won't be handled by the PlayerController.
	*/
	// virtual bool HandleInputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, FDateTime DeviceTimestamp, uint32 TouchpadIndex) override;


	virtual class TSharedPtr< class IStereoRendering, ESPMode::ThreadSafe > GetStereoRenderingDevice() override 
	{ return SharedThis(this); }

	////////////////////////////////////////////
	// Begin FXRRenderTargetManager Interface //
	////////////////////////////////////////////

	/**
	 * Returns an instance of the currently active render bridge (aka. custom present)
	 */
	virtual FXRRenderBridge* GetActiveRenderBridge_GameThread(bool bUseSeparateRenderTarget) override;

	// This view extension should only be allowed when stereo is enabled.
	virtual bool IsActiveThisFrame(class FViewport* InViewport) const override;
	/** ISceneViewExtension interface */
	virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override;
	virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override;
	virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;
	virtual void PreRenderView_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneView& InView) override;
	virtual void PreRenderViewFamily_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneViewFamily& InViewFamily) override;
	
public:
	/** Constructor */
	FNibiruHMD(const FAutoRegister&);

	/** Destructor */
	virtual ~FNibiruHMD();

	void Shutdown();

	/** @return	True if the HMD was initialized OK */
	bool IsInitialized() const;
 
	/** Update head pose, Should be called at the beginning of a frame**/
	void UpdateNibiruHeadPose();

	/** Set RenderTarget size to the default size and return the value. */
	FIntPoint SetRenderTargetSizeToDefault();

	/** Get the RenderTarget size NibiruVRHMD is using for rendering the scene. */
	FIntPoint GetNVRHMDRenderTargetSize();
	
	virtual bool GetCurrentPose(int32 DeviceId, FQuat& OutOrientation, FVector& OutPosition) override;

	/**
	* Returns version string.
	*/
	virtual FString GetVersionString() const override;

	/** Check which method distortion correction is using */
	bool IsUsingNVRApiDistortionCorrection() const;

	/** Change whether distortion correction is performed by NVR Api, or PostProcessHMD. Only supported on-device. */
	void SetDistortionCorrectionMethod(bool bUseNVRApiDistortionCorrection);

	void RegisterNibiruKeyEventCallBack(FNibiruKeyEventCallbackDelegate OnNibiruKeyEventCallback);

	void SetGazeEnabled(bool enabled);

	void SetGazePosZ(float z);

#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	FXRRenderBridge* CustomPresent;

	int GetViewNum() {
		return viewNumber;
	}

	FVector GetCachedFinalHeadPosition()
	{
		return CachedFinalHeadPosition;
	}
#endif

	bool bBeginFrame = false;

	void NotifyKeyEvent(int keyCode, int keyAction);

	ESixDofMode GetSixDofMode();

	void RequestQuitGame();

	int GetVerifyStatus();

	void UpdateVerifyStatus(int status);
private:
	// 是否支持获取6dof数据接口
	bool IsSpt6DofDataApi = false;
	ESixDofMode SixDofMode = ESixDofMode::Head_6DOF_Ctrl_6DOF;
	bool useDTRMode = false;

	FNibiruKeyEventCallbackDelegate myNibiruKeyEventCallback;

	/** Refresh RT so screen isn't black */
	void ApplicationResumeDelegate();
	void ApplicationPauseDelegate();

#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
	int viewNumber;
	float profileData[17];
	
	mutable nvr_mat4f CachedHeadPose;
	mutable FQuat CachedFinalHeadRotation;
	mutable FVector CachedFinalHeadPosition; 
#endif
	int VerifyStatus = -1;
 
	// Simulation data for previewing
	float PosePitch;
	float PoseYaw;

	// distortion mesh
	uint32 DistortionPointsX;
	uint32 DistortionPointsY;
	uint32 NumVerts;
	uint32 NumTris;
	uint32 NumIndices;

	FQuat		BaseOrientation;
 
    IRendererModule* RendererModule;

	FIntPoint NVRRenderTargetSize;
	FIndexBufferRHIRef DistortionMeshIndices;
	FVertexBufferRHIRef DistortionMeshVerticesLeftEye;
	FVertexBufferRHIRef DistortionMeshVerticesRightEye;

	// Drawing Data End
	FQuat					CurHmdOrientation;
	FVector		        CurHmdPosition;

	FRotator				DeltaControlRotation;    // same as DeltaControlOrientation but as rotator
	FQuat					DeltaControlOrientation; // same as DeltaControlRotation but as quat

	double					LastSensorTime;

	bool		bUseNVRApiDistortionCorrection;

	bool        bEnableMultiView;

	void GenerateDistortionCorrectionIndexBuffer();

	/** Helper method to generate vertex buffer for manual distortion rendering */
	void GenerateDistortionCorrectionVertexBuffer(EStereoscopicPass Eye);

	/** Generates Distortion Correction Points*/
	void SetNumOfDistortionPoints(int32 XPoints, int32 YPoints);

	/** Generates a new distortion mesh of the given size */
	void SetDistortionMeshSize(EDistortionMeshSizeEnum MeshSize);

	/** Get how many Unreal units correspond to one meter in the real world */
	float GetWorldToMetersScale() const;

	/** Handle letting application know about GVR back event */
	void HandleNVRBackEvent();
};
