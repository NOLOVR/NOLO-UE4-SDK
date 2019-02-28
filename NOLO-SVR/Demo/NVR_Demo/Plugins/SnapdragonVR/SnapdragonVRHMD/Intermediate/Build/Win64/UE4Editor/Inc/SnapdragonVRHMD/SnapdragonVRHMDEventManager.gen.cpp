// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "Private/SnapdragonVRHMD.h"
#include "Classes/SnapdragonVRHMDEventManager.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSnapdragonVRHMDEventManager() {}
// Cross Module References
	SNAPDRAGONVRHMD_API UFunction* Z_Construct_UDelegateFunction_SnapdragonVRHMD_SnapdragonVRSensorDelegate__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_SnapdragonVRHMD();
	SNAPDRAGONVRHMD_API UEnum* Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRSensorEventType();
	SNAPDRAGONVRHMD_API UFunction* Z_Construct_UDelegateFunction_SnapdragonVRHMD_SnapdragonVRModeDelegate__DelegateSignature();
	SNAPDRAGONVRHMD_API UEnum* Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRModeEventType();
	SNAPDRAGONVRHMD_API UFunction* Z_Construct_UDelegateFunction_SnapdragonVRHMD_SnapdragonVRThermalDelegate__DelegateSignature();
	SNAPDRAGONVRHMD_API UEnum* Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRThermalLevel();
	SNAPDRAGONVRHMD_API UEnum* Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRThermalZone();
	SNAPDRAGONVRHMD_API UFunction* Z_Construct_UDelegateFunction_SnapdragonVRHMD_SnapdragonVRSdkServiceDelegate__DelegateSignature();
	SNAPDRAGONVRHMD_API UEnum* Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRSdkServiceEventType();
	SNAPDRAGONVRHMD_API UClass* Z_Construct_UClass_USnapdragonVRHMDEventManager_NoRegister();
	SNAPDRAGONVRHMD_API UClass* Z_Construct_UClass_USnapdragonVRHMDEventManager();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
