//=============================================================================
// FILE: SnapdragonVRHMD.cpp
//
//                  Copyright (c) 2016 QUALCOMM Technologies Inc.
//                              All Rights Reserved.
//
//=============================================================================

#include "SnapdragonVRHMD.h"
#include "../Public/SnapdragonVRHMDFunctionLibrary.h"
#include "../Classes/SnapdragonVRHMDEventManager.h"

#include "RendererPrivate.h"
#include "ScenePrivate.h"
#include "SceneViewport.h"
#include "PostProcess/PostProcessHMD.h"

#include "GameFramework/PlayerController.h"
#include "GameFramework/WorldSettings.h"
#include "Engine/Canvas.h"
#include "Engine/World.h"
#include "Misc/CoreDelegates.h"
#include "Misc/EngineVersion.h"
#include "RunnableThread.h"

#if PLATFORM_ANDROID
/*
It appears that we must ensure that svrEndVr() (which is always called on the CPU thread) never overlaps with
svrSubmitFrame() (which is always called on the render thread) by mutexing bInVRMode in those cases.  Otherwise, we can
get mysterious deadlocks during suspend/resume (seemingly only if the phone is not plugged into USB!  Plugged in USB
phones never reproduced this deadlock).

It is equally important that we do *not* try to use this thread synchronization construct to guard against other times
bInVRMode is used (for example, at startup), or else a different mysterious deadlock on app launch occurs.  @todo NTF:
understand what's really going on here
*/
FCriticalSection FSnapdragonVRHMDCustomPresent::InVRModeCriticalSection;
FCriticalSection FSnapdragonVRHMDCustomPresent::PerfLevelCriticalSection;

#include <android_native_app_glue.h>

#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidEGL.h"
#endif // PLATFORM_ANDROID

#include "RHIStaticStates.h"
#include "SceneViewport.h"

#include "DrawDebugHelpers.h"

#if SNAPDRAGONVR_SUPPORTED_PLATFORMS
static const TCHAR* const svrPerfLevelSystemCStr = TEXT("sys");
static const TCHAR* const svrPerfLevelMinimumCStr = TEXT("min");
static const TCHAR* const svrPerfLevelMediumCStr = TEXT("med");
static const TCHAR* const svrPerfLevelMaximumCStr = TEXT("max");

//keep these two lines in sync (eg pass the string that corresponds to the enum)
static const TCHAR* const svrPerfLevelDefaultCStr = svrPerfLevelSystemCStr;
/*static*/ enum svrPerfLevel FSnapdragonVRHMD::GetCVarSnapdragonVrPerfLevelDefault() { return kPerfSystem; }

//these variables default values can be overridden by adding a line like this to Engine\Config\ConsoleVariables.ini: svr.perfCpu=max
static TAutoConsoleVariable<FString> CVarPerfLevelCpu(TEXT("svr.perfCpu"), svrPerfLevelDefaultCStr, TEXT("Set SnapdragonVr CPU performance consumption to one of the following: sys, min, med, max.  Note that if this value is set by Blueprint, the cvar will continue to report the last value it was set to, and will not reflect the value set by Blueprint"));
static TAutoConsoleVariable<FString> CVarPerfLevelGpu(TEXT("svr.perfGpu"), svrPerfLevelDefaultCStr, TEXT("Set SnapdragonVr GPU performance consumption to one of the following: sys, min, med, max.  Note that if this value is set by Blueprint, the cvar will continue to report the last value it was set to, and will not reflect the value set by Blueprint"));

//BEG_Q3D_AUDIO_HACK
#if !UE_BUILD_SHIPPING
static TAutoConsoleVariable<int32> CVarQ3D_DrawSound(TEXT("q3d.drawSound"), 0, TEXT("Draws red tetrahedrons centered at each spatialized sound's position (hurts performance significantly)"));
static TAutoConsoleVariable<int32> CVarQ3D_DrawSoundName(TEXT("q3d.drawSoundName"), 0, TEXT("Draws red textual names of spatialized sounds near their positions (hurts performance dramatically)"));
static TAutoConsoleVariable<int32> CVarQ3D_LogSoundName(TEXT("q3d.logSoundName"), 0, TEXT("Logs sound names and positions of spatialized sounds each frame"));
static TAutoConsoleVariable<int32> CVarQ3D_LogSoundNumber(TEXT("q3d.logSoundNumber"), 0, TEXT("Logs the number of spatialized sounds playing on a frame"));
#endif//#if !UE_BUILD_SHIPPING
//END_Q3D_AUDIO_HACK

static bool FStringToSvrPerfLevel(enum svrPerfLevel* OutPerfLevel, const FString& InValueReceived)
{
    if (InValueReceived.Compare(FString(svrPerfLevelSystemCStr, ESearchCase::IgnoreCase)) == 0)
    {
        *OutPerfLevel = kPerfSystem;
        return true;
    }
    else if (InValueReceived.Compare(FString(svrPerfLevelMinimumCStr, ESearchCase::IgnoreCase)) == 0)
    {
        *OutPerfLevel = kPerfMinimum;
        return true;
    }
    else if (InValueReceived.Compare(FString(svrPerfLevelMediumCStr, ESearchCase::IgnoreCase)) == 0)
    {
        *OutPerfLevel = kPerfMedium;
        return true;
    }
    else if (InValueReceived.Compare(FString(svrPerfLevelMaximumCStr, ESearchCase::IgnoreCase)) == 0)
    {
        *OutPerfLevel = kPerfMaximum;
        return true;
    }
    else
    {
        return false;
    }
}
static bool SvrPerfLevelToFString(FString* const OutPerfLevelFString, const enum svrPerfLevel InPerfLevel)
{
    switch (InPerfLevel)
    {
    case kPerfSystem:
    {
        *OutPerfLevelFString = FString(svrPerfLevelSystemCStr);
        return true;
    }
    case kPerfMinimum:
    {
        *OutPerfLevelFString = FString(svrPerfLevelMinimumCStr);
        return true;
    }
    case kPerfMedium:
    {
        *OutPerfLevelFString = FString(svrPerfLevelMediumCStr);
        return true;
    }
    case kPerfMaximum:
    {
        *OutPerfLevelFString = FString(svrPerfLevelMaximumCStr);
        return true;
    }
    default:
    {
        return false;
    }
    }
}

