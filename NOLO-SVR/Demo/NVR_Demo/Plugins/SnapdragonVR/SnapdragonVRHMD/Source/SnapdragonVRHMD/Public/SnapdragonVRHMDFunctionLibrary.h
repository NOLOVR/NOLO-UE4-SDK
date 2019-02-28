#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "../Classes/SnapdragonVRHMDEventManager.h"
#include "SnapdragonVRHMDFunctionLibrary.generated.h"

UCLASS()
class USnapdragonVRHMDFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* Sets Snapdragon VR CPU and GPU performance Levels
	*
	* @param CpuLevel			(in) 0 = kPerfSystem = system-defined; 1 = kPerfMinimum = Minimum performance level (default 30-50% of max frequency); 2 = kPerfMedium = Medium performance level (default 51-80% of max frequency), 3 = kPerfMaximum = Maximum performance level (default 81-100% of max frequency)
	* @param GpuLevel			(in) 0 = kPerfSystem = system-defined; 1 = kPerfMinimum = Minimum performance level (default 30-50% of max frequency); 2 = kPerfMedium = Medium performance level (default 51-80% of max frequency), 3 = kPerfMaximum = Maximum performance level (default 81-100% of max frequency)
	*/
	UFUNCTION(BlueprintCallable, Category = "SnapdragonVR")
	static void SetCpuAndGpuLevelsSVR(const int32 CpuLevel, const int32 GpuLevel);

	UFUNCTION(BlueprintCallable, Category = "SnapdragonVR", meta = (Keywords = "SnapdragonVR"))
	static USnapdragonVRHMDEventManager* GetSnapdragonVRHMDEventManager();
};
