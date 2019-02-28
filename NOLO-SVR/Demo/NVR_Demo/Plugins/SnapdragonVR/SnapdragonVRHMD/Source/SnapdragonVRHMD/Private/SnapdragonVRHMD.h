//=============================================================================
// FILE: SnapdragonVRHMD.h
//
//                  Copyright (c) 2016 QUALCOMM Technologies Inc.
//                              All Rights Reserved.
//
//=============================================================================

#pragma once

#include "CoreMinimal.h"
#include "HeadMountedDisplayBase.h"
#include "XRRenderTargetManager.h"
#include "SceneViewExtension.h"
#include "ISnapdragonVRHMDPlugin.h"
//#include "XRRenderBridge.h"
#include "Queue.h"
#include "CircularBuffer.h"
#include "SnapdragonVRLog.h"

#if SNAPDRAGONVR_SUPPORTED_PLATFORMS
#include "svrApi.h"
#include "SceneViewExtension.h"

#include "OpenGLDrvPrivate.h"//unfortunately, OpenGLResources.h does not stand alone, but requires files #included'd ahead of it
#include "OpenGLResources.h"
#include"nolo_api.h"
#include "../../NoloVR/Private/NoloVRHMD.h"

DEFINE_LOG_CATEGORY_STATIC(LogSVR, Log, All);

template<typename ElementType> class FCircularQueue
{
public:

	/**
	* Default constructor.
	*
	* @param Size The number of elements that the queue can hold (will be rounded up to the next power of 2).
	*/
	FCircularQueue(uint32 Size)
		: Buffer(Size)
		, Head(0)
		, Tail(0)
	{ }

	/** Virtual destructor. */
	virtual ~FCircularQueue() { }

public:

	/**
	* Gets the number of elements in the queue.
	*
	* @return Number of queued elements.
	*/
	uint32 Count() const
	{
		int32 Count = Tail - Head;

		if (Count < 0)
		{
			Count += Buffer.Capacity();
		}

		return Count;
	}

	/**
	* Removes an item from the front of the queue.
	*
	* @param OutElement Will contain the element if the queue is not empty.
	* @return true if an element has been returned, false if the queue was empty.
	*/
	bool Dequeue(ElementType& OutElement)
	{
		if (Head != Tail)
		{
			OutElement = Buffer[Head];
			Head = Buffer.GetNextIndex(Head);

			return true;
		}

		return false;
	}

	/**
	* Empties the queue.
	*
	* @see IsEmpty
	*/
	void Empty()
	{
		Head = Tail;
	}

	/**
	* Adds an item to the end of the queue.
	*
	* @param Element The element to add.
	* @return true if the item was added, false if the queue was full.
	*/
	bool Enqueue(const ElementType& Element)
	{
		uint32 NewTail = Buffer.GetNextIndex(Tail);

		if (NewTail != Head)
		{
			Buffer[Tail] = Element;
			Tail = NewTail;

			return true;
		}

		return false;
	}

	/**
	* Checks whether the queue is empty.
	*
	* @return true if the queue is empty, false otherwise.
	* @see Empty, IsFull
	*/
	FORCEINLINE bool IsEmpty() const
	{
		return (Head == Tail);
	}

	/**
	* Checks whether the queue is full.
	*
	* @return true if the queue is full, false otherwise.
	* @see IsEmpty
	*/
	bool IsFull() const
	{
		return (Buffer.GetNextIndex(Tail) == Head);
	}

	/**
	* Returns the oldest item in the queue without removing it.
	*
	* @param OutItem Will contain the item if the queue is not empty.
	* @return true if an item has been returned, false if the queue was empty.
	*/
	bool Peek(ElementType& OutItem)
	{
		if (Head != Tail)
		{
			OutItem = Buffer[Head];

			return true;
		}

		return false;
	}

	ElementType* Get()
	{
		if (Head != Tail)
		{
			return &Buffer[Head];
		}

		return nullptr;
	}

	ElementType* CurrentPtr()
	{
		if (Head != Tail)
		{
			return &Buffer[Tail];
		}

		return nullptr;
	}

	bool Current(ElementType& OutItem)
	{
		if (Head != Tail)
		{
			OutItem = Buffer[Tail];

			return true;
		}

		return false;
	}

private:

	/** Holds the buffer. */
	TCircularBuffer<ElementType> Buffer;

	/** Holds the index to the first item in the buffer. */
	MS_ALIGN(PLATFORM_CACHE_LINE_SIZE) volatile uint32 Head GCC_ALIGN(PLATFORM_CACHE_LINE_SIZE);

	/** Holds the index to the last item in the buffer. */
	MS_ALIGN(PLATFORM_CACHE_LINE_SIZE) volatile uint32 Tail GCC_ALIGN(PLATFORM_CACHE_LINE_SIZE);
};