// End Cross Module References
	UFunction* Z_Construct_UDelegateFunction_SnapdragonVRHMD_SnapdragonVRSensorDelegate__DelegateSignature()
	{
		struct _Script_SnapdragonVRHMD_eventSnapdragonVRSensorDelegate_Parms
		{
			ESnapdragonVRSensorEventType Type;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FEnumPropertyParams NewProp_Type = { UE4CodeGen_Private::EPropertyClass::Enum, "Type", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(_Script_SnapdragonVRHMD_eventSnapdragonVRSensorDelegate_Parms, Type), Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRSensorEventType, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FBytePropertyParams NewProp_Type_Underlying = { UE4CodeGen_Private::EPropertyClass::Byte, "UnderlyingType", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000000000, 1, nullptr, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Type,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Type_Underlying,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "ModuleRelativePath", "Classes/SnapdragonVRHMDEventManager.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_SnapdragonVRHMD, "SnapdragonVRSensorDelegate__DelegateSignature", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x00130000, sizeof(_Script_SnapdragonVRHMD_eventSnapdragonVRSensorDelegate_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UDelegateFunction_SnapdragonVRHMD_SnapdragonVRModeDelegate__DelegateSignature()
	{
		struct _Script_SnapdragonVRHMD_eventSnapdragonVRModeDelegate_Parms
		{
			ESnapdragonVRModeEventType Type;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FEnumPropertyParams NewProp_Type = { UE4CodeGen_Private::EPropertyClass::Enum, "Type", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(_Script_SnapdragonVRHMD_eventSnapdragonVRModeDelegate_Parms, Type), Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRModeEventType, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FBytePropertyParams NewProp_Type_Underlying = { UE4CodeGen_Private::EPropertyClass::Byte, "UnderlyingType", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000000000, 1, nullptr, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Type,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Type_Underlying,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "ModuleRelativePath", "Classes/SnapdragonVRHMDEventManager.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_SnapdragonVRHMD, "SnapdragonVRModeDelegate__DelegateSignature", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x00130000, sizeof(_Script_SnapdragonVRHMD_eventSnapdragonVRModeDelegate_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UDelegateFunction_SnapdragonVRHMD_SnapdragonVRThermalDelegate__DelegateSignature()
	{
		struct _Script_SnapdragonVRHMD_eventSnapdragonVRThermalDelegate_Parms
		{
			ESnapdragonVRThermalZone Zone;
			ESnapdragonVRThermalLevel Level;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FEnumPropertyParams NewProp_Level = { UE4CodeGen_Private::EPropertyClass::Enum, "Level", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(_Script_SnapdragonVRHMD_eventSnapdragonVRThermalDelegate_Parms, Level), Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRThermalLevel, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FBytePropertyParams NewProp_Level_Underlying = { UE4CodeGen_Private::EPropertyClass::Byte, "UnderlyingType", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000000000, 1, nullptr, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FEnumPropertyParams NewProp_Zone = { UE4CodeGen_Private::EPropertyClass::Enum, "Zone", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(_Script_SnapdragonVRHMD_eventSnapdragonVRThermalDelegate_Parms, Zone), Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRThermalZone, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FBytePropertyParams NewProp_Zone_Underlying = { UE4CodeGen_Private::EPropertyClass::Byte, "UnderlyingType", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000000000, 1, nullptr, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Level,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Level_Underlying,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Zone,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Zone_Underlying,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "ModuleRelativePath", "Classes/SnapdragonVRHMDEventManager.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_SnapdragonVRHMD, "SnapdragonVRThermalDelegate__DelegateSignature", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x00130000, sizeof(_Script_SnapdragonVRHMD_eventSnapdragonVRThermalDelegate_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UDelegateFunction_SnapdragonVRHMD_SnapdragonVRSdkServiceDelegate__DelegateSignature()
	{
		struct _Script_SnapdragonVRHMD_eventSnapdragonVRSdkServiceDelegate_Parms
		{
			ESnapdragonVRSdkServiceEventType Type;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FEnumPropertyParams NewProp_Type = { UE4CodeGen_Private::EPropertyClass::Enum, "Type", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(_Script_SnapdragonVRHMD_eventSnapdragonVRSdkServiceDelegate_Parms, Type), Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRSdkServiceEventType, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FBytePropertyParams NewProp_Type_Underlying = { UE4CodeGen_Private::EPropertyClass::Byte, "UnderlyingType", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000000000, 1, nullptr, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Type,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Type_Underlying,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "ModuleRelativePath", "Classes/SnapdragonVRHMDEventManager.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_SnapdragonVRHMD, "SnapdragonVRSdkServiceDelegate__DelegateSignature", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x00130000, sizeof(_Script_SnapdragonVRHMD_eventSnapdragonVRSdkServiceDelegate_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	static UEnum* ESnapdragonVRThermalZone_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRThermalZone, Z_Construct_UPackage__Script_SnapdragonVRHMD(), TEXT("ESnapdragonVRThermalZone"));
		}
		return Singleton;
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ESnapdragonVRThermalZone(ESnapdragonVRThermalZone_StaticEnum, TEXT("/Script/SnapdragonVRHMD"), TEXT("ESnapdragonVRThermalZone"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRThermalZone_CRC() { return 4187763074U; }
	UEnum* Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRThermalZone()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_SnapdragonVRHMD();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ESnapdragonVRThermalZone"), 0, Get_Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRThermalZone_CRC(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "ESnapdragonVRThermalZone::Cpu", (int64)ESnapdragonVRThermalZone::Cpu },
				{ "ESnapdragonVRThermalZone::Gpu", (int64)ESnapdragonVRThermalZone::Gpu },
				{ "ESnapdragonVRThermalZone::Skin", (int64)ESnapdragonVRThermalZone::Skin },
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "ModuleRelativePath", "Classes/SnapdragonVRHMDEventManager.h" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_SnapdragonVRHMD,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				"ESnapdragonVRThermalZone",
				RF_Public|RF_Transient|RF_MarkAsNative,
				nullptr,
				(uint8)UEnum::ECppForm::EnumClass,
				"ESnapdragonVRThermalZone",
				Enumerators,
				ARRAY_COUNT(Enumerators),
				METADATA_PARAMS(Enum_MetaDataParams, ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	static UEnum* ESnapdragonVRThermalLevel_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRThermalLevel, Z_Construct_UPackage__Script_SnapdragonVRHMD(), TEXT("ESnapdragonVRThermalLevel"));
		}
		return Singleton;
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ESnapdragonVRThermalLevel(ESnapdragonVRThermalLevel_StaticEnum, TEXT("/Script/SnapdragonVRHMD"), TEXT("ESnapdragonVRThermalLevel"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRThermalLevel_CRC() { return 4078750215U; }
	UEnum* Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRThermalLevel()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_SnapdragonVRHMD();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ESnapdragonVRThermalLevel"), 0, Get_Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRThermalLevel_CRC(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "ESnapdragonVRThermalLevel::Safe", (int64)ESnapdragonVRThermalLevel::Safe },
				{ "ESnapdragonVRThermalLevel::Level1", (int64)ESnapdragonVRThermalLevel::Level1 },
				{ "ESnapdragonVRThermalLevel::Level2", (int64)ESnapdragonVRThermalLevel::Level2 },
				{ "ESnapdragonVRThermalLevel::Level3", (int64)ESnapdragonVRThermalLevel::Level3 },
				{ "ESnapdragonVRThermalLevel::Critical", (int64)ESnapdragonVRThermalLevel::Critical },
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "ModuleRelativePath", "Classes/SnapdragonVRHMDEventManager.h" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_SnapdragonVRHMD,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				"ESnapdragonVRThermalLevel",
				RF_Public|RF_Transient|RF_MarkAsNative,
				nullptr,
				(uint8)UEnum::ECppForm::EnumClass,
				"ESnapdragonVRThermalLevel",
				Enumerators,
				ARRAY_COUNT(Enumerators),
				METADATA_PARAMS(Enum_MetaDataParams, ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	static UEnum* ESnapdragonVRSensorEventType_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRSensorEventType, Z_Construct_UPackage__Script_SnapdragonVRHMD(), TEXT("ESnapdragonVRSensorEventType"));
		}
		return Singleton;
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ESnapdragonVRSensorEventType(ESnapdragonVRSensorEventType_StaticEnum, TEXT("/Script/SnapdragonVRHMD"), TEXT("ESnapdragonVRSensorEventType"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRSensorEventType_CRC() { return 1746552705U; }
	UEnum* Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRSensorEventType()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_SnapdragonVRHMD();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ESnapdragonVRSensorEventType"), 0, Get_Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRSensorEventType_CRC(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "ESnapdragonVRSensorEventType::EventSensorError", (int64)ESnapdragonVRSensorEventType::EventSensorError },
				{ "ESnapdragonVRSensorEventType::EventMagnometerUncalibrated", (int64)ESnapdragonVRSensorEventType::EventMagnometerUncalibrated },
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "ModuleRelativePath", "Classes/SnapdragonVRHMDEventManager.h" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_SnapdragonVRHMD,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				"ESnapdragonVRSensorEventType",
				RF_Public|RF_Transient|RF_MarkAsNative,
				nullptr,
				(uint8)UEnum::ECppForm::EnumClass,
				"ESnapdragonVRSensorEventType",
				Enumerators,
				ARRAY_COUNT(Enumerators),
				METADATA_PARAMS(Enum_MetaDataParams, ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	static UEnum* ESnapdragonVRModeEventType_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRModeEventType, Z_Construct_UPackage__Script_SnapdragonVRHMD(), TEXT("ESnapdragonVRModeEventType"));
		}
		return Singleton;
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ESnapdragonVRModeEventType(ESnapdragonVRModeEventType_StaticEnum, TEXT("/Script/SnapdragonVRHMD"), TEXT("ESnapdragonVRModeEventType"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRModeEventType_CRC() { return 3667510304U; }
	UEnum* Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRModeEventType()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_SnapdragonVRHMD();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ESnapdragonVRModeEventType"), 0, Get_Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRModeEventType_CRC(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "ESnapdragonVRModeEventType::EventVrModeStarted", (int64)ESnapdragonVRModeEventType::EventVrModeStarted },
				{ "ESnapdragonVRModeEventType::EventVrModeStopping", (int64)ESnapdragonVRModeEventType::EventVrModeStopping },
				{ "ESnapdragonVRModeEventType::EventVrModeStopped", (int64)ESnapdragonVRModeEventType::EventVrModeStopped },
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "ModuleRelativePath", "Classes/SnapdragonVRHMDEventManager.h" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_SnapdragonVRHMD,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				"ESnapdragonVRModeEventType",
				RF_Public|RF_Transient|RF_MarkAsNative,
				nullptr,
				(uint8)UEnum::ECppForm::EnumClass,
				"ESnapdragonVRModeEventType",
				Enumerators,
				ARRAY_COUNT(Enumerators),
				METADATA_PARAMS(Enum_MetaDataParams, ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	static UEnum* ESnapdragonVRSdkServiceEventType_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRSdkServiceEventType, Z_Construct_UPackage__Script_SnapdragonVRHMD(), TEXT("ESnapdragonVRSdkServiceEventType"));
		}
		return Singleton;
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ESnapdragonVRSdkServiceEventType(ESnapdragonVRSdkServiceEventType_StaticEnum, TEXT("/Script/SnapdragonVRHMD"), TEXT("ESnapdragonVRSdkServiceEventType"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRSdkServiceEventType_CRC() { return 167830808U; }
	UEnum* Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRSdkServiceEventType()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_SnapdragonVRHMD();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ESnapdragonVRSdkServiceEventType"), 0, Get_Z_Construct_UEnum_SnapdragonVRHMD_ESnapdragonVRSdkServiceEventType_CRC(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "ESnapdragonVRSdkServiceEventType::EventSdkServiceStarting", (int64)ESnapdragonVRSdkServiceEventType::EventSdkServiceStarting },
				{ "ESnapdragonVRSdkServiceEventType::EventSdkServiceStarted", (int64)ESnapdragonVRSdkServiceEventType::EventSdkServiceStarted },
				{ "ESnapdragonVRSdkServiceEventType::EventSdkServiceStopped", (int64)ESnapdragonVRSdkServiceEventType::EventSdkServiceStopped },
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "ModuleRelativePath", "Classes/SnapdragonVRHMDEventManager.h" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_SnapdragonVRHMD,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				"ESnapdragonVRSdkServiceEventType",
				RF_Public|RF_Transient|RF_MarkAsNative,
				nullptr,
				(uint8)UEnum::ECppForm::EnumClass,
				"ESnapdragonVRSdkServiceEventType",
				Enumerators,
				ARRAY_COUNT(Enumerators),
				METADATA_PARAMS(Enum_MetaDataParams, ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	void USnapdragonVRHMDEventManager::StaticRegisterNativesUSnapdragonVRHMDEventManager()
	{
	}
	UClass* Z_Construct_UClass_USnapdragonVRHMDEventManager_NoRegister()
	{
		return USnapdragonVRHMDEventManager::StaticClass();
	}
	UClass* Z_Construct_UClass_USnapdragonVRHMDEventManager()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_UObject,
				(UObject* (*)())Z_Construct_UPackage__Script_SnapdragonVRHMD,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "IncludePath", "SnapdragonVRHMDEventManager.h" },
				{ "ModuleRelativePath", "Classes/SnapdragonVRHMDEventManager.h" },
				{ "ToolTip", "SnapdragonVRHMD Extensions Function Library" },
			};
#endif
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnSnapdragonVRSensorDelegate_MetaData[] = {
				{ "ModuleRelativePath", "Classes/SnapdragonVRHMDEventManager.h" },
			};
#endif
			static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnSnapdragonVRSensorDelegate = { UE4CodeGen_Private::EPropertyClass::MulticastDelegate, "OnSnapdragonVRSensorDelegate", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000010080000, 1, nullptr, STRUCT_OFFSET(USnapdragonVRHMDEventManager, OnSnapdragonVRSensorDelegate), Z_Construct_UDelegateFunction_SnapdragonVRHMD_SnapdragonVRSensorDelegate__DelegateSignature, METADATA_PARAMS(NewProp_OnSnapdragonVRSensorDelegate_MetaData, ARRAY_COUNT(NewProp_OnSnapdragonVRSensorDelegate_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnSnapdragonVRModeDelegate_MetaData[] = {
				{ "ModuleRelativePath", "Classes/SnapdragonVRHMDEventManager.h" },
			};
#endif
			static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnSnapdragonVRModeDelegate = { UE4CodeGen_Private::EPropertyClass::MulticastDelegate, "OnSnapdragonVRModeDelegate", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000010080000, 1, nullptr, STRUCT_OFFSET(USnapdragonVRHMDEventManager, OnSnapdragonVRModeDelegate), Z_Construct_UDelegateFunction_SnapdragonVRHMD_SnapdragonVRModeDelegate__DelegateSignature, METADATA_PARAMS(NewProp_OnSnapdragonVRModeDelegate_MetaData, ARRAY_COUNT(NewProp_OnSnapdragonVRModeDelegate_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnSnapdragonVRThermalDelegate_MetaData[] = {
				{ "ModuleRelativePath", "Classes/SnapdragonVRHMDEventManager.h" },
			};
#endif
			static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnSnapdragonVRThermalDelegate = { UE4CodeGen_Private::EPropertyClass::MulticastDelegate, "OnSnapdragonVRThermalDelegate", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000010080000, 1, nullptr, STRUCT_OFFSET(USnapdragonVRHMDEventManager, OnSnapdragonVRThermalDelegate), Z_Construct_UDelegateFunction_SnapdragonVRHMD_SnapdragonVRThermalDelegate__DelegateSignature, METADATA_PARAMS(NewProp_OnSnapdragonVRThermalDelegate_MetaData, ARRAY_COUNT(NewProp_OnSnapdragonVRThermalDelegate_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnSnapdragonVRSdkServiceDelegate_MetaData[] = {
				{ "ModuleRelativePath", "Classes/SnapdragonVRHMDEventManager.h" },
			};
#endif
			static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnSnapdragonVRSdkServiceDelegate = { UE4CodeGen_Private::EPropertyClass::MulticastDelegate, "OnSnapdragonVRSdkServiceDelegate", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000010080000, 1, nullptr, STRUCT_OFFSET(USnapdragonVRHMDEventManager, OnSnapdragonVRSdkServiceDelegate), Z_Construct_UDelegateFunction_SnapdragonVRHMD_SnapdragonVRSdkServiceDelegate__DelegateSignature, METADATA_PARAMS(NewProp_OnSnapdragonVRSdkServiceDelegate_MetaData, ARRAY_COUNT(NewProp_OnSnapdragonVRSdkServiceDelegate_MetaData)) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_OnSnapdragonVRSensorDelegate,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_OnSnapdragonVRModeDelegate,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_OnSnapdragonVRThermalDelegate,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_OnSnapdragonVRSdkServiceDelegate,
			};
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<USnapdragonVRHMDEventManager>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&USnapdragonVRHMDEventManager::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x00800080u,
				nullptr, 0,
				PropPointers, ARRAY_COUNT(PropPointers),
				nullptr,
				&StaticCppClassTypeInfo,
				nullptr, 0,
				METADATA_PARAMS(Class_MetaDataParams, ARRAY_COUNT(Class_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUClass(OuterClass, ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(USnapdragonVRHMDEventManager, 1312418364);
	static FCompiledInDefer Z_CompiledInDefer_UClass_USnapdragonVRHMDEventManager(Z_Construct_UClass_USnapdragonVRHMDEventManager, &USnapdragonVRHMDEventManager::StaticClass, TEXT("/Script/SnapdragonVRHMD"), TEXT("USnapdragonVRHMDEventManager"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USnapdragonVRHMDEventManager);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