static bool IsPerfLevelValid(const enum svrPerfLevel InPerfLevel)
{
    return InPerfLevel >= kPerfSystem && InPerfLevel <= kPerfMaximum;
}

// CTORNE ->
/*static*/ enum svrPerfLevel FSnapdragonVRHMD::PerfLevelCpuLastSet = kPerfMaximum, FSnapdragonVRHMD::PerfLevelGpuLastSet = kPerfMaximum;
// <- CTORNE
/*static*/ void PerfLevelLastSet(enum svrPerfLevel* const OutPerfLevel, const enum svrPerfLevel InPerfLevel)
{
	check(IsPerfLevelValid(InPerfLevel));
	*OutPerfLevel = InPerfLevel;
}
/*static*/ void FSnapdragonVRHMD::PerfLevelCpuWrite(const enum svrPerfLevel InPerfLevel)
{
	PerfLevelLastSet(&PerfLevelCpuLastSet, InPerfLevel);
}
/*static*/ void FSnapdragonVRHMD::PerfLevelGpuWrite(const enum svrPerfLevel InPerfLevel)
{
	PerfLevelLastSet(&PerfLevelGpuLastSet, InPerfLevel);
}
/*static*/ void FSnapdragonVRHMD::PerfLevelLog(const TCHAR* const InPrefix, enum svrPerfLevel InPerfLevelCpu, enum svrPerfLevel InPerfLevelGpu)
{
#if !UE_BUILD_SHIPPING
	FString PerfLevelCpuLastSetFString, PerfLevelGpuLastSetFString;
	SvrPerfLevelToFString(&PerfLevelCpuLastSetFString, InPerfLevelCpu);
	SvrPerfLevelToFString(&PerfLevelGpuLastSetFString, InPerfLevelGpu);
	//UE_LOG(LogSVR, Log, TEXT("%s:CPU = %s; GPU = %s"), InPrefix, *PerfLevelCpuLastSetFString, *PerfLevelGpuLastSetFString);
#endif//#if !UE_BUILD_SHIPPING
}

static bool PerfLevelLastSetByCvarRead(
	enum svrPerfLevel* OutPerfLevel,
	const TAutoConsoleVariable<FString>& InCVar,
	const enum svrPerfLevel InPerfLevelDefault)
{
	const bool bReadSucceeded = FStringToSvrPerfLevel(OutPerfLevel, InCVar.GetValueOnAnyThread());
	if (!bReadSucceeded)
	{
		*OutPerfLevel = InPerfLevelDefault;
	}

	return bReadSucceeded;
}

/*static*/ bool FSnapdragonVRHMD::PerfLevelsLastSetByCvarRead(
	enum svrPerfLevel* OutPerfLevelCpuCurrent,
	enum svrPerfLevel* OutPerfLevelGpuCurrent,
	const enum svrPerfLevel InPerfLevelCpuDefault,
	const enum svrPerfLevel InPerfLevelGpuDefault)
{
	bool bValid = PerfLevelLastSetByCvarRead(OutPerfLevelCpuCurrent, CVarPerfLevelCpu, InPerfLevelCpuDefault);
	bValid &= PerfLevelLastSetByCvarRead(OutPerfLevelGpuCurrent, CVarPerfLevelGpu, InPerfLevelGpuDefault);
	return bValid;
}

static void PerfLevelOnChangeByCvar(enum svrPerfLevel* const OutPerfLevelToSet, const IConsoleVariable* const InConsoleVar, const TCHAR* const InLogPrefix)
{
	//svr performance levels can be manipulated by render or game thread, so prevent race conditions
	FScopeLock ScopeLock(&FSnapdragonVRHMDCustomPresent::PerfLevelCriticalSection);

	enum svrPerfLevel PerfLevel;
	const bool bReadSucceeded = FStringToSvrPerfLevel(&PerfLevel, InConsoleVar->GetString());
	if (bReadSucceeded)
	{
		PerfLevelLastSet(OutPerfLevelToSet, PerfLevel);
		FSnapdragonVRHMD::PerfLevelLog(InLogPrefix, FSnapdragonVRHMD::PerfLevelCpuLastSet, FSnapdragonVRHMD::PerfLevelGpuLastSet);
		svrSetPerformanceLevels(FSnapdragonVRHMD::PerfLevelCpuLastSet, FSnapdragonVRHMD::PerfLevelGpuLastSet);
	}
}
static void PerfLevelCpuOnChangeByCvar(IConsoleVariable* InVar)
{
	PerfLevelOnChangeByCvar(&FSnapdragonVRHMD::PerfLevelCpuLastSet, InVar, TEXT("svr.perfCpu cvar"));
}
static void PerfLevelGpuOnChangeByCvar(IConsoleVariable* InVar)
{
	PerfLevelOnChangeByCvar(&FSnapdragonVRHMD::PerfLevelGpuLastSet, InVar, TEXT("svr.perfGpu cvar"));
}
#endif//#if SNAPDRAGONVR_SUPPORTED_PLATFORMS

#if SNAPDRAGONVR_SUPPORTED_PLATFORMS
bool FSnapdragonVRHMD::IsHMDEnabled() const
{
	
	return bHmdEnabled;
}

