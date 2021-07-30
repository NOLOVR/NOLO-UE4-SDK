// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Features/IModularFeature.h"
/**
 * The public interface of the INoloDevice
 */
class  INoloVRDevice : public IModularFeature{
public:
	static FName GetModularFeatureName()
	{
		static FName FeatureName = FName(TEXT("NoloVRHMD"));
		return FeatureName;
	}
	/**
	* Returns the device type of the NoloVR.
	*
	* @return	Device type of the NoloVR.
	*/
	virtual FName GetNoloVRDeviceTypeName() const = 0;
};
