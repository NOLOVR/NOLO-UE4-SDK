// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "NoloVRControllerLibrary.generated.h"

/** Defines the set of input events you want associated with your NoloVR d-pad buttons */
UENUM(BlueprintType)
enum class ENoloVRTouchDPadMapping : uint8
{
	/** Maps each controller's four touchpad buttons to the respective FaceButton1/2/3/4 events */
	FaceButtons,

	/** Maps each controller's four touchpad buttons to the respective Up/Down/Left/Right events  */
	ThumbstickDirections,

	/** Unmaps all directional touchpad input so that the d-pad buttons won't trigger their own input events */
	Disabled
};

/** */
UCLASS()
class NOLOVRCONTROLLER_API UNoloVRControllerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	 * Sets which input events you want associated with the NoloVR controller's 
	 * directional touchpad buttons - does so for both left and right controllers.
	 *
	 * @param  NewMapping	Defines the set of input events you want associated with the four directional touchpad buttons.
	 */
	UFUNCTION(BlueprintCallable, Category="NoloVR")
	static void SetTouchDPadMapping(ENoloVRTouchDPadMapping NewMapping = ENoloVRTouchDPadMapping::FaceButtons); // @see NoloVRController.cpp for implementation
};