void FSnapdragonVRHMD::EnableHMD(bool allow)
{
	
	bHmdEnabled = allow;
	if (!bHmdEnabled)
	{
		EnableStereo(false);
		return;
	}
	EnableStereo(allow);	// Only the console command will call this function.  Therefore the bHmdEnabled is initially true.
}

bool FSnapdragonVRHMD::IsStereoEnabledInternal() const
{
	// Internal function will not use the LOG_FUNC()
	return bStereoEnabled && bHmdEnabled;
}

void FSnapdragonVRHMD::GetFieldOfView(float & OutHFOVInDegrees, float & OutVFOVInDegrees) const
{
	
	OutHFOVInDegrees = 0.0f;
	OutVFOVInDegrees = 0.0f;
}

bool FSnapdragonVRHMD::GetHMDMonitorInfo(MonitorInfo & MonitorDesc)
{
	if (IsInitialized())
	{
		MonitorDesc.MonitorName = "";
		MonitorDesc.MonitorId = 0;
		MonitorDesc.DesktopX = MonitorDesc.DesktopY = 0;
		MonitorDesc.ResolutionX = RenderTargetSize.X;
		MonitorDesc.ResolutionY = RenderTargetSize.Y;
		return true;
	}
	else
	{
		MonitorDesc.MonitorName = "";
		MonitorDesc.MonitorId = 0;
		MonitorDesc.DesktopX = MonitorDesc.DesktopY = MonitorDesc.ResolutionX = MonitorDesc.ResolutionY = 0;
	}

	return false;
}

void FSnapdragonVRHMD::GetEyeRenderParams_RenderThread(const FRenderingCompositePassContext & Context, FVector2D & EyeToSrcUVScaleValue, FVector2D & EyeToSrcUVOffsetValue) const
{
	EyeToSrcUVOffsetValue = FVector2D::ZeroVector;
	EyeToSrcUVScaleValue = FVector2D(1.0f, 1.0f);
}

void FSnapdragonVRHMD::SetInterpupillaryDistance(float NewInterpupillaryDistance)
{
}

float FSnapdragonVRHMD::GetInterpupillaryDistance() const
{
	return 0.064f;
}

bool FSnapdragonVRHMD::GetHMDDistortionEnabled(EShadingPath ShadingPath) const
{
	return false;
}

FIntPoint FSnapdragonVRHMD::GetIdealRenderTargetSize() const
{
	
	return RenderTargetSize;
}

bool FSnapdragonVRHMD::IsChromaAbCorrectionEnabled() const
{
	return true;
}

void FSnapdragonVRHMD::DrawDistortionMesh_RenderThread(FRenderingCompositePassContext & Context, const FIntPoint & TextureSize)
{
}

bool FSnapdragonVRHMD::GetCurrentPose(int32 DeviceId, FQuat & OutOrientation, FVector & OutPosition)
{
	
	if (DeviceId != IXRTrackingSystem::HMDDeviceId) {
		return false;
	}
	if (!IsInGameThread()) return false;
	if (!bInitialized) return false;

	FSnapdragonVRHMDCustomPresent::FPoseStateFrame* PoseState = pSnapdragonVRBridge->PoseHistory.Get();
	if (!PoseState)
	{
		return false;
	}

	FNoloVRHMD *noloVR = GetNoloVRHMD();
	bool RetVal = false;
	if (noloVR != nullptr) {
		FQuat DeviceOrientation = FQuat::Identity;
		RetVal = noloVR->GetTrackedDevicePositionAndOrientation( OutPosition, DeviceOrientation);
	}
	PoseToOrientationAndPosition(PoseState->Pose.pose, OutOrientation);

	CurHmdOrientation = LastHmdOrientation = OutOrientation;
	if (RetVal) {
		CurHmdPosition = OutPosition;
	}
	return true;
}

bool FSnapdragonVRHMD::GetRelativeEyePose(int32 DeviceId, EStereoscopicPass Eye, FQuat & OutOrientation, FVector & OutPosition)
{
	
	return FXRTrackingSystemBase::GetRelativeEyePose(DeviceId, Eye, OutOrientation, OutPosition);
}

bool FSnapdragonVRHMD::IsHeadTrackingAllowed() const
{
	
	return true;
}

void FSnapdragonVRHMD::OnEndPlay(FWorldContext & InWorldContext)
{
	EnableStereo(false);
}

bool FSnapdragonVRHMD::OnStartGameFrame(FWorldContext & WorldContext)
{
	if (bInitialized == false) 
		return false;
	check(pSnapdragonVRBridge)

	//if sensor fusion is inactive, but the app has been resumed and initialized on both the main thread and graphics thread, then start sensor fusion
	if (bResumed &&pSnapdragonVRBridge->bContextInitialized &&!pSnapdragonVRBridge->bInVRMode &&bInitialized)
	{
		BeginVRMode();
	}

	bool ReturnVal = true;

	if (pSnapdragonVRBridge->bInVRMode)
	{
		FRenderCommandFence Fence_Pose; //Avoid GetSyncPose twice in one submit.
										//SCOPED_NAMED_EVENT(UpdetePoses, FColor::Orange);
		Fence_Pose.BeginFence();
		Fence_Pose.Wait();

		svrHeadPoseState HeadPoseState;
		ReturnVal = GetHeadPoseState(&HeadPoseState);

		FSnapdragonVRHMDCustomPresent::FPoseStateFrame svrHeadPose;
		svrHeadPose.Pose = HeadPoseState;
		svrHeadPose.FrameNumber = GFrameCounter;
		pSnapdragonVRBridge->PoseHistory.Enqueue(svrHeadPose);
	}
	RefreshTrackingToWorldTransform(WorldContext);
	return ReturnVal;
}

