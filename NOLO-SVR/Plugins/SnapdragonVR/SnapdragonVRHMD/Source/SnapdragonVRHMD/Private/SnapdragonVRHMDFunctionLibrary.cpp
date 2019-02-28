//=============================================================================
//
//                  Copyright (c) 2018 QUALCOMM Technologies Inc.
//                              All Rights Reserved.
//
//==============================================================================
#include "SnapdragonVRHMD.h"
#include "../Public/SnapdragonVRHMDFunctionLibrary.h"
#include "Engine.h"   //PMILI: Apparently GEngine is located in Engine.h... Not sure how we can avoid receiving the MONOLITHIC warning
#include "HMDPrivatePCH.h"

USnapdragonVRHMDFunctionLibrary::USnapdragonVRHMDFunctionLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

#if SNAPDRAGONVR_SUPPORTED_PLATFORMS
FSnapdragonVRHMD* GetSnapdragonHMD()
{
	if (GEngine->XRSystem.IsValid() && GEngine->XRSystem->GetSystemName() == FName("FSnapdragonVRHMD"))
	{
		return static_cast<FSnapdragonVRHMD*>(GEngine->XRSystem.Get());
	}

	return nullptr;
}
#endif//#if SNAPDRAGONVR_SUPPORTED_PLATFORMS

void USnapdragonVRHMDFunctionLibrary::SetCpuAndGpuLevelsSVR(const int32 CpuLevel, const int32 GpuLevel)
{
#if SNAPDRAGONVR_SUPPORTED_PLATFORMS
	FSnapdragonVRHMD* HMD = GetSnapdragonHMD();
	if (HMD)
	{
		HMD->SetCPUAndGPULevels(CpuLevel, GpuLevel);
	}
#endif//#if SNAPDRAGONVR_SUPPORTED_PLATFORMS
}

USnapdragonVRHMDEventManager* USnapdragonVRHMDFunctionLibrary::GetSnapdragonVRHMDEventManager()
{
	return USnapdragonVRHMDEventManager::GetInstance();
}