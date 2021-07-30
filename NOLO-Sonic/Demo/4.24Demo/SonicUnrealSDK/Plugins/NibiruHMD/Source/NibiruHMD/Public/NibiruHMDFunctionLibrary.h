// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NibiruHMDFunctionLibrary.generated.h"


DECLARE_DYNAMIC_DELEGATE_TwoParams(FNibiruKeyEventCallbackDelegate, int32, nibiruKeyCode, int32, nibiruKeyAction);

DECLARE_DYNAMIC_DELEGATE_OneParam(FNibVerifyCallbackDelegate, const FString&, Code);

/**
 * 
 */
UCLASS()
class NIBIRUHMD_API UNibiruHMDFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	//static FNibiruKeyEventCallbackDelegate NibiruKeyEventCallback;

	/** Enable/disable DistortionCorrection */
	//UFUNCTION(BlueprintCallable, Category = "Nibiru | Other", meta = (Keywords = "Nibiru Test"))
 //   static void SetDistortionCorrectionMethod(bool bEnable);

	/** Set the key event callback */
	UFUNCTION(BlueprintCallable, Category = "Nibiru | KeyEvent")
	static void NibiruSetCallbackDelegates(FNibiruKeyEventCallbackDelegate OnNibiruKeyEventCallback);

	UFUNCTION(BlueprintCallable, Category = "Nibiru | Gaze")
	static void NibiruSetGazeEnabled(bool show);
	
	UFUNCTION(BlueprintCallable, Category = "Nibiru | Gaze")
	static void NibiruSetGazePosZ(float z);

	UFUNCTION(BlueprintCallable, Category = "Nibiru | Hmd")
		static FVector NibiruGetHmdPosition();

	UFUNCTION(BlueprintCallable, Category = "Nibiru | Hmd")
		static void NibiruQuitGame();

	UFUNCTION(BlueprintCallable, Category = "Nibiru | Hmd")
		static int NibiruGetVerifyStatus();
};
