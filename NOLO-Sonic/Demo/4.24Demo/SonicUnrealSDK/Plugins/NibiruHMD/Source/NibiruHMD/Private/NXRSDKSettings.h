// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NXRSDKSettings.generated.h"

UENUM()
enum ESixDofMode
{
	Head_3DOF_Ctrl_3DOF,
	Head_3DOF_Ctrl_6DOF,
	Head_6DOF_Ctrl_6DOF
};


/**
 * 
 */
UCLASS(config = Engine, defaultconfig)
class NIBIRUHMD_API UNXRSDKSettings : public UObject
{
	GENERATED_BODY()

    UNXRSDKSettings();
public:
	UPROPERTY(Config, EditAnywhere, Category = NXR, Meta = (DisplayName = "Pro Key Content", 
		ToolTip = "Input Pro SDK Key Content"))
		FString SDKKeyContent = "";

	//UPROPERTY(Config, EditAnywhere, Category = NXR, Meta = (DisplayName = "SixDof Mode", 
	//	ToolTip = "Choose the mode of SixDof"))
	//	TEnumAsByte<ESixDofMode> SixDofMode;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif // WITH_EDITOR
};
