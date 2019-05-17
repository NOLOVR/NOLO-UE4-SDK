// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "NoloVRHMD.h"
#include "Core.h"
#include "ModuleManager.h"
#include "IPluginManager.h"
#include "Engine/Engine.h"
#include "EngineGlobals.h"
#include "INoloVRPlugin.h"
#define LOCTEXT_NAMESPACE "NoloVRPlugin"

FName FNoloVRHMD::DeviceTypeName(TEXT("NoloVRHMD"));

FNoloVRHMD::FNoloVRHMD() {
	noloVrApi = nolovr::NoloVrApi::Create();
}

void FNoloVRHMD::searchNoloDevice(){
	noloVrApi.get()->Search_Nolo_Device();
}

bool FNoloVRHMD::TriggerHapticPulse(EControllerHand Hand, int intensity)
{
	return (Hand == EControllerHand::Left) ? noloVrApi.get()->TriggerHapticPulse(1, intensity) : noloVrApi.get()->TriggerHapticPulse(2, intensity);
}

int FNoloVRHMD::GetTrackingStatusByDeviceType(const int DeviceType) const
{
	return noloVrApi.get()->GetPoseByDeviceType(DeviceType).status;

}

NControllerState FNoloVRHMD::GetControllerStateByDeviceType(int type) {
	return noloVrApi.get()->GetControllerStateByDeviceType(type);
}

int FNoloVRHMD::GetElectricityByDeviceType(int DeviceType) const
{
	int battery = 0;
	battery = noloVrApi.get()->GetElectricityByDeviceType(DeviceType);
	return battery;
}

void FNoloVRHMD::SetAppKey(FString appkey) const
{
	noloVrApi.get()->SetAppKey(TCHAR_TO_ANSI(* appkey));
}
void FNoloVRHMD::ReportError(FString errorMsg) const
{
	noloVrApi.get()->ReportError(TCHAR_TO_ANSI(*errorMsg));
}

bool FNoloVRHMD::IsInstallNoloHome()const {
	UE_LOG(LogTemp, Log, TEXT("===========IsInstallNoloHome==============\n"));
	return noloVrApi.get()->IsInstallNoloHome();
}

bool FNoloVRHMD::IsStartUpNoloHome()const {
	bool flag = noloVrApi.get()->IsStartUpNolohome();
	UE_LOG(LogTemp, Log, TEXT("===========IsStartUpNoloHome============== %d \n"), flag);
	return noloVrApi.get()->IsStartUpNolohome();
}

void FNoloVRHMD::SetHmdDeviceType(const EMobileVR_HMDDeviceType DeviceType) const
{
	if (DeviceType == EMobileVR_HMDDeviceType::DT_GoogleVR_Cardboard) {
		noloVrApi.get()->SetHmdTrackingCenterByDeviceType((int32)DeviceType);
	}
	else if (DeviceType == EMobileVR_HMDDeviceType::DT_GoogleVR_Daydream)
	{
		noloVrApi.get()->SetHmdTrackingCenterByDeviceType((int32)DeviceType);
	}
	else if (DeviceType == EMobileVR_HMDDeviceType::DT_GearVR)
	{
		noloVrApi.get()->SetHmdTrackingCenterByDeviceType((int32)DeviceType);
	}

}

bool FNoloVRHMD::GetTrackedDevicePositionAndOrientation(FVector& CurrentPosition, FQuat& CurrentOrientation) {

	bool bHasValidPose = false;
	NTrackedDevicePose nPose = noloVrApi.get()->GetPoseByDeviceType(0);
	CurrentPosition = ConvertNVectorToUnreal(nPose.pos);
	CurrentOrientation = ConvertNQuaternionToUnreal(nPose.rot);
	bHasValidPose = nPose.IsConnected;
	return bHasValidPose;
}

