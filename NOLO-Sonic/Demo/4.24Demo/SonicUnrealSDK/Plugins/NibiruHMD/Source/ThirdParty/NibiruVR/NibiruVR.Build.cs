// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;

// 类名与文件夹，cs文件一致
public class NibiruVR : ModuleRules
{
    public NibiruVR(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;
        string BasePath = ModuleDirectory;
        if(!Directory.Exists(BasePath)){
            string Err = string.Format("NibiruSDK not found in {0}",BasePath);
            System.Console.WriteLine(Err);
            return;
        }

	    string NibiruVRSDKDir = BasePath;

        System.Console.WriteLine("RUN-------NibiruVR.Build.cs---------------"+NibiruVRSDKDir);

        PublicSystemIncludePaths.AddRange(
			new string[] {
					NibiruVRSDKDir + "/include",
				}
			);

		string NibiruVRBaseLibPath = NibiruVRSDKDir + "/lib/";
		
		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			string NibiruVRArmLibPath = NibiruVRBaseLibPath + "android_arm/";


			// toolchain will filter properly
			//PublicLibraryPaths.Add(NibiruVRArmLibPath);

			//PublicAdditionalLibraries.Add("nvr_v2_ue");
            
        }
		
    }
}