bool FSnapdragonVRHMD::DoesSupportPositionalTracking() const
{
	svrDeviceInfo di = svrGetDeviceInfo();
	const unsigned int supportedTrackingModes = svrGetSupportedTrackingModes();

	const bool bTrackingPosition = supportedTrackingModes & kTrackingPosition;

	return bTrackingPosition;
}

bool FSnapdragonVRHMD::HasValidTrackingPosition()
{
	
	return DoesSupportPositionalTracking();
}

bool FSnapdragonVRHMD::EnumerateTrackedDevices(TArray<int32>& OutDevices, EXRTrackedDeviceType Type)
{

	if (Type == EXRTrackedDeviceType::Any || Type == EXRTrackedDeviceType::HeadMountedDisplay) {
		OutDevices.Add(IXRTrackingSystem::HMDDeviceId);
		return true;
	}
	return false;
}


void FSnapdragonVRHMD::SetTrackingOrigin(EHMDTrackingOrigin::Type NewOrigin)
{
	switch (NewOrigin)
	{
	case EHMDTrackingOrigin::Eye:
		Origin = SVR_PoseOriginModel::SVR_PoseOriginModel_OriginOnHead;
		break;
	case EHMDTrackingOrigin::Floor:
		Origin = SVR_PoseOriginModel::SVR_PoseOriginModel_OriginOnGround;
		break;
	}
}

EHMDTrackingOrigin::Type FSnapdragonVRHMD::GetTrackingOrigin()
{
	EHMDTrackingOrigin::Type rv = EHMDTrackingOrigin::Eye;

	switch (Origin)
	{
	case SVR_PoseOriginModel::SVR_PoseOriginModel_OriginOnHead:
		rv = EHMDTrackingOrigin::Eye;
		break;
	case SVR_PoseOriginModel::SVR_PoseOriginModel_OriginOnGround:
		rv = EHMDTrackingOrigin::Floor;
		break;
	}

	return rv;
}

void FSnapdragonVRHMD::ResetOrientationAndPosition(float yaw)
{
	ResetOrientation(yaw);
	ResetPosition();
}

void FSnapdragonVRHMD::ResetOrientation(float Yaw)
{
	svrRecenterPose();
}

void FSnapdragonVRHMD::ResetPosition()
{

}

void FSnapdragonVRHMD::SetBaseRotation(const FRotator & BaseRot)
{
}

FRotator FSnapdragonVRHMD::GetBaseRotation() const
{
	return FRotator::ZeroRotator;
}

void FSnapdragonVRHMD::SetBaseOrientation(const FQuat & BaseOrient)
{
}

FQuat FSnapdragonVRHMD::GetBaseOrientation() const
{
	return FQuat::Identity;
}

float FSnapdragonVRHMD::GetWorldToMetersScale() const
{
	if (IsInGameThread() && GWorld != nullptr)
	{
		return GWorld->GetWorldSettings()->WorldToMeters;
	}
	return 100.0f;
}

bool FSnapdragonVRHMD::ShouldUseSeparateRenderTarget() const
{
	
	check(IsInGameThread());
	return IsStereoEnabled();
}

void FSnapdragonVRHMD::CalculateRenderTargetSize(const FViewport & Viewport, uint32 & InOutSizeX, uint32 & InOutSizeY)
{
	InOutSizeX = RenderTargetSize.X;
	InOutSizeY = RenderTargetSize.Y;
}

bool FSnapdragonVRHMD::NeedReAllocateViewportRenderTarget(const FViewport & Viewport)
{
	check(IsInGameThread());

	const uint32 InSizeX = Viewport.GetSizeXY().X;
	const uint32 InSizeY = Viewport.GetSizeXY().Y;

	FIntPoint RTSize;
	RTSize.X = Viewport.GetRenderTargetTexture()->GetSizeX();
	RTSize.Y = Viewport.GetRenderTargetTexture()->GetSizeY();

	uint32 NewSizeX = InSizeX, NewSizeY = InSizeY;
	CalculateRenderTargetSize(Viewport, NewSizeX, NewSizeY);
	if (NewSizeX != RTSize.X || NewSizeY != RTSize.Y)
	{
		return true;
	}

	return false;
}

void FSnapdragonVRHMD::UpdateViewportRHIBridge(bool bUseSeparateRenderTarget, const FViewport & Viewport, FRHIViewport * const ViewportRHI)
{
	check(IsInGameThread());
	if (!IsStereoEnabled())
	{
		if (!bUseSeparateRenderTarget)
		{
			ViewportRHI->SetCustomPresent(nullptr);
		}
		return;
	}
	pSnapdragonVRBridge->UpdateViewport(Viewport, ViewportRHI);

}

bool FSnapdragonVRHMD::IsStereoEnabled() const
{
	return bStereoEnabled && bHmdEnabled;
}

bool FSnapdragonVRHMD::EnableStereo(bool stereo)
{
	
	bStereoEnabled = stereo;
	GEngine->bForceDisableFrameRateSmoothing = stereo;
	return bStereoEnabled;
}

void FSnapdragonVRHMD::AdjustViewRect(EStereoscopicPass StereoPass, int32 & X, int32 & Y, uint32 & SizeX, uint32 & SizeY) const
{
	SizeX = FMath::CeilToInt(RenderTargetSize.X * PixelDensity) / 2;
	SizeY = FMath::CeilToInt(RenderTargetSize.Y * PixelDensity);
	if (StereoPass == eSSP_RIGHT_EYE)
	{
		X += SizeX;
	}
}

void FSnapdragonVRHMD::SetFinalViewRect(const EStereoscopicPass StereoPass, const FIntRect & FinalViewRect)
{
}