class FSnapdragonVRHMD;

class FSnapdragonVRHMDTextureSet:public FOpenGLTexture2D
{
public:
    static FSnapdragonVRHMDTextureSet* CreateTexture2DSet(
        FOpenGLDynamicRHI* InGLRHI,
        uint32 SizeX, 
        uint32 SizeY,
        uint32 InNumSamples,
        EPixelFormat InFormat,
        uint32 InFlags);

    FSnapdragonVRHMDTextureSet(
        class FOpenGLDynamicRHI* InGLRHI,
        GLuint InResource,
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
        uint8* InTextureRange);

    virtual ~FSnapdragonVRHMDTextureSet() override;

    void SwitchToNextElement();
    void SetIndexAsCurrentRenderTarget();
    GLuint GetRenderTargetResource();
	FTexture2DRHIRef GetRenderTarget();
private:

    FSnapdragonVRHMDTextureSet(const FSnapdragonVRHMDTextureSet &) = delete;
    FSnapdragonVRHMDTextureSet(FSnapdragonVRHMDTextureSet &&) = delete;
    FSnapdragonVRHMDTextureSet &operator=(const FSnapdragonVRHMDTextureSet &) = delete;

    enum { mkRenderTargetTextureNum = 3 };
    FTexture2DRHIRef    mRenderTargetTexture2DHIRef[mkRenderTargetTextureNum];
    int                 mRenderTargetTexture2DHIRefIndex;
};

class FSnapdragonVRHMDCustomPresent : public FRHICustomPresent
{
    friend class FViewExtension;
    friend class FSnapdragonVRHMD;

	enum 
	{
		kMaxPoseHistoryLength = 8
	};

public:
    // FRHICustomPresent
	virtual bool NeedsNativePresent() override; //D3D12 only now, not mobile.
    virtual void OnBackBufferResize() override;
    virtual bool Present(int32& InOutSyncInterval) override;
    //FSnapdragonVRHMDCustomPresent
    FSnapdragonVRHMDCustomPresent(FSnapdragonVRHMD* pHMD);
    void BeginRendering(FRHICommandListImmediate& RHICmdList, FSceneViewFamily& InViewFamily);
    void FinishRendering();
    void UpdateViewport(const FViewport& Viewport, FRHIViewport* InViewportRHI);
    void DoBeginVR();
    void DoEndVR();
    bool AllocateRenderTargetTexture(
        uint32 SizeX, 
        uint32 SizeY, 
        uint8 Format, 
        uint32 NumMips, 
        uint32 Flags, 
        uint32 TargetableTextureFlags, 
        FTexture2DRHIRef& OutTargetableTexture, 
        FTexture2DRHIRef& OutShaderResourceTexture, 
        uint32 NumSamples);

public:
	static FCriticalSection InVRModeCriticalSection;
	static FCriticalSection	PerfLevelCriticalSection;
    bool                bInVRMode;
    bool                bContextInitialized;

    struct FPoseStateFrame
    {
        svrHeadPoseState Pose;
        uint64 FrameNumber;
    };

