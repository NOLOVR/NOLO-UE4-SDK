// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "Private/SnapdragonVRHMD.h"
#include "Public/SnapdragonVRHMDFunctionLibrary.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSnapdragonVRHMDFunctionLibrary() {}
// Cross Module References
	SNAPDRAGONVRHMD_API UClass* Z_Construct_UClass_USnapdragonVRHMDFunctionLibrary_NoRegister();
	SNAPDRAGONVRHMD_API UClass* Z_Construct_UClass_USnapdragonVRHMDFunctionLibrary();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	UPackage* Z_Construct_UPackage__Script_SnapdragonVRHMD();
	SNAPDRAGONVRHMD_API UFunction* Z_Construct_UFunction_USnapdragonVRHMDFunctionLibrary_GetSnapdragonVRHMDEventManager();
	SNAPDRAGONVRHMD_API UClass* Z_Construct_UClass_USnapdragonVRHMDEventManager_NoRegister();
	SNAPDRAGONVRHMD_API UFunction* Z_Construct_UFunction_USnapdragonVRHMDFunctionLibrary_SetCpuAndGpuLevelsSVR();
// End Cross Module References
	void USnapdragonVRHMDFunctionLibrary::StaticRegisterNativesUSnapdragonVRHMDFunctionLibrary()
	{
		UClass* Class = USnapdragonVRHMDFunctionLibrary::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetSnapdragonVRHMDEventManager", &USnapdragonVRHMDFunctionLibrary::execGetSnapdragonVRHMDEventManager },
			{ "SetCpuAndGpuLevelsSVR", &USnapdragonVRHMDFunctionLibrary::execSetCpuAndGpuLevelsSVR },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, ARRAY_COUNT(Funcs));
	}
	UFunction* Z_Construct_UFunction_USnapdragonVRHMDFunctionLibrary_GetSnapdragonVRHMDEventManager()
	{
		struct SnapdragonVRHMDFunctionLibrary_eventGetSnapdragonVRHMDEventManager_Parms
		{
			USnapdragonVRHMDEventManager* ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Object, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, STRUCT_OFFSET(SnapdragonVRHMDFunctionLibrary_eventGetSnapdragonVRHMDEventManager_Parms, ReturnValue), Z_Construct_UClass_USnapdragonVRHMDEventManager_NoRegister, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "SnapdragonVR" },
				{ "Keywords", "SnapdragonVR" },
				{ "ModuleRelativePath", "Public/SnapdragonVRHMDFunctionLibrary.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_USnapdragonVRHMDFunctionLibrary, "GetSnapdragonVRHMDEventManager", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04022401, sizeof(SnapdragonVRHMDFunctionLibrary_eventGetSnapdragonVRHMDEventManager_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_USnapdragonVRHMDFunctionLibrary_SetCpuAndGpuLevelsSVR()
	{
		struct SnapdragonVRHMDFunctionLibrary_eventSetCpuAndGpuLevelsSVR_Parms
		{
			int32 CpuLevel;
			int32 GpuLevel;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GpuLevel_MetaData[] = {
				{ "NativeConst", "" },
			};
#endif
			static const UE4CodeGen_Private::FIntPropertyParams NewProp_GpuLevel = { UE4CodeGen_Private::EPropertyClass::Int, "GpuLevel", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000082, 1, nullptr, STRUCT_OFFSET(SnapdragonVRHMDFunctionLibrary_eventSetCpuAndGpuLevelsSVR_Parms, GpuLevel), METADATA_PARAMS(NewProp_GpuLevel_MetaData, ARRAY_COUNT(NewProp_GpuLevel_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CpuLevel_MetaData[] = {
				{ "NativeConst", "" },
			};
#endif
			static const UE4CodeGen_Private::FIntPropertyParams NewProp_CpuLevel = { UE4CodeGen_Private::EPropertyClass::Int, "CpuLevel", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000082, 1, nullptr, STRUCT_OFFSET(SnapdragonVRHMDFunctionLibrary_eventSetCpuAndGpuLevelsSVR_Parms, CpuLevel), METADATA_PARAMS(NewProp_CpuLevel_MetaData, ARRAY_COUNT(NewProp_CpuLevel_MetaData)) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_GpuLevel,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_CpuLevel,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "SnapdragonVR" },
				{ "ModuleRelativePath", "Public/SnapdragonVRHMDFunctionLibrary.h" },
				{ "ToolTip", "Sets Snapdragon VR CPU and GPU performance Levels\n\n@param CpuLevel                       (in) 0 = kPerfSystem = system-defined; 1 = kPerfMinimum = Minimum performance level (default 30-50% of max frequency); 2 = kPerfMedium = Medium performance level (default 51-80% of max frequency), 3 = kPerfMaximum = Maximum performance level (default 81-100% of max frequency)\n@param GpuLevel                       (in) 0 = kPerfSystem = system-defined; 1 = kPerfMinimum = Minimum performance level (default 30-50% of max frequency); 2 = kPerfMedium = Medium performance level (default 51-80% of max frequency), 3 = kPerfMaximum = Maximum performance level (default 81-100% of max frequency)" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_USnapdragonVRHMDFunctionLibrary, "SetCpuAndGpuLevelsSVR", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04022401, sizeof(SnapdragonVRHMDFunctionLibrary_eventSetCpuAndGpuLevelsSVR_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_USnapdragonVRHMDFunctionLibrary_NoRegister()
	{
		return USnapdragonVRHMDFunctionLibrary::StaticClass();
	}
	UClass* Z_Construct_UClass_USnapdragonVRHMDFunctionLibrary()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
				(UObject* (*)())Z_Construct_UPackage__Script_SnapdragonVRHMD,
			};
			static const FClassFunctionLinkInfo FuncInfo[] = {
				{ &Z_Construct_UFunction_USnapdragonVRHMDFunctionLibrary_GetSnapdragonVRHMDEventManager, "GetSnapdragonVRHMDEventManager" }, // 2870979707
				{ &Z_Construct_UFunction_USnapdragonVRHMDFunctionLibrary_SetCpuAndGpuLevelsSVR, "SetCpuAndGpuLevelsSVR" }, // 2140764830
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "IncludePath", "SnapdragonVRHMDFunctionLibrary.h" },
				{ "ModuleRelativePath", "Public/SnapdragonVRHMDFunctionLibrary.h" },
			};
#endif
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<USnapdragonVRHMDFunctionLibrary>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&USnapdragonVRHMDFunctionLibrary::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x00000080u,
				FuncInfo, ARRAY_COUNT(FuncInfo),
				nullptr, 0,
				nullptr,
				&StaticCppClassTypeInfo,
				nullptr, 0,
				METADATA_PARAMS(Class_MetaDataParams, ARRAY_COUNT(Class_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUClass(OuterClass, ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(USnapdragonVRHMDFunctionLibrary, 2366516356);
	static FCompiledInDefer Z_CompiledInDefer_UClass_USnapdragonVRHMDFunctionLibrary(Z_Construct_UClass_USnapdragonVRHMDFunctionLibrary, &USnapdragonVRHMDFunctionLibrary::StaticClass, TEXT("/Script/SnapdragonVRHMD"), TEXT("USnapdragonVRHMDFunctionLibrary"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USnapdragonVRHMDFunctionLibrary);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
