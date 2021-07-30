// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


using System.IO;
using UnrealBuildTool;

public class NibiruHMD : ModuleRules
{
	public NibiruHMD(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        //Unreal engine install path
        string ue4_include_path = Path.GetFullPath(Path.Combine(Target.RelativeEnginePath, "Source/Runtime/Renderer/Private"));
        string ue4_include_path2 = Path.GetFullPath(Path.Combine(Target.RelativeEnginePath, "Source/Runtime/Core/Private"));
        string ue4_include_path3 = Path.GetFullPath(Path.Combine(Target.RelativeEnginePath, "Source/Runtime/Launch/Private"));
        string ue4_include_path4 = Path.GetFullPath(Path.Combine(Target.RelativeEnginePath, "Source/Runtime/OpenGLDrv/Private"));
        string ue4_include_path5 = Path.GetFullPath(Path.Combine(Target.RelativeEnginePath, "Source/Runtime/ApplicationCore/Private"));
        PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
                "NibiruHMD/Private",
                ue4_include_path,
                ue4_include_path2,
                ue4_include_path3,
                ue4_include_path4,
                ue4_include_path5
            }
			);

        PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "RHI",
                    "RenderCore",
                    "Renderer",
                    "HeadMountedDisplay",
                    "InputCore"
				// ... add private dependencies that you statically link with here ...	
			}
		);

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PrivateDependencyModuleNames.Add("Launch");
        }

        PrivateDependencyModuleNames.Add("OpenGLDrv");
        AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenGL");

        if (Target.bBuildEditor == true)
        {
            System.Console.WriteLine("RUN-------is BuildEditor");
            PrivateDependencyModuleNames.AddRange(
                    new string[]
                    {
                        "UnrealEd"
                    });
        }

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PrivateDependencyModuleNames.AddRange(new string[] {
                  "NibiruVR"
            });

            string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "NibiruVRHMD_APL.xml"));

        }

    }
}
