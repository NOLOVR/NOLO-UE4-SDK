// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
using System.IO;
using UnrealBuildTool;

public class NoloVR : ModuleRules
{
	public NoloVR(ReadOnlyTargetRules Target): base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
                "NoloVR/Private"
				// ... add other private include paths required here ...
			}
			);

        
        PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Projects",
				"AndroidRuntimeSettings",
				"NOLOLibrary",
				// ... 	,add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "Core",
                "CoreUObject",
                "Engine",
                "NOLOLibrary",
                "InputCore",
                "Slate",
                "SlateCore"
				// ... add private dependencies that you statically link with here ...	
			}
			);

        DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
        if (Target.Platform == UnrealTargetPlatform.Android)
        {
	        PrivateDependencyModuleNames.AddRange(
		        new string[]
		        {
			        "Launch",
			        "AndroidRuntimeSettings",
		        }
	        );
            string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "NoloVR_APL.xml"));
        }

    }
}
