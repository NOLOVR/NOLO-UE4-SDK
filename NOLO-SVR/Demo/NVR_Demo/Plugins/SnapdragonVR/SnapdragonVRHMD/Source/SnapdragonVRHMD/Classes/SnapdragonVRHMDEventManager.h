//=============================================================================
//
//                  Copyright (c) 2018 QUALCOMM Technologies Inc.
//                              All Rights Reserved.
//
//==============================================================================

#pragma once

#include "Delegates/Delegate.h"
#include "UObject/Object.h"
#include "UObject/WeakObjectPtr.h"
#include "SnapdragonVRHMDEventManager.generated.h"

UENUM(BlueprintType)
enum class ESnapdragonVRSdkServiceEventType : uint8
{
	EventSdkServiceStarting,
	EventSdkServiceStarted,
	EventSdkServiceStopped
};

UENUM(BlueprintType)
enum class ESnapdragonVRModeEventType : uint8
{
	EventVrModeStarted,
	EventVrModeStopping,
	EventVrModeStopped
};

UENUM(BlueprintType)
enum class ESnapdragonVRSensorEventType : uint8
{
	EventSensorError,
	EventMagnometerUncalibrated
};

UENUM(BlueprintType)
enum class ESnapdragonVRThermalLevel : uint8
{
	Safe,
	Level1,
	Level2,
	Level3,
	Critical
};


UENUM(BlueprintType)
enum class ESnapdragonVRThermalZone : uint8
{
	Cpu,
	Gpu,
	Skin
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSnapdragonVRSdkServiceDelegate, ESnapdragonVRSdkServiceEventType, Type);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSnapdragonVRThermalDelegate, ESnapdragonVRThermalZone, Zone, ESnapdragonVRThermalLevel, Level);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSnapdragonVRModeDelegate, ESnapdragonVRModeEventType, Type);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSnapdragonVRSensorDelegate, ESnapdragonVRSensorEventType, Type);

/**
* SnapdragonVRHMD Extensions Function Library
*/
UCLASS()
class USnapdragonVRHMDEventManager : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(BlueprintAssignable)
		FSnapdragonVRSdkServiceDelegate OnSnapdragonVRSdkServiceDelegate;

	UPROPERTY(BlueprintAssignable)
		FSnapdragonVRThermalDelegate OnSnapdragonVRThermalDelegate;

	UPROPERTY(BlueprintAssignable)
		FSnapdragonVRModeDelegate OnSnapdragonVRModeDelegate;

	UPROPERTY(BlueprintAssignable)
		FSnapdragonVRSensorDelegate OnSnapdragonVRSensorDelegate;

public:
	static USnapdragonVRHMDEventManager* GetInstance();
};