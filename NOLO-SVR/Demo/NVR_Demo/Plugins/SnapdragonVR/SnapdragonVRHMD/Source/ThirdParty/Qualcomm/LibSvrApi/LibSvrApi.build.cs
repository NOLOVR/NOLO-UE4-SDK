// Copyright (c) 2016 QUALCOMM Technologies Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
public class LibSvrApi : ModuleRules
{
    public LibSvrApi(ReadOnlyTargetRules Target) : base(Target)
	{
		// current version of the Snapdragon SDK
		Type = ModuleType.External;
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));

        //System.Console.WriteLine("[NSVR]"+Path.Combine(ModuleDirectory, "include"));

        //string SnapdragonThirdPartyDirectory = UEBuildConfiguration.UEThirdPartySourceDirectory + "Qualcomm/LibSvrApi";

        if (Target.Platform == UnrealTargetPlatform.Android)
		{
            //PublicLibraryPaths.Add(SnapdragonThirdPartyDirectory + "/Libs/Android/armeabi-v7a/");

			PublicLibraryPaths.Add(Path.Combine(ModuleDirectory, "Libs", "armeabi-v7a"));

            //PublicAdditionalLibraries.Add(SnapdragonThirdPartyDirectory + "/Libs/Android/armeabi-v7a/libsvrapi.so");

            PublicAdditionalLibraries.Add("svrapi");
			

            PublicSystemIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));
		}
	}
}