void FSnapdragonVRHMD::CalculateStereoViewOffset(const EStereoscopicPass StereoPassType, FRotator & ViewRotation, const float WorldToMeters, FVector & ViewLocation)
{
	
	if (StereoPassType != eSSP_FULL)
	{
		const float EyeOffset = (GetInterpupillaryDistance() * 0.5f) * WorldToMeters;
		const float PassOffset = (StereoPassType == eSSP_LEFT_EYE) ? -EyeOffset : EyeOffset;
		ViewLocation += ViewRotation.Quaternion().RotateVector(FVector(0, PassOffset, 0));
	}
}

FMatrix FSnapdragonVRHMD::GetStereoProjectionMatrix(const EStereoscopicPass StereoPassType) const
{
	
	check(IsStereoEnabledInternal());
	FMatrix* Mat = nullptr;
	if (StereoPassType == eSSP_LEFT_EYE) {
		Mat = LeftProjection;
	}
	else if (StereoPassType == eSSP_RIGHT_EYE) {
		Mat = RightProjection;
	}
	return *Mat;
}

void FSnapdragonVRHMD::InitCanvasFromView(FSceneView * InView, UCanvas * Canvas)
{
}

FRHICustomPresent * FSnapdragonVRHMD::GetCustomPresent()
{
	return pSnapdragonVRBridge;
}

void FSnapdragonVRHMD::SetupViewFamily(FSceneViewFamily & InViewFamily)
{
	InViewFamily.EngineShowFlags.MotionBlur = 0;
	InViewFamily.EngineShowFlags.HMDDistortion = false;
	InViewFamily.EngineShowFlags.ScreenPercentage = false;
	InViewFamily.EngineShowFlags.StereoRendering = IsStereoEnabled();
}
void FSnapdragonVRHMD::SetupView(FSceneViewFamily & InViewFamily, FSceneView & InView)
{
	InView.BaseHmdOrientation = LastHmdOrientation;
	InView.BaseHmdLocation = LastHmdPosition;
}
void FSnapdragonVRHMD::PreRenderViewFamily_RenderThread(FRHICommandListImmediate & RHICmdList, FSceneViewFamily & InViewFamily)
{
	check(IsInRenderingThread());
	pSnapdragonVRBridge->BeginRendering(RHICmdList, InViewFamily);

	//const FSceneView* MainView = InViewFamily.Views[0];
	//const float WorldToMetersScale = MainView->WorldToMetersScale;

	//FSnapdragonVRHMDCustomPresent::FPoseStateFrame* PoseState = pSnapdragonVRBridge->PoseHistory.Get();
	//if (!PoseState)
	//{
	//	return;
	//}

	//FQuat OldOrientation;
	//FVector OldPosition;
	//PoseToOrientationAndPosition(PoseState->Pose.pose, OldOrientation, OldPosition, WorldToMetersScale);
	//const FTransform OldRelativeTransform(OldOrientation, OldPosition);

	//svrHeadPoseState HeadPoseState;
	//GetHeadPoseState(&HeadPoseState);

	//const svrHeadPose Pose = HeadPoseState.pose;

	//PoseState->Pose = HeadPoseState;

	//FQuat NewOrientation;
	//FVector NewPosition;
	//PoseToOrientationAndPosition(Pose, NewOrientation, NewPosition, WorldToMetersScale);
	//const FTransform NewRelativeTransform(NewOrientation, NewPosition);

//	ApplyLateUpdate(InViewFamily.Scene, OldRelativeTransform, NewRelativeTransform);

}
void FSnapdragonVRHMD::PreRenderView_RenderThread(FRHICommandListImmediate & RHICmdList, FSceneView & InView)
{
	
	check(IsInRenderingThread());
}
//-----------------------------------------------------------------------------
// FSnapdragonVRHMD Implementation
//-----------------------------------------------------------------------------

void FSnapdragonVRHMD::Shutdown()
{
	bInitialized = false;
	bResumed = false;
	if (LeftProjection != nullptr)
		delete LeftProjection;
	LeftProjection = nullptr;

	if (RightProjection != nullptr)
		delete RightProjection;
	RightProjection = nullptr;
}

FSnapdragonVRHMD::FSnapdragonVRHMD(const FAutoRegister & AutoRegister)
	: FSceneViewExtensionBase(AutoRegister),
	bInitialized(false),
	bResumed(false),
	CurHmdOrientation(FQuat::Identity),
	LastHmdOrientation(FQuat::Identity),
	DeltaControlRotation(FRotator::ZeroRotator),
	DeltaControlOrientation(FQuat::Identity),
	CurHmdPosition(FVector::ZeroVector),
	LastHmdPosition(FVector::ZeroVector),
	PixelDensity(1.f),
	LeftProjection(nullptr),
	RightProjection(nullptr),
	bHmdEnabled(true),
	bStereoEnabled(false),
	bNeedReinitEGL(false)
{

	//noloVrApi = nolovr::NoloVrApi::Create();
	
	Startup();
}

FSnapdragonVRHMD::~FSnapdragonVRHMD()
{
	UE_LOG(LogSVR, Log, TEXT("~FSnapdragonVRHMD()"));
	EndVRMode();
}


bool FSnapdragonVRHMD::IsInitialized() const
{
	return bInitialized;
}