bool FNoloVRHMD::GetControllerOrientationAndPosition(EControllerHand Hand, FVector & CurrentPosition, FQuat & CurrentOrientation)
{
	bool bHasValidPose = false;
	int handIndex = (Hand == EControllerHand::Left) ? 1 : 2;
	NTrackedDevicePose nPose = noloVrApi.get()->GetPoseByDeviceType(handIndex);
	CurrentPosition = ConvertNVectorToUnreal(nPose.pos);
	CurrentOrientation = ConvertNQuaternionToUnreal(nPose.rot);
	bHasValidPose = nPose.IsConnected;
	return bHasValidPose;
}

float FNoloVRHMD::GetWorldToMetersScale() const
{
	if (IsInGameThread() && GWorld != nullptr)
	{
		return GWorld->GetWorldSettings()->WorldToMeters;
	}

	// Default value, assume Unreal units are in centimeters
	return 100.0f;
}

FVector FNoloVRHMD::ConvertNVectorToUnreal(const NVector3 & nVector3) const
{
	// Number of Unreal Units per meter.
	const float WorldToMetersScale = GetWorldToMetersScale();
	FVector Result;
	//// Nolovr: Positive Z is Forward, UE: Positive X is Forward.
	Result.X = nVector3.z * WorldToMetersScale;
	//// Nolovr: Positive X is Right, UE: Positive Y is Right.
	Result.Y = nVector3.x * WorldToMetersScale;
	//// Nolovr: Positive Y is Up, UE: Positive Z is Up
	Result.Z = nVector3.y * WorldToMetersScale;
	
	return Result;
}

FQuat FNoloVRHMD::ConvertNQuaternionToUnreal(const NQuaternion & nQuat) const
{
	 FQuat Result = FQuat(nQuat.z, nQuat.x, nQuat.y, nQuat.w);
	return Result;
}


class FNoloVRHMDPlugin:public INoloVRPlugin {
	//Will return nullptr if NoloVR Module has not been loaded.
	virtual TSharedPtr< class INoloVRDevice > CreateNoloVRDevice() override
	{
		//UE_LOG(LogTemp, Log, TEXT("===========CreateNoloVRDevice==============\n"));
		return TSharedPtr< class INoloVRDevice >(new FNoloVRHMD());
	}
public:
	FNoloVRHMDPlugin() {
		//UE_LOG(LogTemp, Log, TEXT("=============FNoloVRHMDPlugin===========\n"));
		LoadNoloVRModule();
	}
	virtual void StartupModule() override
	{
		INoloVRDeviceModule::StartupModule();

		LoadNoloVRModule();
	}

	virtual void ShutdownModule() override
	{
		INoloVRDeviceModule::ShutdownModule();

		UnloadNoloVRModule();
	}

	bool LoadNoloVRModule() {

#if PLATFORM_WINDOWS
		// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

		// Get the base directory of this plugin
		FString BaseDir = IPluginManager::Get().FindPlugin("NoloVR")->GetBaseDir();
		// Add on the relative location of the third party dll and load it
		FString LibraryPath;

		LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/NOLOLibrary/x64/Release/NoLo_USBHID.dll"));
		//FPlatformProcess::PushDllDirectory(*LibraryPath);
		NoloVRDLLHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;
		//FPlatformProcess::PopDllDirectory(*LibraryPath);
		if (!NoloVRDLLHandle)
		{

			UE_LOG(LogTemp, Log, TEXT("Failed to load NoloVR library."));
			return false;
			
		}
#endif
		return true;
	}
	void UnloadNoloVRModule() {
#if PLATFORM_WINDOWS
		// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
		// we call this function before unloading the module.
		// Free the dll handle
		if (NoloVRDLLHandle != nullptr)
		{
			FPlatformProcess::FreeDllHandle(NoloVRDLLHandle);
			NoloVRDLLHandle = nullptr;
		}
#endif
	}
public:
	//static searchNoloDevice search_Nolo_Device;
private:

	void* NoloVRDLLHandle;
};

#undef LOCTEXT_NAMESPACE
IMPLEMENT_MODULE(FNoloVRHMDPlugin, NoloVR)