// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "Classes/NOLOVRBlueprintFunctionLibrary.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNOLOVRBlueprintFunctionLibrary() {}
// Cross Module References
	NOLOVR_API UEnum* Z_Construct_UEnum_NoloVR_EMobileVR_HMDDeviceType();
	UPackage* Z_Construct_UPackage__Script_NoloVR();
	NOLOVR_API UEnum* Z_Construct_UEnum_NoloVR_ENoloDeviceType();
	NOLOVR_API UClass* Z_Construct_UClass_UNOLOVRBlueprintFunctionLibrary_NoRegister();
	NOLOVR_API UClass* Z_Construct_UClass_UNOLOVRBlueprintFunctionLibrary();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	NOLOVR_API UFunction* Z_Construct_UFunction_UNOLOVRBlueprintFunctionLibrary_GetElectricityByDeviceType();
	NOLOVR_API UFunction* Z_Construct_UFunction_UNOLOVRBlueprintFunctionLibrary_GetHandPositionAndOrientation();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	INPUTCORE_API UEnum* Z_Construct_UEnum_InputCore_EControllerHand();
	NOLOVR_API UFunction* Z_Construct_UFunction_UNOLOVRBlueprintFunctionLibrary_GetRunningPlatform();
	NOLOVR_API UFunction* Z_Construct_UFunction_UNOLOVRBlueprintFunctionLibrary_GetTrackedDevicePositionAndOrientation();
	NOLOVR_API UFunction* Z_Construct_UFunction_UNOLOVRBlueprintFunctionLibrary_GetTrackingStatusByDeviceType();
	NOLOVR_API UFunction* Z_Construct_UFunction_UNOLOVRBlueprintFunctionLibrary_ReportError();
	NOLOVR_API UFunction* Z_Construct_UFunction_UNOLOVRBlueprintFunctionLibrary_SetAppKey();
	NOLOVR_API UFunction* Z_Construct_UFunction_UNOLOVRBlueprintFunctionLibrary_SetHmdDeviceType();