bool FSnapdragonVRHMD::InitializeExternalResources()
{
	CVarPerfLevelCpu.AsVariable()->SetOnChangedCallback(FConsoleVariableDelegate::CreateStatic(&PerfLevelCpuOnChangeByCvar));
	CVarPerfLevelGpu.AsVariable()->SetOnChangedCallback(FConsoleVariableDelegate::CreateStatic(&PerfLevelGpuOnChangeByCvar));

	extern struct android_app* GNativeAndroidApp;

	svrInitParams initParams;

	initParams.javaVm = GJavaVM;
	initParams.javaEnv = FAndroidApplication::GetJavaEnv();
	initParams.javaActivityObject = GNativeAndroidApp->activity->clazz;

	if (svrInitialize(&initParams) != SVR_ERROR_NONE)
	{
		UE_LOG(LogSVR, Error, TEXT("svrInitialize failed"));
		return false;
	}
	else
	{
		UE_LOG(LogSVR, Log, TEXT("svrInitialize succeeeded"));

		svrSetTrackingMode(kTrackingRotation | kTrackingPosition);
		return true;
	}
}


void FSnapdragonVRHMD::Startup()
{
	bInitialized = InitializeExternalResources();
	if (!bInitialized)
	{
		return;
	}

	pSnapdragonVRBridge = new FSnapdragonVRHMDCustomPresent(this);
	ResetProjectionMats();
	//Register life cycle delegates
	FCoreDelegates::ApplicationWillEnterBackgroundDelegate.AddRaw(this, &FSnapdragonVRHMD::ApplicationWillEnterBackgroundDelegate);
	FCoreDelegates::ApplicationWillDeactivateDelegate.AddRaw(this, &FSnapdragonVRHMD::ApplicationWillDeactivateDelegate);//calls to this delegate are often (always?) paired with a call to ApplicationWillEnterBackgroundDelegate(), but cover the possibility that only this delegate is called
	FCoreDelegates::ApplicationHasEnteredForegroundDelegate.AddRaw(this, &FSnapdragonVRHMD::ApplicationHasEnteredForegroundDelegate);
	FCoreDelegates::ApplicationHasReactivatedDelegate.AddRaw(this, &FSnapdragonVRHMD::ApplicationHasReactivatedDelegate);//calls to this delegate are often (always?) paired with a call to ApplicationHasEnteredForegroundDelegate(), but cover the possibility that only this delegate is called
	FCoreDelegates::OnFEngineLoopInitComplete.AddRaw(this, &FSnapdragonVRHMD::OnFEngineLoopInitComplete);
																														 //don't bother with ApplicationWillTerminateDelegate() -- "There is no guarantee that this will ever be called on a mobile device, save state when ApplicationWillEnterBackgroundDelegate is called instead." -- https://docs.unrealengine.com/latest/INT/API/Runtime/Core/Misc/FCoreDelegates/ApplicationWillTerminateDelegate/index.html --June 10, 2016
																														 //OnExit() and OnPreExit() are not documented as being called on mobile -- https://docs.unrealengine.com/latest/INT/API/Runtime/Core/Misc/FCoreDelegates/OnExit/index.html and https://docs.unrealengine.com/latest/INT/API/Runtime/Core/Misc/FCoreDelegates/OnPreExit/index.html --June 10, 2016
	//svrDeviceInfo DeviceInfo = svrGetDeviceInfo();
	//RenderTargetSize.X = DeviceInfo.targetEyeWidthPixels * 2;
	//RenderTargetSize.Y = DeviceInfo.targetEyeHeightPixels;

	FPlatformRect Rect = FAndroidWindow::GetScreenRect();
	uint32 width = Rect.Right - Rect.Left;
	uint32 height = Rect.Bottom - Rect.Top;
	RenderTargetSize.X = width;
	RenderTargetSize.Y = height;

	const int32 RTSizeX = RenderTargetSize.X;
	const int32 RTSizeY = RenderTargetSize.Y;
	EyeRenderViewport[0] = FIntRect(0, 0, RTSizeX / 2 - 1, RTSizeY - 1);
	EyeRenderViewport[1] = FIntRect(RTSizeX / 2 + 1, 1, RTSizeX - 1, RTSizeY - 1);
	// disable vsync
	static IConsoleVariable* CVSyncVar = IConsoleManager::Get().FindConsoleVariable(TEXT("r.VSync"));
	CVSyncVar->Set(false);

	// enforce finishcurrentframe
	static IConsoleVariable* CFCFVar = IConsoleManager::Get().FindConsoleVariable(TEXT("r.FinishCurrentFrame"));
	CFCFVar->Set(false);
}

void FSnapdragonVRHMD::ApplicationWillEnterBackgroundDelegate()
{
	CleanupIfNecessary();
}

void FSnapdragonVRHMD::CleanupIfNecessary()
{
	if (!bResumed)
		return;

	bResumed = false;

	if (pSnapdragonVRBridge->bInVRMode)
	{
		//stop consuming resources for VR until the app is resumed
		svrEndVr();
		svrShutdown();
		pSnapdragonVRBridge->bInVRMode = false;
		bInitialized = false;
		auto egl = AndroidEGL::GetInstance();
		if (!bNeedReinitEGL && egl->IsInitialized()) {
			egl->UnBind();
			bNeedReinitEGL = true;
		}
	}
}

void FSnapdragonVRHMD::ApplicationWillDeactivateDelegate()
{
	CleanupIfNecessary();
}

void FSnapdragonVRHMD::ApplicationHasReactivatedDelegate()
{
	InitializeIfNecessaryOnResume();
}

void FSnapdragonVRHMD::ApplicationHasEnteredForegroundDelegate()
{
	InitializeIfNecessaryOnResume();
}

void FSnapdragonVRHMD::InitializeIfNecessaryOnResume()
{
	if (bResumed)
		return;

	auto egl = AndroidEGL::GetInstance();
	if (bNeedReinitEGL && !egl->IsInitialized()) {
		egl->ReInit();
		bNeedReinitEGL = false;
	}
	if (!bInitialized)//Upon application launch, FSnapdragonVRHMD::Startup() must initialize immediately, but Android lifecycle "resume" delegates will also be called -- don't double-initialize
	{
		bInitialized = InitializeExternalResources();
	}
	bResumed = true;
}