    bool PoseIsEmpty();

	FCircularQueue<FPoseStateFrame> PoseHistory;

private:

	TRefCountPtr<FSnapdragonVRHMDTextureSet> mTextureSet;
};


class FSnapdragonVRHMD : public FHeadMountedDisplayBase, public FXRRenderTargetManager, public FSceneViewExtensionBase
{

	FNoloVRHMD* GetNoloVRHMD() const
	{
		FNoloVRHMD* noloVR;
		TArray<INoloVRDevice*> NoloVRDevices = IModularFeatures::Get().GetModularFeatureImplementations<INoloVRDevice>(INoloVRDevice::GetModularFeatureName());

		for (auto NoloVRDevice : NoloVRDevices)
		{
			//UE_LOG(LogTemp, Log, TEXT("==============NoloVRDevice===%d=============\n"), NoloVRDevice->getFlag());
			if (NoloVRDevice != nullptr)
			{
				noloVR = static_cast<FNoloVRHMD*>(NoloVRDevice);
				if (noloVR != nullptr) {
					//UE_LOG(LogTemp, Log, TEXT("============== noloVR->test===%d=====%d=====%d=====%x=\n"), noloVR->test(), noloVR->test2(), noloVR->test3(),noloVR);
					return noloVR;
				}
			}
		}
		return nullptr;
	}
public:

	// IXRSystemIdentifier
	virtual FName GetSystemName() const override
	{
		LOG_FUNC();
		static FName DefaultName(TEXT("FSnapdragonVRHMD"));
		return DefaultName;
	}
	/** IHeadMountedDisplay interface */
	virtual bool IsHMDConnected() override { return true; }
	virtual bool IsHMDEnabled() const override;
	virtual bool GetHMDMonitorInfo(MonitorInfo&) override;
	virtual void GetEyeRenderParams_RenderThread(const struct FRenderingCompositePassContext& Context, FVector2D& EyeToSrcUVScaleValue, FVector2D& EyeToSrcUVOffsetValue) const override;
	virtual void SetInterpupillaryDistance(float NewInterpupillaryDistance) override;
	virtual float GetInterpupillaryDistance() const override;
	virtual bool GetHMDDistortionEnabled(EShadingPath ShadingPath) const override;
	virtual void OnLateUpdateApplied_RenderThread(const FTransform& NewRelativeTransform) override {  FHeadMountedDisplayBase::OnLateUpdateApplied_RenderThread(NewRelativeTransform); }
	virtual float GetPixelDenity() const { return PixelDensity; }
	virtual void SetPixelDensity(const float NewDensity) { PixelDensity = NewDensity; }
	virtual FIntPoint GetIdealRenderTargetSize() const override;
	virtual bool IsChromaAbCorrectionEnabled() const override;
	virtual bool HasHiddenAreaMesh() const override {  return false; }
	virtual bool HasVisibleAreaMesh() const override {  return false; }
	virtual void DrawDistortionMesh_RenderThread(struct FRenderingCompositePassContext& Context, const FIntPoint& TextureSize) override;
	virtual void UpdateScreenSettings(const class FViewport* InViewport) override {  }
	virtual void UpdatePostProcessSettings(FPostProcessSettings*) override {  }
	virtual bool NeedsUpscalePostProcessPass() override {  return false; }
	virtual void RecordAnalytics() override {  FHeadMountedDisplayBase::RecordAnalytics(); }
	

