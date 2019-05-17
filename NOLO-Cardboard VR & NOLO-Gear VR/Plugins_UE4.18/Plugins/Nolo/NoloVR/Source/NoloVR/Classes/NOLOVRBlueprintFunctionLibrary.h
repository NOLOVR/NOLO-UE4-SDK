// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NOLOVRBlueprintFunctionLibrary.generated.h"
UENUM(BlueprintType)
enum class ENoloDeviceType : uint8
{
	Hmd,
	Left,
	Right,
	Basestation
};
UENUM(BlueprintType)
enum class EMobileVR_HMDDeviceType : uint8
{
	DT_GearVR,
	DT_GoogleVR_Cardboard,
	DT_GoogleVR_Daydream,
	DT_Other
};
/**
*
*/
UCLASS()
class NOLOVR_API UNOLOVRBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/*
	****Running Platform**
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "NOLO VR")
		static FString GetRunningPlatform();
	/**
	* Set the type of helmet you are using to develop the game
	* @param EMobileVR_HMDDeviceType 
	*/
	UFUNCTION(BlueprintCallable, Category = "NOLO VR")
		static void SetHmdDeviceType(const EMobileVR_HMDDeviceType DeviceType);
	/**
	* Gets the orientation and position (in device space) of the HMD
	*
	* @param	OutPosition		(out) Current position of the device
	* @param	OutOrientation	(out) Current orientation of the device
	* @return	True if the specified device id had a valid tracking pose this frame, false otherwise
	*/
	UFUNCTION(BlueprintPure, Category = "NOLO VR")
		static bool GetTrackedDevicePositionAndOrientation(FVector& OutPosition, FRotator& OutOrientation);
	/**
	* Given a hand, returns the position and orientation of the controller
	*
	* @param	Hand			Which hand's controller to get the position and orientation for
	* @param	OutPosition		(out) Current position of the device
	* @param	OutRotation		(out) Current rotation of the device
	* @return	True if the specified controller is Available
	*/
	UFUNCTION(BlueprintPure, Category = "NOLO VR")
		static bool GetHandPositionAndOrientation(EControllerHand Hand, FVector& OutPosition, FRotator& OutOrientation);
	/**
	* Get device tracking status
	*
	* @param	ENoloDeviceType		Hmd,Left,Right,Basestation		
	* @return	True £ºTracked ,false : not Tracked
	*/
	UFUNCTION(BlueprintPure, Category = "NOLO VR")
		static bool GetTrackingStatusByDeviceType(const ENoloDeviceType DeviceType);
	/**
	* Get devices power information
	*
	* @param	ENoloDeviceType		Hmd,Left,Right,Basestation
	* @param	battery		        (out)0:shut down ¡¢1:low ¡¢2:middle ¡¢3:high
	* @return	True if the battery info  is Available
	*/
	UFUNCTION(BlueprintPure, Category = "NOLO VR")
		static bool GetElectricityByDeviceType(const ENoloDeviceType DeviceType,int & battery);

	/**
	* Set vibration functions of NOLO controller
	*
	* @param	EControllerHand	 Which hand's controller to  vibrate
	* @param	intensity        Vibration intensity range from 0~100, the bigger the stronger
	* @return	True if the vibration is Available
	*/
	//UFUNCTION(BlueprintPure, Category = "NOLO VR")
	//	static bool SetTriggerHapticPulse(const EControllerHand DeviceHand, int intensity);

	/**
    *
	*/
	UFUNCTION(BlueprintCallable, Category = "NOLO VR")
		static void SetAppKey(FString appKey);

	///**
	//*
	//*/
	UFUNCTION(BlueprintCallable, Category = "NOLO VR")
		static void ReportError(FString errorMsg);

	///**
	//*
	//*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "NOLO VR")
		static bool IsInstallNoloHome();

	///**
	//*
	//*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "NOLO VR")
		static bool IsStartUpNoloHome();
};