// End Cross Module References
	static UEnum* EMobileVR_HMDDeviceType_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_NoloVR_EMobileVR_HMDDeviceType, Z_Construct_UPackage__Script_NoloVR(), TEXT("EMobileVR_HMDDeviceType"));
		}
		return Singleton;
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EMobileVR_HMDDeviceType(EMobileVR_HMDDeviceType_StaticEnum, TEXT("/Script/NoloVR"), TEXT("EMobileVR_HMDDeviceType"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_NoloVR_EMobileVR_HMDDeviceType_CRC() { return 1013188429U; }
	UEnum* Z_Construct_UEnum_NoloVR_EMobileVR_HMDDeviceType()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_NoloVR();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EMobileVR_HMDDeviceType"), 0, Get_Z_Construct_UEnum_NoloVR_EMobileVR_HMDDeviceType_CRC(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EMobileVR_HMDDeviceType::DT_GearVR", (int64)EMobileVR_HMDDeviceType::DT_GearVR },
				{ "EMobileVR_HMDDeviceType::DT_GoogleVR_Cardboard", (int64)EMobileVR_HMDDeviceType::DT_GoogleVR_Cardboard },
				{ "EMobileVR_HMDDeviceType::DT_GoogleVR_Daydream", (int64)EMobileVR_HMDDeviceType::DT_GoogleVR_Daydream },
				{ "EMobileVR_HMDDeviceType::DT_Other", (int64)EMobileVR_HMDDeviceType::DT_Other },
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "ModuleRelativePath", "Classes/NOLOVRBlueprintFunctionLibrary.h" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_NoloVR,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				"EMobileVR_HMDDeviceType",
				RF_Public|RF_Transient|RF_MarkAsNative,
				nullptr,
				(uint8)UEnum::ECppForm::EnumClass,
				"EMobileVR_HMDDeviceType",
				Enumerators,
				ARRAY_COUNT(Enumerators),
				METADATA_PARAMS(Enum_MetaDataParams, ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	static UEnum* ENoloDeviceType_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_NoloVR_ENoloDeviceType, Z_Construct_UPackage__Script_NoloVR(), TEXT("ENoloDeviceType"));
		}
		return Singleton;
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ENoloDeviceType(ENoloDeviceType_StaticEnum, TEXT("/Script/NoloVR"), TEXT("ENoloDeviceType"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_NoloVR_ENoloDeviceType_CRC() { return 649419695U; }
	UEnum* Z_Construct_UEnum_NoloVR_ENoloDeviceType()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_NoloVR();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ENoloDeviceType"), 0, Get_Z_Construct_UEnum_NoloVR_ENoloDeviceType_CRC(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "ENoloDeviceType::Hmd", (int64)ENoloDeviceType::Hmd },
				{ "ENoloDeviceType::Left", (int64)ENoloDeviceType::Left },
				{ "ENoloDeviceType::Right", (int64)ENoloDeviceType::Right },
				{ "ENoloDeviceType::Basestation", (int64)ENoloDeviceType::Basestation },
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "ModuleRelativePath", "Classes/NOLOVRBlueprintFunctionLibrary.h" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_NoloVR,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				"ENoloDeviceType",
				RF_Public|RF_Transient|RF_MarkAsNative,
				nullptr,
				(uint8)UEnum::ECppForm::EnumClass,
				"ENoloDeviceType",
				Enumerators,
				ARRAY_COUNT(Enumerators),
				METADATA_PARAMS(Enum_MetaDataParams, ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	void UNOLOVRBlueprintFunctionLibrary::StaticRegisterNativesUNOLOVRBlueprintFunctionLibrary()
	{
		UClass* Class = UNOLOVRBlueprintFunctionLibrary::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetElectricityByDeviceType", &UNOLOVRBlueprintFunctionLibrary::execGetElectricityByDeviceType },
			{ "GetHandPositionAndOrientation", &UNOLOVRBlueprintFunctionLibrary::execGetHandPositionAndOrientation },
			{ "GetRunningPlatform", &UNOLOVRBlueprintFunctionLibrary::execGetRunningPlatform },
			{ "GetTrackedDevicePositionAndOrientation", &UNOLOVRBlueprintFunctionLibrary::execGetTrackedDevicePositionAndOrientation },
			{ "GetTrackingStatusByDeviceType", &UNOLOVRBlueprintFunctionLibrary::execGetTrackingStatusByDeviceType },
			{ "ReportError", &UNOLOVRBlueprintFunctionLibrary::execReportError },
			{ "SetAppKey", &UNOLOVRBlueprintFunctionLibrary::execSetAppKey },
			{ "SetHmdDeviceType", &UNOLOVRBlueprintFunctionLibrary::execSetHmdDeviceType },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, ARRAY_COUNT(Funcs));
	}
	UFunction* Z_Construct_UFunction_UNOLOVRBlueprintFunctionLibrary_GetElectricityByDeviceType()
	{
		struct NOLOVRBlueprintFunctionLibrary_eventGetElectricityByDeviceType_Parms
		{
			ENoloDeviceType DeviceType;
			int32 battery;
			bool ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			auto NewProp_ReturnValue_SetBit = [](void* Obj){ ((NOLOVRBlueprintFunctionLibrary_eventGetElectricityByDeviceType_Parms*)Obj)->ReturnValue = 1; };
			static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Bool, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, sizeof(bool), UE4CodeGen_Private::ENativeBool::Native, sizeof(NOLOVRBlueprintFunctionLibrary_eventGetElectricityByDeviceType_Parms), &UE4CodeGen_Private::TBoolSetBitWrapper<decltype(NewProp_ReturnValue_SetBit)>::SetBit, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_battery = { UE4CodeGen_Private::EPropertyClass::Int, "battery", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000180, 1, nullptr, STRUCT_OFFSET(NOLOVRBlueprintFunctionLibrary_eventGetElectricityByDeviceType_Parms, battery), METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DeviceType_MetaData[] = {
				{ "NativeConst", "" },
			};
#endif
			static const UE4CodeGen_Private::FEnumPropertyParams NewProp_DeviceType = { UE4CodeGen_Private::EPropertyClass::Enum, "DeviceType", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000082, 1, nullptr, STRUCT_OFFSET(NOLOVRBlueprintFunctionLibrary_eventGetElectricityByDeviceType_Parms, DeviceType), Z_Construct_UEnum_NoloVR_ENoloDeviceType, METADATA_PARAMS(NewProp_DeviceType_MetaData, ARRAY_COUNT(NewProp_DeviceType_MetaData)) };
			static const UE4CodeGen_Private::FBytePropertyParams NewProp_DeviceType_Underlying = { UE4CodeGen_Private::EPropertyClass::Byte, "UnderlyingType", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000000000, 1, nullptr, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_battery,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_DeviceType,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_DeviceType_Underlying,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "NOLO VR" },
				{ "ModuleRelativePath", "Classes/NOLOVRBlueprintFunctionLibrary.h" },
				{ "ToolTip", "Get devices power information\n\n@param        ENoloDeviceType         Hmd,Left,Right,Basestation\n@param        battery                 (out)0:shut down ??1:low ??2:middle ??3:high\n@return       True if the battery info  is Available" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_UNOLOVRBlueprintFunctionLibrary, "GetElectricityByDeviceType", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x14422401, sizeof(NOLOVRBlueprintFunctionLibrary_eventGetElectricityByDeviceType_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_UNOLOVRBlueprintFunctionLibrary_GetHandPositionAndOrientation()
	{
		struct NOLOVRBlueprintFunctionLibrary_eventGetHandPositionAndOrientation_Parms
		{
			EControllerHand Hand;
			FVector OutPosition;
			FRotator OutOrientation;
			bool ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			auto NewProp_ReturnValue_SetBit = [](void* Obj){ ((NOLOVRBlueprintFunctionLibrary_eventGetHandPositionAndOrientation_Parms*)Obj)->ReturnValue = 1; };
			static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Bool, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, sizeof(bool), UE4CodeGen_Private::ENativeBool::Native, sizeof(NOLOVRBlueprintFunctionLibrary_eventGetHandPositionAndOrientation_Parms), &UE4CodeGen_Private::TBoolSetBitWrapper<decltype(NewProp_ReturnValue_SetBit)>::SetBit, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_OutOrientation = { UE4CodeGen_Private::EPropertyClass::Struct, "OutOrientation", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000180, 1, nullptr, STRUCT_OFFSET(NOLOVRBlueprintFunctionLibrary_eventGetHandPositionAndOrientation_Parms, OutOrientation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_OutPosition = { UE4CodeGen_Private::EPropertyClass::Struct, "OutPosition", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000180, 1, nullptr, STRUCT_OFFSET(NOLOVRBlueprintFunctionLibrary_eventGetHandPositionAndOrientation_Parms, OutPosition), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FEnumPropertyParams NewProp_Hand = { UE4CodeGen_Private::EPropertyClass::Enum, "Hand", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(NOLOVRBlueprintFunctionLibrary_eventGetHandPositionAndOrientation_Parms, Hand), Z_Construct_UEnum_InputCore_EControllerHand, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FBytePropertyParams NewProp_Hand_Underlying = { UE4CodeGen_Private::EPropertyClass::Byte, "UnderlyingType", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000000000, 1, nullptr, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_OutOrientation,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_OutPosition,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Hand,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Hand_Underlying,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "NOLO VR" },
				{ "ModuleRelativePath", "Classes/NOLOVRBlueprintFunctionLibrary.h" },
				{ "ToolTip", "Given a hand, returns the position and orientation of the controller\n\n@param        Hand                    Which hand's controller to get the position and orientation for\n@param        OutPosition             (out) Current position of the device\n@param        OutRotation             (out) Current rotation of the device\n@return       True if the specified controller is Available" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_UNOLOVRBlueprintFunctionLibrary, "GetHandPositionAndOrientation", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x14C22401, sizeof(NOLOVRBlueprintFunctionLibrary_eventGetHandPositionAndOrientation_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_UNOLOVRBlueprintFunctionLibrary_GetRunningPlatform()
	{
		struct NOLOVRBlueprintFunctionLibrary_eventGetRunningPlatform_Parms
		{
			FString ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FStrPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Str, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, STRUCT_OFFSET(NOLOVRBlueprintFunctionLibrary_eventGetRunningPlatform_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "NOLO VR" },
				{ "ModuleRelativePath", "Classes/NOLOVRBlueprintFunctionLibrary.h" },
				{ "ToolTip", "****Running Platform**" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_UNOLOVRBlueprintFunctionLibrary, "GetRunningPlatform", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x14022401, sizeof(NOLOVRBlueprintFunctionLibrary_eventGetRunningPlatform_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_UNOLOVRBlueprintFunctionLibrary_GetTrackedDevicePositionAndOrientation()
	{
		struct NOLOVRBlueprintFunctionLibrary_eventGetTrackedDevicePositionAndOrientation_Parms
		{
			FVector OutPosition;
			FRotator OutOrientation;
			bool ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			auto NewProp_ReturnValue_SetBit = [](void* Obj){ ((NOLOVRBlueprintFunctionLibrary_eventGetTrackedDevicePositionAndOrientation_Parms*)Obj)->ReturnValue = 1; };
			static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Bool, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, sizeof(bool), UE4CodeGen_Private::ENativeBool::Native, sizeof(NOLOVRBlueprintFunctionLibrary_eventGetTrackedDevicePositionAndOrientation_Parms), &UE4CodeGen_Private::TBoolSetBitWrapper<decltype(NewProp_ReturnValue_SetBit)>::SetBit, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_OutOrientation = { UE4CodeGen_Private::EPropertyClass::Struct, "OutOrientation", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000180, 1, nullptr, STRUCT_OFFSET(NOLOVRBlueprintFunctionLibrary_eventGetTrackedDevicePositionAndOrientation_Parms, OutOrientation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_OutPosition = { UE4CodeGen_Private::EPropertyClass::Struct, "OutPosition", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000180, 1, nullptr, STRUCT_OFFSET(NOLOVRBlueprintFunctionLibrary_eventGetTrackedDevicePositionAndOrientation_Parms, OutPosition), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_OutOrientation,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_OutPosition,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "NOLO VR" },
				{ "ModuleRelativePath", "Classes/NOLOVRBlueprintFunctionLibrary.h" },
				{ "ToolTip", "Gets the orientation and position (in device space) of the HMD\n\n@param        OutPosition             (out) Current position of the device\n@param        OutOrientation  (out) Current orientation of the device\n@return       True if the specified device id had a valid tracking pose this frame, false otherwise" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_UNOLOVRBlueprintFunctionLibrary, "GetTrackedDevicePositionAndOrientation", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x14C22401, sizeof(NOLOVRBlueprintFunctionLibrary_eventGetTrackedDevicePositionAndOrientation_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_UNOLOVRBlueprintFunctionLibrary_GetTrackingStatusByDeviceType()
	{
		struct NOLOVRBlueprintFunctionLibrary_eventGetTrackingStatusByDeviceType_Parms
		{
			ENoloDeviceType DeviceType;
			bool ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			auto NewProp_ReturnValue_SetBit = [](void* Obj){ ((NOLOVRBlueprintFunctionLibrary_eventGetTrackingStatusByDeviceType_Parms*)Obj)->ReturnValue = 1; };
			static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Bool, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, sizeof(bool), UE4CodeGen_Private::ENativeBool::Native, sizeof(NOLOVRBlueprintFunctionLibrary_eventGetTrackingStatusByDeviceType_Parms), &UE4CodeGen_Private::TBoolSetBitWrapper<decltype(NewProp_ReturnValue_SetBit)>::SetBit, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DeviceType_MetaData[] = {
				{ "NativeConst", "" },
			};
#endif
			static const UE4CodeGen_Private::FEnumPropertyParams NewProp_DeviceType = { UE4CodeGen_Private::EPropertyClass::Enum, "DeviceType", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000082, 1, nullptr, STRUCT_OFFSET(NOLOVRBlueprintFunctionLibrary_eventGetTrackingStatusByDeviceType_Parms, DeviceType), Z_Construct_UEnum_NoloVR_ENoloDeviceType, METADATA_PARAMS(NewProp_DeviceType_MetaData, ARRAY_COUNT(NewProp_DeviceType_MetaData)) };
			static const UE4CodeGen_Private::FBytePropertyParams NewProp_DeviceType_Underlying = { UE4CodeGen_Private::EPropertyClass::Byte, "UnderlyingType", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000000000, 1, nullptr, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_DeviceType,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_DeviceType_Underlying,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "NOLO VR" },
				{ "ModuleRelativePath", "Classes/NOLOVRBlueprintFunctionLibrary.h" },
				{ "ToolTip", "Get device tracking status\n\n@param        ENoloDeviceType         Hmd,Left,Right,Basestation\n@return       True ??Tracked ,false : not Tracked" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_UNOLOVRBlueprintFunctionLibrary, "GetTrackingStatusByDeviceType", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x14022401, sizeof(NOLOVRBlueprintFunctionLibrary_eventGetTrackingStatusByDeviceType_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_UNOLOVRBlueprintFunctionLibrary_ReportError()
	{
		struct NOLOVRBlueprintFunctionLibrary_eventReportError_Parms
		{
			FString errorMsg;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FStrPropertyParams NewProp_errorMsg = { UE4CodeGen_Private::EPropertyClass::Str, "errorMsg", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(NOLOVRBlueprintFunctionLibrary_eventReportError_Parms, errorMsg), METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_errorMsg,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "NOLO VR" },
				{ "ModuleRelativePath", "Classes/NOLOVRBlueprintFunctionLibrary.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_UNOLOVRBlueprintFunctionLibrary, "ReportError", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04022401, sizeof(NOLOVRBlueprintFunctionLibrary_eventReportError_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_UNOLOVRBlueprintFunctionLibrary_SetAppKey()
	{
		struct NOLOVRBlueprintFunctionLibrary_eventSetAppKey_Parms
		{
			FString appKey;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FStrPropertyParams NewProp_appKey = { UE4CodeGen_Private::EPropertyClass::Str, "appKey", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(NOLOVRBlueprintFunctionLibrary_eventSetAppKey_Parms, appKey), METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_appKey,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "NOLO VR" },
				{ "ModuleRelativePath", "Classes/NOLOVRBlueprintFunctionLibrary.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_UNOLOVRBlueprintFunctionLibrary, "SetAppKey", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04022401, sizeof(NOLOVRBlueprintFunctionLibrary_eventSetAppKey_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_UNOLOVRBlueprintFunctionLibrary_SetHmdDeviceType()
	{
		struct NOLOVRBlueprintFunctionLibrary_eventSetHmdDeviceType_Parms
		{
			EMobileVR_HMDDeviceType DeviceType;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DeviceType_MetaData[] = {
				{ "NativeConst", "" },
			};
#endif
			static const UE4CodeGen_Private::FEnumPropertyParams NewProp_DeviceType = { UE4CodeGen_Private::EPropertyClass::Enum, "DeviceType", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000082, 1, nullptr, STRUCT_OFFSET(NOLOVRBlueprintFunctionLibrary_eventSetHmdDeviceType_Parms, DeviceType), Z_Construct_UEnum_NoloVR_EMobileVR_HMDDeviceType, METADATA_PARAMS(NewProp_DeviceType_MetaData, ARRAY_COUNT(NewProp_DeviceType_MetaData)) };
			static const UE4CodeGen_Private::FBytePropertyParams NewProp_DeviceType_Underlying = { UE4CodeGen_Private::EPropertyClass::Byte, "UnderlyingType", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000000000, 1, nullptr, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_DeviceType,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_DeviceType_Underlying,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "NOLO VR" },
				{ "ModuleRelativePath", "Classes/NOLOVRBlueprintFunctionLibrary.h" },
				{ "ToolTip", "Set the type of helmet you are using to develop the game\n@param EMobileVR_HMDDeviceType" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_UNOLOVRBlueprintFunctionLibrary, "SetHmdDeviceType", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04022401, sizeof(NOLOVRBlueprintFunctionLibrary_eventSetHmdDeviceType_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UNOLOVRBlueprintFunctionLibrary_NoRegister()
	{
		return UNOLOVRBlueprintFunctionLibrary::StaticClass();
	}
	UClass* Z_Construct_UClass_UNOLOVRBlueprintFunctionLibrary()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
				(UObject* (*)())Z_Construct_UPackage__Script_NoloVR,
			};
			static const FClassFunctionLinkInfo FuncInfo[] = {
				{ &Z_Construct_UFunction_UNOLOVRBlueprintFunctionLibrary_GetElectricityByDeviceType, "GetElectricityByDeviceType" }, // 518622702
				{ &Z_Construct_UFunction_UNOLOVRBlueprintFunctionLibrary_GetHandPositionAndOrientation, "GetHandPositionAndOrientation" }, // 3556272710
				{ &Z_Construct_UFunction_UNOLOVRBlueprintFunctionLibrary_GetRunningPlatform, "GetRunningPlatform" }, // 2808791202
				{ &Z_Construct_UFunction_UNOLOVRBlueprintFunctionLibrary_GetTrackedDevicePositionAndOrientation, "GetTrackedDevicePositionAndOrientation" }, // 507626727
				{ &Z_Construct_UFunction_UNOLOVRBlueprintFunctionLibrary_GetTrackingStatusByDeviceType, "GetTrackingStatusByDeviceType" }, // 2963207907
				{ &Z_Construct_UFunction_UNOLOVRBlueprintFunctionLibrary_ReportError, "ReportError" }, // 2201521978
				{ &Z_Construct_UFunction_UNOLOVRBlueprintFunctionLibrary_SetAppKey, "SetAppKey" }, // 4065742144
				{ &Z_Construct_UFunction_UNOLOVRBlueprintFunctionLibrary_SetHmdDeviceType, "SetHmdDeviceType" }, // 3633209364
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "IncludePath", "NOLOVRBlueprintFunctionLibrary.h" },
				{ "ModuleRelativePath", "Classes/NOLOVRBlueprintFunctionLibrary.h" },
			};
#endif
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<UNOLOVRBlueprintFunctionLibrary>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&UNOLOVRBlueprintFunctionLibrary::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x00100080u,
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
	IMPLEMENT_CLASS(UNOLOVRBlueprintFunctionLibrary, 1155220156);
	static FCompiledInDefer Z_CompiledInDefer_UClass_UNOLOVRBlueprintFunctionLibrary(Z_Construct_UClass_UNOLOVRBlueprintFunctionLibrary, &UNOLOVRBlueprintFunctionLibrary::StaticClass, TEXT("/Script/NoloVR"), TEXT("UNOLOVRBlueprintFunctionLibrary"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UNOLOVRBlueprintFunctionLibrary);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
