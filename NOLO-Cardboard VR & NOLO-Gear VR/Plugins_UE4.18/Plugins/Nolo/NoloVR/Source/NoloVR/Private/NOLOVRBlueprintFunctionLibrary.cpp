// Fill out your copyright notice in the Description page of Project Settings.
#include "NOLOVRBlueprintFunctionLibrary.h"
#include "NoloVRHMD.h"

//#include "..\Classes\NOLOVRBlueprintFunctionLibrary.h"

//#if PLATFORM_WINDOWS
FNoloVRHMD* GetNoloVRHMD()
{
	FNoloVRHMD* noloVR;
	TArray<INoloVRDevice*> NoloVRDevices = IModularFeatures::Get().GetModularFeatureImplementations<INoloVRDevice>(INoloVRDevice::GetModularFeatureName());
	for (auto NoloVRDevice : NoloVRDevices)
	{
		if (NoloVRDevice != nullptr)
		{
			noloVR = static_cast<FNoloVRHMD*>(NoloVRDevice);
			if (noloVR != nullptr) {
				return noloVR;
			}
		}
	}
	return nullptr;
}
//#endif // STEAMVR_SUPPORTED_PLATFORMS
FString UNOLOVRBlueprintFunctionLibrary::GetRunningPlatform()
{
#if PLATFORM_ANDROID
	return "Android";
#else
	return "Default";
#endif
}

void UNOLOVRBlueprintFunctionLibrary::SetHmdDeviceType(const EMobileVR_HMDDeviceType DeviceType)
{
	FNoloVRHMD* noloVR = GetNoloVRHMD();
	if (noloVR != nullptr) {
		noloVR->SetHmdDeviceType(DeviceType);
	}
}

bool UNOLOVRBlueprintFunctionLibrary::GetTrackedDevicePositionAndOrientation(FVector & OutPosition, FRotator & OutOrientation)
{
	bool RetVal = false;
	FNoloVRHMD* noloVR = GetNoloVRHMD();
	if (noloVR != nullptr) {
		FQuat DeviceOrientation = FQuat::Identity;
		RetVal = noloVR->GetTrackedDevicePositionAndOrientation(OutPosition, DeviceOrientation);
		OutOrientation = DeviceOrientation.Rotator();
	}
	return RetVal;
}

bool UNOLOVRBlueprintFunctionLibrary::GetHandPositionAndOrientation(EControllerHand Hand, FVector & OutPosition, FRotator & OutOrientation)
{
	bool RetVal = false;
	FNoloVRHMD* noloVR = GetNoloVRHMD();
	if (noloVR != nullptr) {
		FQuat DeviceOrientation = FQuat::Identity;
		RetVal = noloVR->GetControllerOrientationAndPosition(Hand, OutPosition, DeviceOrientation);
		OutOrientation = DeviceOrientation.Rotator();
	}
	return RetVal;
}

bool UNOLOVRBlueprintFunctionLibrary::GetTrackingStatusByDeviceType(const ENoloDeviceType DeviceType)
{
	FNoloVRHMD *noloVR = GetNoloVRHMD();
	if (noloVR != nullptr) {
		return noloVR->GetTrackingStatusByDeviceType((int32)DeviceType)>0 ? true : false;
	}
	return false;
}

bool UNOLOVRBlueprintFunctionLibrary::GetElectricityByDeviceType(const ENoloDeviceType DeviceType, int & battery)
{
	FNoloVRHMD *noloVR = GetNoloVRHMD();
	if (noloVR != nullptr) {
		battery = noloVR->GetElectricityByDeviceType((int32)DeviceType);
		return true;
	}
	battery = 0;
	return false;
}

void UNOLOVRBlueprintFunctionLibrary::SetAppKey(FString appKey)
{
	FNoloVRHMD *noloVR = GetNoloVRHMD();
	if (noloVR != nullptr) {
		 noloVR->SetAppKey(appKey);
	}
}

void UNOLOVRBlueprintFunctionLibrary::ReportError(FString errorMsg)
{
	FNoloVRHMD *noloVR = GetNoloVRHMD();
	if (noloVR != nullptr) {
		noloVR->ReportError(errorMsg);
	}
}

bool UNOLOVRBlueprintFunctionLibrary::IsInstallNoloHome() {
	FNoloVRHMD *noloVR = GetNoloVRHMD();
	if (noloVR != nullptr) {
		return noloVR->IsInstallNoloHome();
	}
	return false;
}

 bool UNOLOVRBlueprintFunctionLibrary::IsStartUpNoloHome(){
	 FNoloVRHMD *noloVR = GetNoloVRHMD();
	 if (noloVR != nullptr) {
		 return noloVR->IsStartUpNoloHome();
	 }
	 return false;
 }

//bool UNOLOVRBlueprintFunctionLibrary::SetTriggerHapticPulse(const EControllerHand DeviceHand, int intensity)
//{
//	FNoloVRHMD *noloVR = GetNoloVRHMD();
//	if (noloVR != nullptr) {
//		return noloVR->TriggerHapticPulse(DeviceHand, intensity);
//	}
//	return false;
//}


