// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "../Launch/Resources/Version.h"
#if ENGINE_MINOR_VERSION >= 24
#define ModuleManagerHead "Modules/ModuleManager.h"
#else
#define ModuleManagerHead "ModuleManager.h"
#endif

#include ModuleManagerHead
#include "IHeadMountedDisplayModule.h"


#define NIBIRUVRHMD_SUPPORTED_ANDROID_PLATFORMS (PLATFORM_ANDROID)
#define NIBIRUVRHMD_SUPPORTED_PLATFORMS  (PLATFORM_ANDROID)

class INibiruHMDPlugin : public IHeadMountedDisplayModule
{
public:
	/**
	* Singleton-like access to this module's interface.  This is just for convenience!
	* Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	*
	* @return Returns singleton instance, loading the module on demand if needed
	*/
	static inline INibiruHMDPlugin& Get()
	{
		return FModuleManager::LoadModuleChecked< INibiruHMDPlugin >("NibiruHMD");
	}

	/**
	* Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	*
	* @return True if the module is loaded and ready to use
	*/
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("NibiruHMD");
	}

};