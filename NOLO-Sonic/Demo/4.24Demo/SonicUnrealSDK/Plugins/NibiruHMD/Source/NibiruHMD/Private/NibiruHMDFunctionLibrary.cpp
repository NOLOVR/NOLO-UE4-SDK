// Fill out your copyright notice in the Description page of Project Settings.
#include "NibiruHMDFunctionLibrary.h"
#include "NibiruHMDPrivatePCH.h"
#include "NibiruHMD.h"

 
static FNibiruHMD* GetHMD()
{
	if (GEngine && GEngine->XRSystem.IsValid() && GEngine->XRSystem->GetVersionString().Contains(TEXT("NibiruVR")))
	{
		return static_cast<FNibiruHMD*>(GEngine->XRSystem.Get());
	}

	return nullptr;
}
 

void UNibiruHMDFunctionLibrary::NibiruSetGazeEnabled(bool bEnable)
{
	FNibiruHMD* HMD = GetHMD();
	if (HMD)
	{
		HMD->SetGazeEnabled(bEnable);
	}
}

void UNibiruHMDFunctionLibrary::NibiruSetGazePosZ(float z)
{
	FNibiruHMD* HMD = GetHMD();
	if (HMD)
	{
		HMD->SetGazePosZ(z);
	}
}


void UNibiruHMDFunctionLibrary::NibiruSetCallbackDelegates(FNibiruKeyEventCallbackDelegate OnNibiruKeyEventCallback)
{
	FNibiruHMD* HMD = GetHMD();
	if (HMD)
	{
		HMD->RegisterNibiruKeyEventCallBack(OnNibiruKeyEventCallback);
	}
} 

FVector UNibiruHMDFunctionLibrary::NibiruGetHmdPosition()
{
	FNibiruHMD* HMD = GetHMD();
	if (HMD)
	{
#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
		return HMD->GetCachedFinalHeadPosition();
#endif
	}
	return FVector::ZeroVector;
}

void UNibiruHMDFunctionLibrary::NibiruQuitGame()
{
	// FGenericPlatformMisc::RequestExit(false);
	FNibiruHMD* HMD = GetHMD();
	if (HMD)
	{
#if NIBIRUVRHMD_SUPPORTED_PLATFORMS
		HMD->RequestQuitGame();
#endif
	}
}

int UNibiruHMDFunctionLibrary::NibiruGetVerifyStatus()
{
	FNibiruHMD* HMD = GetHMD();
	if (HMD)
	{
		return HMD->GetVerifyStatus();
	}
	return -1;
}