	/** IHeadMountedDisplay interface not used*/
	virtual void GetFieldOfView(float& OutHFOVInDegrees, float& OutVFOVInDegrees) const override;
	virtual void EnableHMD(bool allow = true) override;
	virtual void SetClippingPlanes(float NCP, float FCP) override { }
	//virtual class ISpectatorScreenController* GetSpectatorScreenController() override { return FHeadMountedDisplayBase::GetSpectatorScreenController(); }
	//virtual class ISpectatorScreenController const* GetSpectatorScreenController() const override { return FHeadMountedDisplayBase::GetSpectatorScreenController(); }
	//virtual float GetDistortionScalingFactor() const override { return 0; }
	//virtual float GetLensCenterOffset() const override { return 0; }
	//virtual void GetDistortionWarpValues(FVector4& K) const override { }
	//virtual bool GetChromaAbCorrectionValues(FVector4& K) const override { return false; }
	virtual void DrawHiddenAreaMesh_RenderThread(class FRHICommandList& RHICmdList, EStereoscopicPass StereoPass) const override { }
	virtual void DrawVisibleAreaMesh_RenderThread(class FRHICommandList& RHICmdList, EStereoscopicPass StereoPass) const override { }
	//virtual FTexture* GetDistortionTextureLeft() const override { return NULL; }
	//virtual FTexture* GetDistortionTextureRight() const override { return NULL; }
	//virtual FVector2D GetTextureOffsetLeft() const override { return FVector2D::ZeroVector; }
	//virtual FVector2D GetTextureOffsetRight() const override { return FVector2D::ZeroVector; }
	//virtual FVector2D GetTextureScaleLeft() const override { return FVector2D::ZeroVector; }
	//virtual FVector2D GetTextureScaleRight() const override { return FVector2D::ZeroVector; }
	//virtual const float* GetRedDistortionParameters() const override { return nullptr; }
	//virtual const float* GetGreenDistortionParameters() const override { return nullptr; }
	//virtual const float* GetBlueDistortionParameters() const override { return nullptr; }
	//virtual bool DoesAppUseVRFocus() const override { return IHeadMountedDisplay::DoesAppUseVRFocus(); }
	//virtual bool DoesAppHaveVRFocus() const override { return IHeadMountedDisplay::DoesAppHaveVRFocus(); }
	virtual EHMDWornState::Type GetHMDWornState() override { return EHMDWornState::Unknown; }
	virtual bool PopulateAnalyticsAttributes(TArray<struct FAnalyticsEventAttribute>& EventAttributes) override { return FHeadMountedDisplayBase::PopulateAnalyticsAttributes(EventAttributes); }
	virtual FTexture2DRHIRef GetOverlayLayerTarget_RenderThread(EStereoscopicPass StereoPass, FIntRect& InOutViewport) override { return nullptr; }
	virtual FTexture2DRHIRef GetSceneLayerTarget_RenderThread(EStereoscopicPass StereoPass, FIntRect& InOutViewport) override { return nullptr; }

	//** FHeadMountedDisplayBase interface not used*/
	virtual FVector2D GetEyeCenterPoint_RenderThread(EStereoscopicPass Eye) const override { return FHeadMountedDisplayBase::GetEyeCenterPoint_RenderThread(Eye); }
	virtual FIntRect GetFullFlatEyeRect_RenderThread(FTexture2DRHIRef EyeTexture) const override { return FHeadMountedDisplayBase::GetFullFlatEyeRect_RenderThread(EyeTexture); }
	virtual void CopyTexture_RenderThread(FRHICommandListImmediate& RHICmdList, FTexture2DRHIParamRef SrcTexture, FIntRect SrcRect, FTexture2DRHIParamRef DstTexture, FIntRect DstRect, bool bClearBlack) const { FHeadMountedDisplayBase::CopyTexture_RenderThread(RHICmdList, SrcTexture, SrcRect, DstTexture, DstRect, bClearBlack);}

