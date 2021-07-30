// Fill out your copyright notice in the Description page of Project Settings.
#include "NOLOVRBlueprintFunctionLibrary.h"
#if PLATFORM_ANDROID
#include "AndroidRuntimeSettings.h"
#endif
#include "NoloVRHMD.h"

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

void UNOLOVRBlueprintFunctionLibrary::HapticWithArg(EControllerHand Hand, float duration, float frequency,
	float amplitude)
{
	FNoloVRHMD *noloVR = GetNoloVRHMD();
	if (noloVR != nullptr) {
		 noloVR->HapticWithArg(Hand,duration,frequency,amplitude);
	}
}

void UNOLOVRBlueprintFunctionLibrary::HapticWithAudioFile(FString path, int channel_number)
{
	FNoloVRHMD *noloVR = GetNoloVRHMD();
	if (noloVR != nullptr) {
		noloVR->HapticWithAudioFile(TCHAR_TO_ANSI(*path),channel_number);
	}
}

void UNOLOVRBlueprintFunctionLibrary::SetHapticAudioConfig(int layout, int format, int sample_rate, int channel_number)
{
	FNoloVRHMD *noloVR = GetNoloVRHMD();
	if (noloVR != nullptr) {
		noloVR->SetHapticAudioConfig(layout,format,sample_rate,channel_number);
	}
}

void UNOLOVRBlueprintFunctionLibrary::HapticWithAudioBuffer(TArray<uint8> buffer, int nb_samples, int channel_number)
{
	FNoloVRHMD *noloVR = GetNoloVRHMD();
	if (noloVR != nullptr) {		
		noloVR->HapticWithAudioBuffer(buffer.GetData(), nb_samples,channel_number);
	}
}

bool UNOLOVRBlueprintFunctionLibrary::StopHaptic(int channel_number)
{
	FNoloVRHMD *noloVR = GetNoloVRHMD();
	if (noloVR != nullptr) {
		return noloVR->StopHaptic(channel_number);
	}
	return false;
}

bool UNOLOVRBlueprintFunctionLibrary::HapticWithAudioFileLoop(FString path, int channel_number, int loopCount)
{
	FNoloVRHMD *noloVR = GetNoloVRHMD();
	if (noloVR != nullptr) {
		return noloVR->HapticWithAudioFileLoop(TCHAR_TO_ANSI(*path),channel_number,loopCount);
	}
	return false;
}

bool UNOLOVRBlueprintFunctionLibrary::HapticWithConfig(float strength, int filtering, int channel_number)
{
	FNoloVRHMD *noloVR = GetNoloVRHMD();
	if (noloVR != nullptr) {
		return noloVR->HapticWithConfig(strength,filtering,channel_number);
	}
	return false;
}

bool UNOLOVRBlueprintFunctionLibrary::Action(FString actionJson)
{
	FNoloVRHMD *noloVR = GetNoloVRHMD();
	if (noloVR != nullptr) {
		return noloVR->Action(TCHAR_TO_ANSI(*actionJson));
	}
	return false;
}

bool UNOLOVRBlueprintFunctionLibrary::M1Write(TArray<uint8> buffer, int32 size)
{
	FNoloVRHMD *noloVR = GetNoloVRHMD();
	if (noloVR != nullptr) {		
		return noloVR->M1Write(buffer.GetData(), size);
	}
	return false;
}

bool UNOLOVRBlueprintFunctionLibrary::M1Write(uint8* buffer, uint32_t size)
{
	FNoloVRHMD *noloVR = GetNoloVRHMD();
	if (noloVR != nullptr) {
		return noloVR->M1Write(buffer,size);
	}
	return false;
}

extern FString GExternalFilePath;
bool UNOLOVRBlueprintFunctionLibrary::CopyFilesToDevices(FString FilesPath, FString FileName, FString& TargetPath)
{
	FString RootPath = "";
	bool Result = false;
#if PLATFORM_ANDROID
	TArray<FString> Folders;
	GExternalFilePath.ParseIntoArray(Folders, TEXT("/"));
	for (FString Folder : Folders)
	{
		RootPath += FString("/..");
	}


	auto AndroidRuntimeSettings = GetDefault<UAndroidRuntimeSettings>();	
	TargetPath = FPaths::Combine(RootPath,TEXT("/sdcard/Android/data/"),AndroidRuntimeSettings->PackageName,TEXT("files"),FileName);
#endif
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	const FString ResourcePath = FPaths::Combine(FPaths::ProjectDir(),FilesPath,FileName);
	UE_LOG(LogTemp,Log,TEXT("CopyFilesToDevices from %s to %s"),*ResourcePath,*TargetPath);
	if (PlatformFile.FileExists(*ResourcePath))
	{
		Result = PlatformFile.CopyFile(*TargetPath, *ResourcePath);
		UE_LOG(LogTemp,Log,TEXT("CopyFilesToDevices Result:%d"),Result);
	}
	return Result;
}

//bool UNOLOVRBlueprintFunctionLibrary::SetTriggerHapticPulse(const EControllerHand DeviceHand, int intensity)
//{
//	FNoloVRHMD *noloVR = GetNoloVRHMD();
//	if (noloVR != nullptr) {
//		return noloVR->TriggerHapticPulse(DeviceHand, intensity);
//	}
//	return false;
//}


