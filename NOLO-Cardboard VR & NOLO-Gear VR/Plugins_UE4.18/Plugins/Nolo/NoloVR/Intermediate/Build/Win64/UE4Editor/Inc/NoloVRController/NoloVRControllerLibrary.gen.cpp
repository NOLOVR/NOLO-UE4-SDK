// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "Private/NoloVRControllerLibrary.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNoloVRControllerLibrary() {}
// Cross Module References
	NOLOVRCONTROLLER_API UEnum* Z_Construct_UEnum_NoloVRController_ENoloVRTouchDPadMapping();
	UPackage* Z_Construct_UPackage__Script_NoloVRController();
	NOLOVRCONTROLLER_API UClass* Z_Construct_UClass_UNoloVRControllerLibrary_NoRegister();
	NOLOVRCONTROLLER_API UClass* Z_Construct_UClass_UNoloVRControllerLibrary();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	NOLOVRCONTROLLER_API UFunction* Z_Construct_UFunction_UNoloVRControllerLibrary_SetTouchDPadMapping();
// End Cross Module References
	static UEnum* ENoloVRTouchDPadMapping_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_NoloVRController_ENoloVRTouchDPadMapping, Z_Construct_UPackage__Script_NoloVRController(), TEXT("ENoloVRTouchDPadMapping"));
		}
		return Singleton;
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ENoloVRTouchDPadMapping(ENoloVRTouchDPadMapping_StaticEnum, TEXT("/Script/NoloVRController"), TEXT("ENoloVRTouchDPadMapping"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_NoloVRController_ENoloVRTouchDPadMapping_CRC() { return 2842296714U; }
	UEnum* Z_Construct_UEnum_NoloVRController_ENoloVRTouchDPadMapping()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_NoloVRController();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ENoloVRTouchDPadMapping"), 0, Get_Z_Construct_UEnum_NoloVRController_ENoloVRTouchDPadMapping_CRC(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "ENoloVRTouchDPadMapping::FaceButtons", (int64)ENoloVRTouchDPadMapping::FaceButtons },
				{ "ENoloVRTouchDPadMapping::ThumbstickDirections", (int64)ENoloVRTouchDPadMapping::ThumbstickDirections },
				{ "ENoloVRTouchDPadMapping::Disabled", (int64)ENoloVRTouchDPadMapping::Disabled },
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "Disabled.ToolTip", "Unmaps all directional touchpad input so that the d-pad buttons won't trigger their own input events" },
				{ "FaceButtons.ToolTip", "Maps each controller's four touchpad buttons to the respective FaceButton1/2/3/4 events" },
				{ "ModuleRelativePath", "Private/NoloVRControllerLibrary.h" },
				{ "ThumbstickDirections.ToolTip", "Maps each controller's four touchpad buttons to the respective Up/Down/Left/Right events" },
				{ "ToolTip", "Defines the set of input events you want associated with your NoloVR d-pad buttons" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_NoloVRController,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				"ENoloVRTouchDPadMapping",
				RF_Public|RF_Transient|RF_MarkAsNative,
				nullptr,
				(uint8)UEnum::ECppForm::EnumClass,
				"ENoloVRTouchDPadMapping",
				Enumerators,
				ARRAY_COUNT(Enumerators),
				METADATA_PARAMS(Enum_MetaDataParams, ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	void UNoloVRControllerLibrary::StaticRegisterNativesUNoloVRControllerLibrary()
	{
		UClass* Class = UNoloVRControllerLibrary::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "SetTouchDPadMapping", &UNoloVRControllerLibrary::execSetTouchDPadMapping },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, ARRAY_COUNT(Funcs));
	}
	UFunction* Z_Construct_UFunction_UNoloVRControllerLibrary_SetTouchDPadMapping()
	{
		struct NoloVRControllerLibrary_eventSetTouchDPadMapping_Parms
		{
			ENoloVRTouchDPadMapping NewMapping;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FEnumPropertyParams NewProp_NewMapping = { UE4CodeGen_Private::EPropertyClass::Enum, "NewMapping", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(NoloVRControllerLibrary_eventSetTouchDPadMapping_Parms, NewMapping), Z_Construct_UEnum_NoloVRController_ENoloVRTouchDPadMapping, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FBytePropertyParams NewProp_NewMapping_Underlying = { UE4CodeGen_Private::EPropertyClass::Byte, "UnderlyingType", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000000000, 1, nullptr, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_NewMapping,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_NewMapping_Underlying,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "NoloVR" },
				{ "CPP_Default_NewMapping", "FaceButtons" },
				{ "ModuleRelativePath", "Private/NoloVRControllerLibrary.h" },
				{ "ToolTip", "Sets which input events you want associated with the NoloVR controller's\ndirectional touchpad buttons - does so for both left and right controllers.\n\n@param  NewMapping   Defines the set of input events you want associated with the four directional touchpad buttons." },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_UNoloVRControllerLibrary, "SetTouchDPadMapping", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04022401, sizeof(NoloVRControllerLibrary_eventSetTouchDPadMapping_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UNoloVRControllerLibrary_NoRegister()
	{
		return UNoloVRControllerLibrary::StaticClass();
	}
	UClass* Z_Construct_UClass_UNoloVRControllerLibrary()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
				(UObject* (*)())Z_Construct_UPackage__Script_NoloVRController,
			};
			static const FClassFunctionLinkInfo FuncInfo[] = {
				{ &Z_Construct_UFunction_UNoloVRControllerLibrary_SetTouchDPadMapping, "SetTouchDPadMapping" }, // 2619277992
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "IncludePath", "NoloVRControllerLibrary.h" },
				{ "ModuleRelativePath", "Private/NoloVRControllerLibrary.h" },
			};
#endif
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<UNoloVRControllerLibrary>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&UNoloVRControllerLibrary::StaticClass,
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
	IMPLEMENT_CLASS(UNoloVRControllerLibrary, 4191223066);
	static FCompiledInDefer Z_CompiledInDefer_UClass_UNoloVRControllerLibrary(Z_Construct_UClass_UNoloVRControllerLibrary, &UNoloVRControllerLibrary::StaticClass, TEXT("/Script/NoloVRController"), TEXT("UNoloVRControllerLibrary"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UNoloVRControllerLibrary);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