	/** IXRTrackingSystem interface */
	virtual bool DoesSupportLateUpdate() const { return false; }
	virtual bool GetCurrentPose(int32 DeviceId, FQuat& OutOrientation, FVector& OutPosition) override;
	virtual bool GetRelativeEyePose(int32 DeviceId, EStereoscopicPass Eye, FQuat& OutOrientation, FVector& OutPosition) override;
	virtual FTransform GetTrackingToWorldTransform() const override { return FXRTrackingSystemBase::GetTrackingToWorldTransform(); }
	virtual void UpdateTrackingToWorldTransform(const FTransform& TrackingToWorldOverride) override { return FXRTrackingSystemBase::UpdateTrackingToWorldTransform(TrackingToWorldOverride); }
	virtual FVector GetAudioListenerOffset(int32 DeviceId = HMDDeviceId) const override { return IXRTrackingSystem::GetAudioListenerOffset(); }
	virtual class TSharedPtr< class IXRCamera, ESPMode::ThreadSafe > GetXRCamera(int32 DeviceId = HMDDeviceId) override { return FXRTrackingSystemBase::GetXRCamera(DeviceId); }
	virtual class TSharedPtr< class IStereoRendering, ESPMode::ThreadSafe > GetStereoRenderingDevice() override { return SharedThis(this); }
	virtual IXRInput* GetXRInput() override { return IXRTrackingSystem::GetXRInput(); }
	virtual bool IsHeadTrackingAllowed() const override;
	virtual void OnBeginPlay(FWorldContext& InWorldContext) override { }
	virtual void OnEndPlay(FWorldContext& InWorldContext) override;
	virtual bool OnStartGameFrame(FWorldContext& WorldContext) override;
	virtual bool OnEndGameFrame(FWorldContext& WorldContext) override {
		SendEvents(); 
		return true;
	}
	virtual void OnBeginRendering_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneViewFamily& ViewFamily) { }
	virtual void OnBeginRendering_GameThread() { }

	/** IXRTrackingSystem interface not used*/
	virtual FString GetVersionString() const override {  return FString(TEXT("GenericHMD")); }
	virtual bool DoesSupportPositionalTracking() const override;
	virtual bool HasValidTrackingPosition() override;
	virtual bool EnumerateTrackedDevices(TArray<int32>& OutDevices, EXRTrackedDeviceType Type = EXRTrackedDeviceType::Any) override;
	virtual uint32 CountTrackedDevices(EXRTrackedDeviceType Type = EXRTrackedDeviceType::Any) override {  return FXRTrackingSystemBase::CountTrackedDevices(Type); }
	virtual bool IsTracking(int32 DeviceId) override {  return FXRTrackingSystemBase::IsTracking(DeviceId); }
	virtual void RebaseObjectOrientationAndPosition(FVector& OutPosition, FQuat& OutOrientation) const override {  }
	virtual bool GetTrackingSensorProperties(int32 DeviceId, FQuat& OutOrientation, FVector& OutPosition, FXRSensorProperties& OutSensorProperties) override {  return false; }
	virtual void SetTrackingOrigin(EHMDTrackingOrigin::Type NewOrigin) override;
	virtual EHMDTrackingOrigin::Type GetTrackingOrigin() override;

	virtual void ResetOrientationAndPosition(float yaw = 0.f) override;
	virtual void ResetOrientation(float Yaw = 0.f) override;
	virtual void ResetPosition() override;
	virtual void SetBaseRotation(const FRotator& BaseRot) override;
	virtual FRotator GetBaseRotation() const override;
	virtual void SetBaseOrientation(const FQuat& BaseOrient) override;
	virtual FQuat GetBaseOrientation() const override;
	virtual class IHeadMountedDisplay* GetHMDDevice() override { return this; }

	/** FXRTrackingSystemBase interface not used*/
	virtual float GetWorldToMetersScale() const override;

	/** IStereoRenderTargetManager interface */
	virtual bool ShouldUseSeparateRenderTarget() const override;
	//virtual void UpdateViewport(bool bUseSeparateRenderTarget, const class FViewport& Viewport, class SViewport* ViewportWidget = nullptr) override;
	virtual void CalculateRenderTargetSize(const class FViewport& Viewport, uint32& InOutSizeX, uint32& InOutSizeY) override;
	virtual bool NeedReAllocateViewportRenderTarget(const class FViewport& Viewport) override;
	virtual bool NeedReAllocateDepthTexture(const TRefCountPtr<struct IPooledRenderTarget>& DepthTarget) { return false; }
	virtual uint32 GetNumberOfBufferedFrames() const override { return 1; }
	virtual bool AllocateRenderTargetTexture(uint32 Index, uint32 SizeX, uint32 SizeY, uint8 Format, uint32 NumMips, uint32 Flags, uint32 TargetableTextureFlags, FTexture2DRHIRef& OutTargetableTexture, FTexture2DRHIRef& OutShaderResourceTexture, uint32 NumSamples = 1) override;
	virtual bool AllocateDepthTexture(uint32 Index, uint32 SizeX, uint32 SizeY, uint8 Format, uint32 NumMips, uint32 Flags, uint32 TargetableTextureFlags, FTexture2DRHIRef& OutTargetableTexture, FTexture2DRHIRef& OutShaderResourceTexture, uint32 NumSamples = 1) { return false; }

	/** FXRRenderTargetManager interface */
	virtual void UpdateViewportWidget(bool bUseSeparateRenderTarget, const class FViewport& Viewport, class SViewport* ViewportWidget) override { }
	virtual void UpdateViewportRHIBridge(bool bUseSeparateRenderTarget, const class FViewport& Viewport, FRHIViewport* const ViewportRHI) override;
	
	/** IStereoRendering interface */
	virtual bool IsStereoEnabled() const override;
	virtual bool IsStereoEnabledOnNextFrame() const override {  return IsStereoEnabled(); }
	virtual bool EnableStereo(bool stereo = true) override;
	virtual int32 GetDesiredNumberOfViews(bool bStereoRequested) const override {  return IStereoRendering::GetDesiredNumberOfViews(bStereoRequested); }
	virtual EStereoscopicPass GetViewPassForIndex(bool bStereoRequested, uint32 ViewIndex) const override {  return IStereoRendering::GetViewPassForIndex(bStereoRequested, ViewIndex); }
	virtual bool IsStereoEyePass(EStereoscopicPass Pass) override {  return IStereoRendering::IsStereoEyePass(Pass); }
	virtual void AdjustViewRect(EStereoscopicPass StereoPass, int32& X, int32& Y, uint32& SizeX, uint32& SizeY) const override;
	virtual void SetFinalViewRect(const enum EStereoscopicPass StereoPass, const FIntRect& FinalViewRect) override;
	virtual FVector2D GetTextSafeRegionBounds() const override {  return FVector2D(0.75f, 0.75f); }
	virtual void CalculateStereoViewOffset(const EStereoscopicPass StereoPassType, FRotator& ViewRotation, const float MetersToWorld, FVector& ViewLocation) override;
	virtual FMatrix GetStereoProjectionMatrix(const EStereoscopicPass StereoPassType) const override;
	virtual void InitCanvasFromView(FSceneView* InView, UCanvas* Canvas) override;
	virtual bool IsSpectatorScreenActive() const override {  return false;/*return FHeadMountedDisplayBase::IsSpectatorScreenActive();*/ } //UE do not support SpectatorScreen on mobile device now.
	virtual void RenderTexture_RenderThread(class FRHICommandListImmediate& RHICmdList, class FRHITexture2D* BackBuffer, class FRHITexture2D* SrcTexture, FVector2D WindowSize) const override {  }
	virtual void GetOrthoProjection(int32 RTWidth, int32 RTHeight, float OrthoDistance, FMatrix OrthoProjection[2]) const override {  IStereoRendering::GetOrthoProjection(RTWidth, RTHeight, OrthoDistance, OrthoProjection); }
	
	virtual FRHICustomPresent* GetCustomPresent() override;
	virtual IStereoRenderTargetManager* GetRenderTargetManager() override { return this; }
	//virtual IStereoLayers* GetStereoLayers() override {  return this; }

	/** ISceneViewExtension interface */
	virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override;
	virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override;
	virtual void SetupViewPoint(APlayerController* Player, FMinimalViewInfo& InViewInfo) override { }
	virtual void SetupViewProjectionMatrix(FSceneViewProjectionData& InOutProjectionData) override { }
	virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override { }
	virtual void PreRenderViewFamily_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneViewFamily& InViewFamily) override;
	virtual void PreRenderView_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneView& InView) override;
	virtual void PostRenderBasePass_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneView& InView) override { }
	virtual void PostRenderViewFamily_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneViewFamily& InViewFamily) override { }
	virtual void PostRenderView_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneView& InView) override { }
	virtual int32 GetPriority() const override { return 0; }
	virtual bool IsActiveThisFrame(class FViewport* InViewport) const override { return true; }

	void SetCPUAndGPULevels(const int32 InCPULevel, const int32 InGPULevel) const;
	void Shutdown();
