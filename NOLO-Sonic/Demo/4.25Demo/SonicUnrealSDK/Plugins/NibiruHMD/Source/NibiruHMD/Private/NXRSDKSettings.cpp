// Fill out your copyright notice in the Description page of Project Settings.


#include "NXRSDKSettings.h"

UNXRSDKSettings::UNXRSDKSettings()
	: Super(),
	SDKKeyContent("MoGflG1iN2c.")
{
}

#if WITH_EDITOR
void UNXRSDKSettings::PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	Super::UpdateDefaultConfigFile();
}
#endif // #if WITH_EDITOR