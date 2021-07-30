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

	bool IsInstallNoloHome()const;

	bool IsStartUpNoloHome()const;
public:
	NOLOVR_API bool TriggerHapticPulse(EControllerHand Hand, int intensity);

	NOLOVR_API int GetTrackingStatusByDeviceType(const int DeviceType) const;

	NOLOVR_API NControllerState GetControllerStateByDeviceType(int type);

	NOLOVR_API bool GetTrackedDevicePositionAndOrientation(FVector& CurrentPosition, FQuat& CurrentOrientation);

	NOLOVR_API bool GetControllerOrientationAndPosition(EControllerHand Hand, FVector& CurrentPosition, FQuat& CurrentOrientation);
	/**
	******************************************************************************
	* Function description����ȡ��Ʒ����
	* Parameter��
	C1 = 0,
	CV1 = 1,
	CV1Pro = 2,
	Air = 3,
	M1 = 4
	******************************************************************************
	*/
	NOLOVR_API int GetNoloProductType() const;

	NOLOVR_API void HapticWithArg(EControllerHand Hand, float duration, float frequency, float amplitude);

	NOLOVR_API void HapticWithAudioFile(char* path, int channel_number);

	NOLOVR_API void SetHapticAudioConfig(int layout, int format, int sample_rate, int channel_number);

	NOLOVR_API void HapticWithAudioBuffer(uint8_t *buffer, int nb_samples, int channel_number);

	NOLOVR_API bool StopHaptic(int channel_number);

	NOLOVR_API bool HapticWithAudioFileLoop(char* path, int channel_number, int loopCount);

	NOLOVR_API bool HapticWithConfig(float strength,int filtering,int channel_number);

	NOLOVR_API bool Action(char *actionJson);

	NOLOVR_API bool M1Write(const void *buffer,uint32_t size);

};