// Copyright (c) 2016 QUALCOMM Technologies Inc. All Rights Reserved.

using System.IO;

namespace UnrealBuildTool.Rules
{
	public class SnapdragonVRHMD : ModuleRules
	{
        public SnapdragonVRHMD(ReadOnlyTargetRules Target) : base(Target)
		{
            //Debug.Print("Build the SnapdragonVRHMD Plugin");
            var EngineDir = Path.GetFullPath(Target.RelativeEnginePath);

            var rendererPrivatePath = Path.Combine(EngineDir, @"Source/Runtime/Renderer/Private");
            var corePrivatePath = Path.Combine(EngineDir, "Source/Runtime/Core/Private");
            var launchPrivatePath = Path.Combine(EngineDir, "Source/Runtime/Launch/Private");
            var openglDrvPrivatePath = Path.Combine(EngineDir, @"Source/Runtime/OpenGLDrv/Private");
            var openglPath =Path.Combine(EngineDir, @"Source\ThirdParty\OpenGL");

            PrivateIncludePaths.AddRange(
				new string[] {
					"SnapdragonVRHMD/Private",
					rendererPrivatePath,
					corePrivatePath,
					openglDrvPrivatePath,
                    openglPath
                    //"../../../../../Source/Runtime/Renderer/Private",
                    //"../../../../../Source/Runtime/Core/Private"
					// ... add other private include paths required here ...
				}
				);
            PublicIncludePaths.AddRange(
                new string[] {
                    "SnapdragonVRHMD/Public",
                    // ... add public include paths required here ...
                }
                );
			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					"Engine",
					"InputCore",
					"RHI",
					"RenderCore",
					"Renderer",
					"ShaderCore",
                    "HeadMountedDisplay",
                    "OpenGLDrv",
                    "Slate",
                    "SlateCore",
                    "LibSvrApi",
                    "NoloVR"
                }
				);
            PrivateIncludePathModuleNames.AddRange(new string[]
            {
                    "NoloVR"
            });
            if (Target.Platform == UnrealTargetPlatform.Android)
            {
                PrivateDependencyModuleNames.Add("Launch");
            }
			AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenGL");
            // PrivateIncludePaths.AddRange(
			// 	new string[] {
            //         openglDrvPrivatePath
			// 		//"../../../../../Source/Runtime/OpenGLDrv/Private",
			// 		// ... add other private include paths required here ...
			// 		}
			// 	);
			if (Target.Platform == UnrealTargetPlatform.Android)
			{
				//PrivateDependencyModuleNames.AddRange(new string[] { "LibSvrApi" });
				string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
                AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "SnapdragonVRHMD_APL.xml"));
			}

		}
	}
}
