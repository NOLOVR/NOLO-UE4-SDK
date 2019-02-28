//=============================================================================
//
//                  Copyright (c) 2018 QUALCOMM Technologies Inc.
//                              All Rights Reserved.
//
//==============================================================================
#include "SnapdragonVRHMD.h"
#include "../Classes/SnapdragonVRHMDEventManager.h"
#include "HMDPrivatePCH.h"

static USnapdragonVRHMDEventManager* Singleton = nullptr;

USnapdragonVRHMDEventManager::USnapdragonVRHMDEventManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

USnapdragonVRHMDEventManager* USnapdragonVRHMDEventManager::GetInstance()
{
	if (!Singleton)
	{
		Singleton = NewObject<USnapdragonVRHMDEventManager>();
		Singleton->AddToRoot();
	}
	return Singleton;
}