void FSnapdragonVRHMD::SetCPUAndGPULevels(const int32 InCPULevel, const int32 InGPULevel) const
{
	const svrPerfLevel SvrPerfLevelCPU = static_cast<const svrPerfLevel>(InCPULevel);
	const svrPerfLevel SvrPerfLevelGPU = static_cast<const svrPerfLevel>(InGPULevel);
	check(IsPerfLevelValid(SvrPerfLevelCPU));
	check(IsPerfLevelValid(SvrPerfLevelGPU));

	//svr performance levels can be manipulated by render or game thread, so prevent race conditions
	FScopeLock ScopeLock(&pSnapdragonVRBridge->PerfLevelCriticalSection);
	PerfLevelCpuLastSet = SvrPerfLevelCPU;
	PerfLevelGpuLastSet = SvrPerfLevelGPU;
	// CTORNE ->
	if (pSnapdragonVRBridge->bInVRMode)
	{
		svrSetPerformanceLevels(PerfLevelCpuLastSet, PerfLevelGpuLastSet);
		FSnapdragonVRHMD::PerfLevelLog(TEXT("SetCPUAndGPULevels"), PerfLevelCpuLastSet, PerfLevelGpuLastSet);
	}
	// <- CTORNE
}

void FSnapdragonVRHMD::PoseToOrientationAndPosition(const svrHeadPose& Pose, FQuat& OutCurrentOrientation)
{
	if (pSnapdragonVRBridge->bInVRMode)
	{
		OutCurrentOrientation = FQuat(-Pose.rotation.z, Pose.rotation.x, Pose.rotation.y, Pose.rotation.w);
		//OutCurrentPosition = FVector(NPosition.z * WorldToMetersScale, NPosition.x * WorldToMetersScale, NPosition.y * WorldToMetersScale);
	}
	else
	{
		OutCurrentOrientation = FQuat(FRotator(0.0f, 0.0f, 0.0f));
		//OutCurrentPosition = FVector(0.0f, 0.0f, 0.0f);
	}
}

void FSnapdragonVRHMD::BeginVRMode()
{
	check(pSnapdragonVRBridge);
	if (IsInRenderingThread())
	{
		pSnapdragonVRBridge->DoBeginVR();
	}
	else
	{
		ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER(BeginVRMode,
			FSnapdragonVRHMDCustomPresent*, pSnapdragonVRBridge, pSnapdragonVRBridge,
			{
				pSnapdragonVRBridge->DoBeginVR();
			});
		FlushRenderingCommands();
	}
}

void FSnapdragonVRHMD::EndVRMode()
{
	if (pSnapdragonVRBridge!=nullptr) {
		pSnapdragonVRBridge->DoEndVR();
	}
	delete pSnapdragonVRBridge;
	pSnapdragonVRBridge = nullptr;

	if (LeftProjection != nullptr)
		delete LeftProjection;
	LeftProjection = nullptr;

	if (RightProjection != nullptr)
		delete RightProjection;
	RightProjection = nullptr;

	svrShutdown();
}

bool FSnapdragonVRHMD::GetHeadPoseState(svrHeadPoseState* HeadPoseState)
{
	
	float PredictedTime = 0.f;
	 const double Now = FPlatformTime::Seconds();
	 if (IsInGameThread())
	 {
	 	static double Prev;
	 	const double RawDelta = Now - Prev;
	 	Prev = Now;
	 	const float ClampedPrediction = FMath::Min(0.1, RawDelta * 2.f);
	 	// convert Seconds to MS
	 	PredictedTime = ClampedPrediction * 1000.f;
	 }
	 else if (IsInRenderingThread())
	 {
		PredictedTime = svrGetPredictedDisplayTime();
	 }

	svrHeadPoseState PredictedHeadPose = svrGetPredictedHeadPose(PredictedTime);
	*HeadPoseState = PredictedHeadPose;
	return true;
}

void FSnapdragonVRHMD::SendEvents()
{
	svrEvent SvrEvent;
	while (svrPollEvent(&SvrEvent))
	{
		switch (SvrEvent.eventType)
		{
		case svrEventType::kEventSdkServiceStarting:
		{
			USnapdragonVRHMDFunctionLibrary::GetSnapdragonVRHMDEventManager()->OnSnapdragonVRSdkServiceDelegate.Broadcast(ESnapdragonVRSdkServiceEventType::EventSdkServiceStarting);
			break;
		}
		case svrEventType::kEventSdkServiceStarted:
		{
			USnapdragonVRHMDFunctionLibrary::GetSnapdragonVRHMDEventManager()->OnSnapdragonVRSdkServiceDelegate.Broadcast(ESnapdragonVRSdkServiceEventType::EventSdkServiceStarted);
			break;
		}
		case svrEventType::kEventSdkServiceStopped:
		{
			USnapdragonVRHMDFunctionLibrary::GetSnapdragonVRHMDEventManager()->OnSnapdragonVRSdkServiceDelegate.Broadcast(ESnapdragonVRSdkServiceEventType::EventSdkServiceStopped);
			break;
		}
		case svrEventType::kEventThermal:
		{
			ESnapdragonVRThermalZone ThermalZone = static_cast<ESnapdragonVRThermalZone>(SvrEvent.eventData.thermal.zone);
			ESnapdragonVRThermalLevel ThermalLevel = static_cast<ESnapdragonVRThermalLevel>(SvrEvent.eventData.thermal.level);

			USnapdragonVRHMDFunctionLibrary::GetSnapdragonVRHMDEventManager()->OnSnapdragonVRThermalDelegate.Broadcast(ThermalZone, ThermalLevel);
			break;
		}
		case svrEventType::kEventVrModeStarted:
		{
			USnapdragonVRHMDFunctionLibrary::GetSnapdragonVRHMDEventManager()->OnSnapdragonVRModeDelegate.Broadcast(ESnapdragonVRModeEventType::EventVrModeStarted);
			break;
		}
		//case svrEventType::kEventVrModeStopping:
		//{
		//	UE_LOG(LogSVR, Log, TEXT("SendEvents::kEventVrModeStopping"));
		//	USnapdragonVRHMDFunctionLibrary::GetSnapdragonVRHMDEventManager()->OnSnapdragonVRModeDelegate.Broadcast(ESnapdragonVRModeEventType::EventVrModeStopping);
		//	break;
		//}
		//case svrEventType::kEventVrModeStopped:
		//{
		//	UE_LOG(LogSVR, Log, TEXT("SendEvents::kEventVrModeStopped"));
		//	USnapdragonVRHMDFunctionLibrary::GetSnapdragonVRHMDEventManager()->OnSnapdragonVRModeDelegate.Broadcast(ESnapdragonVRModeEventType::EventVrModeStopped);
		//	break;
		//}
		default:
			break;
		}
	}
}