public:
	FSnapdragonVRHMD(const FAutoRegister&);
	virtual ~FSnapdragonVRHMD();


	bool IsInitialized() const;
	static void PerfLevelLog(const TCHAR* const InPrefix, enum svrPerfLevel InPerfLevelCpu, enum svrPerfLevel InPerfLevelGpu);
	static bool PerfLevelsLastSetByCvarRead(
		enum svrPerfLevel* OutPerfLevelCpuCurrent, 
		enum svrPerfLevel* OutPerfLevelGpuCurrent, 
		const enum svrPerfLevel InPerfLevelCpuDefault,
		const enum svrPerfLevel InPerfLevelGpuDefault);
	static enum svrPerfLevel GetCVarSnapdragonVrPerfLevelDefault();
	static void PerfLevelCpuWrite(const enum svrPerfLevel InPerfLevel);
	static void PerfLevelGpuWrite(const enum svrPerfLevel InPerfLevel);
	static enum svrPerfLevel PerfLevelCpuLastSet, PerfLevelGpuLastSet;

private:
	void Startup();
	void InitializeIfNecessaryOnResume();
	void CleanupIfNecessary();

	void ApplicationWillEnterBackgroundDelegate();
	void ApplicationWillDeactivateDelegate();
	void ApplicationHasEnteredForegroundDelegate();
	void ApplicationHasReactivatedDelegate();

	void PoseToOrientationAndPosition(const svrHeadPose& Pose,FQuat& CurrentOrientation);

	void BeginVRMode();
	void EndVRMode();

	bool GetHeadPoseState(svrHeadPoseState* HeadPoseState);

	void SendEvents();

	void OnFEngineLoopInitComplete();
	void setDeviceSupportedMaxFPS();
	void ResetProjectionMats();
	bool IsStereoEnabledInternal() const;
private:
	bool bInitialized;
	bool bResumed;

	TRefCountPtr<FSnapdragonVRHMDCustomPresent> pSnapdragonVRBridge;

	bool InitializeExternalResources();

	//Temporary until svr pose is integrated
	FQuat					CurHmdOrientation;
	FQuat					LastHmdOrientation;
	FVector                 CurHmdPosition;
	FVector					LastHmdPosition;
    FRotator				DeltaControlRotation;    
    FQuat					DeltaControlOrientation; 
	double					LastSensorTime;

	FIntPoint				RenderTargetSize;
	FIntRect				EyeRenderViewport[2];

	float PixelDensity;
	SVR_PoseOriginModel Origin = SVR_PoseOriginModel::SVR_PoseOriginModel_OriginOnGround;
	bool bNeedReinitEGL;
	FMatrix* LeftProjection;
	FMatrix* RightProjection;
	bool bHmdEnabled;
	bool bStereoEnabled;
	//std::unique_ptr<nolovr::NoloVrApi> noloVrApi;
};




#endif //SNAPDRAGONVR_SUPPORTED_PLATFORMS
