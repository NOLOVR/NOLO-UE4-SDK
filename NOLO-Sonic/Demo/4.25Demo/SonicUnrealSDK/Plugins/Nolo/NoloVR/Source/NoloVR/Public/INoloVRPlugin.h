// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Modules/ModuleManager.h"
#include "INoloVRDeviceModule.h"

#define PC_PLATFORMS (PLATFORM_WINDOWS && WINVER > 0x0502)
#define ANDROID_PLATFORMS (PLATFORM_ANDROID)
#define NOLOVR_SUPPORTED_EMULATOR_PLATFORMS (WITH_EDITOR)
#define NOLOVR_SUPPORTED_PC_PLATFORMS (PC_PLATFORMS || NOLOVR_SUPPORTED_EMULATOR_PLATFORMS)
#define NOLOVR_SUPPORTED_Android_PLATFORMS (ANDROID_PLATFORMS || NOLOVR_SUPPORTED_EMULATOR_PLATFORMS)


class INoloVRPlugin : public INoloVRDeviceModule
{

public:
/**
	* Singleton-like access to this module's interface.  This is just for convenience!
	* Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	*
	* @return Returns singleton instance, loading the module on demand if needed
	*/
	static inline INoloVRPlugin& Get()
	{
		return FModuleManager::LoadModuleChecked<INoloVRPlugin>("NoloVR");
	}

	/**
	* Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	*
	* @return True if the module is loaded and ready to use
	*/
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("NoloVR");
	}
};