void FSnapdragonVRHMD::OnFEngineLoopInitComplete()
{
	setDeviceSupportedMaxFPS();
}

void FSnapdragonVRHMD::setDeviceSupportedMaxFPS()
{
#if SNAPDRAGONVR_SUPPORTED_PLATFORMS
	svrDeviceInfo DeviceInfo = svrGetDeviceInfo();

		float fps = DeviceInfo.displayRefreshRateHz;
		GEngine->SetMaxFPS(fps);
#endif

}

void FSnapdragonVRHMD::ResetProjectionMats()
{
	
	svrEye hmdEyes[2] = { SVR_Eye_Left, SVR_Eye_Right };
	svrDeviceInfo di = svrGetDeviceInfo();
	for (auto eye : hmdEyes) {
		float Left, Right, Top, Bottom;

		if (eye == SVR_Eye_Left) {
			Right = -0.992601;
			Left = 0.992601;
			Bottom = 0.992601;
			Top = -0.992601;
		}
		else
		{
			Right = -0.990773;
			Left = 0.990773;
			Bottom = 0.990773;
			Top = -0.990773;
		}


		Right *= -1.0f;
		Left *= -1.0f;
		Top *= -1.0f;
		Bottom *= -1.0f;

		float ZNear = (GNearClippingPlane == 10.f) ? 0.1f : GNearClippingPlane;

		float SumRL = (Right + Left);
		float SumTB = (Top + Bottom);
		float InvRL = (1.0f / (Right - Left));
		float InvTB = (1.0f / (Top - Bottom));

		FMatrix** Proj = (eye == SVR_Eye_Left) ? &LeftProjection : &RightProjection;

		*Proj = new FMatrix(
			FPlane((2.0f * InvRL), 0.0f, 0.0f, 0.0f),
			FPlane(0.0f, (2.0f * InvTB), 0.0f, 0.0f),
			FPlane((SumRL * InvRL), (SumTB * InvTB), 0.0f, 1.0f),
			FPlane(0.0f, 0.0f, ZNear, 0.0f)
		);
	}

}
#endif//#if SNAPDRAGONVR_SUPPORTED_PLATFORMS
//-----------------------------------------------------------------------------
// FSnapdragonVRHMDPlugin Implementation
//-----------------------------------------------------------------------------

class FSnapdragonVRHMDPlugin : public ISnapdragonVRHMDPlugin
{
	/** IHeadMountedDisplayModule implementation */
	virtual TSharedPtr< class IXRTrackingSystem, ESPMode::ThreadSafe > CreateTrackingSystem() override;

	FString GetModulePriorityKeyName() const
	{
		
		return FString(TEXT("SnapdragonVR"));
	}

	FString GetModuleKeyName() const
	{
		
		return FString(TEXT("SnapdragonVR"));
	}
	//TODO: Test whether it works or not if been removed
	virtual bool IsHMDConnected() override
	{
		
		return true;
	}
#if SNAPDRAGONVR_SUPPORTED_PLATFORMS
	TSharedPtr< FSnapdragonVRHMD, ESPMode::ThreadSafe > SnapdragonVRHMD;//maintain singleton instance, since for Android platforms, UEngine::PreExit() is not called, which means the destructor for FSnapdragonVRHMD is never called.  Nonetheless, CreateHeadMountedDisplay() can still be called an arbitrary number of times -- June 13, 2016
#endif//SNAPDRAGONVR_SUPPORTED_PLATFORMS
};

IMPLEMENT_MODULE(FSnapdragonVRHMDPlugin, SnapdragonVRHMD)

TSharedPtr< class IXRTrackingSystem, ESPMode::ThreadSafe > FSnapdragonVRHMDPlugin::CreateTrackingSystem()
{
#if SNAPDRAGONVR_SUPPORTED_PLATFORMS

	if (!SnapdragonVRHMD.IsValid())
	{
		LOG_FUNC_IF(NSVR_LOG_ENTRY_LIFECYCLE);
		SnapdragonVRHMD = FSceneViewExtensions::NewExtension<FSnapdragonVRHMD>();
	}
	if (static_cast<FSnapdragonVRHMD*>(&*SnapdragonVRHMD)->IsInitialized())
	{
		UE_LOG(LogSVR, Log, TEXT("SnapdragonVR->IsInitialized() == True"));
		return SnapdragonVRHMD;
	}
	else
	{
		SnapdragonVRHMD.Reset();//failed to initialize; free useless instance of SnapdragonVR
	}
#endif//SNAPDRAGONVR_SUPPORTED_PLATFORMS
	return nullptr;
}
