// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Engine.h"
#include "nolo_api.h"
#include "INoloVRDevice.h"
#include "INoloVRPlugin.h"
#include "NOLOVRBlueprintFunctionLibrary.h"
//typedef void(__cdecl *searchNoloDevice)();

class FNoloVRHMD:public INoloVRDevice{
private:
	std::unique_ptr<nolovr::NoloVrApi> noloVrApi;
public:
	FNoloVRHMD();
	virtual ~FNoloVRHMD() {}
	void searchNoloDevice();
	//INoloVRDevice
	static FName DeviceTypeName;
	virtual FName GetNoloVRDeviceTypeName() const override
	{
		return DeviceTypeName;
	}

private:

	/** Get how many Unreal units correspond to one meter in the real world */
	float GetWorldToMetersScale() const;

	FVector ConvertNVectorToUnreal(const NVector3 & nVector3) const;

	FQuat ConvertNQuaternionToUnreal(const NQuaternion & nQuat) const;
public:
	int GetElectricityByDeviceType(int DeviceType) const;

	void SetHmdDeviceType(const EMobileVR_HMDDeviceType DeviceType)const;

	void SetAppKey(FString data)const;

	void ReportError(FString errorMsg)const;
public:
	NOLOVR_API bool TriggerHapticPulse(EControllerHand Hand, int intensity);

	NOLOVR_API int GetTrackingStatusByDeviceType(const int DeviceType) const;

	NOLOVR_API NControllerState GetControllerStateByDeviceType(int type);

	NOLOVR_API bool GetTrackedDevicePositionAndOrientation(FVector& CurrentPosition, FQuat& CurrentOrientation);

	NOLOVR_API bool GetControllerOrientationAndPosition(EControllerHand Hand, FVector& CurrentPosition, FQuat& CurrentOrientation);

};