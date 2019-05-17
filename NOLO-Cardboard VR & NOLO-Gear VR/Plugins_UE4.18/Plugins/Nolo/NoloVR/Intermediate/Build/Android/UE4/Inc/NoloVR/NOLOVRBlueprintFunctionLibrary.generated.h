// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectMacros.h"
#include "ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class ENoloDeviceType : uint8;
enum class EControllerHand : uint8;
struct FVector;
struct FRotator;
enum class EMobileVR_HMDDeviceType : uint8;
#ifdef NOLOVR_NOLOVRBlueprintFunctionLibrary_generated_h
#error "NOLOVRBlueprintFunctionLibrary.generated.h already included, missing '#pragma once' in NOLOVRBlueprintFunctionLibrary.h"
#endif
#define NOLOVR_NOLOVRBlueprintFunctionLibrary_generated_h

#define NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVR_Classes_NOLOVRBlueprintFunctionLibrary_h_28_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execIsStartUpNoloHome) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UNOLOVRBlueprintFunctionLibrary::IsStartUpNoloHome(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execIsInstallNoloHome) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UNOLOVRBlueprintFunctionLibrary::IsInstallNoloHome(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execReportError) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_errorMsg); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UNOLOVRBlueprintFunctionLibrary::ReportError(Z_Param_errorMsg); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execSetAppKey) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_appKey); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UNOLOVRBlueprintFunctionLibrary::SetAppKey(Z_Param_appKey); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetElectricityByDeviceType) \
	{ \
		P_GET_ENUM(ENoloDeviceType,Z_Param_DeviceType); \
		P_GET_PROPERTY_REF(UIntProperty,Z_Param_Out_battery); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UNOLOVRBlueprintFunctionLibrary::GetElectricityByDeviceType(ENoloDeviceType(Z_Param_DeviceType),Z_Param_Out_battery); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetTrackingStatusByDeviceType) \
	{ \
		P_GET_ENUM(ENoloDeviceType,Z_Param_DeviceType); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UNOLOVRBlueprintFunctionLibrary::GetTrackingStatusByDeviceType(ENoloDeviceType(Z_Param_DeviceType)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetHandPositionAndOrientation) \
	{ \
		P_GET_ENUM(EControllerHand,Z_Param_Hand); \
		P_GET_STRUCT_REF(FVector,Z_Param_Out_OutPosition); \
		P_GET_STRUCT_REF(FRotator,Z_Param_Out_OutOrientation); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UNOLOVRBlueprintFunctionLibrary::GetHandPositionAndOrientation(EControllerHand(Z_Param_Hand),Z_Param_Out_OutPosition,Z_Param_Out_OutOrientation); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetTrackedDevicePositionAndOrientation) \
	{ \
		P_GET_STRUCT_REF(FVector,Z_Param_Out_OutPosition); \
		P_GET_STRUCT_REF(FRotator,Z_Param_Out_OutOrientation); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UNOLOVRBlueprintFunctionLibrary::GetTrackedDevicePositionAndOrientation(Z_Param_Out_OutPosition,Z_Param_Out_OutOrientation); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execSetHmdDeviceType) \
	{ \
		P_GET_ENUM(EMobileVR_HMDDeviceType,Z_Param_DeviceType); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UNOLOVRBlueprintFunctionLibrary::SetHmdDeviceType(EMobileVR_HMDDeviceType(Z_Param_DeviceType)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetRunningPlatform) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=UNOLOVRBlueprintFunctionLibrary::GetRunningPlatform(); \
		P_NATIVE_END; \
	}


#define NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVR_Classes_NOLOVRBlueprintFunctionLibrary_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execIsStartUpNoloHome) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UNOLOVRBlueprintFunctionLibrary::IsStartUpNoloHome(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execIsInstallNoloHome) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UNOLOVRBlueprintFunctionLibrary::IsInstallNoloHome(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execReportError) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_errorMsg); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UNOLOVRBlueprintFunctionLibrary::ReportError(Z_Param_errorMsg); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execSetAppKey) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_appKey); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UNOLOVRBlueprintFunctionLibrary::SetAppKey(Z_Param_appKey); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetElectricityByDeviceType) \
	{ \
		P_GET_ENUM(ENoloDeviceType,Z_Param_DeviceType); \
		P_GET_PROPERTY_REF(UIntProperty,Z_Param_Out_battery); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UNOLOVRBlueprintFunctionLibrary::GetElectricityByDeviceType(ENoloDeviceType(Z_Param_DeviceType),Z_Param_Out_battery); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetTrackingStatusByDeviceType) \
	{ \
		P_GET_ENUM(ENoloDeviceType,Z_Param_DeviceType); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UNOLOVRBlueprintFunctionLibrary::GetTrackingStatusByDeviceType(ENoloDeviceType(Z_Param_DeviceType)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetHandPositionAndOrientation) \
	{ \
		P_GET_ENUM(EControllerHand,Z_Param_Hand); \
		P_GET_STRUCT_REF(FVector,Z_Param_Out_OutPosition); \
		P_GET_STRUCT_REF(FRotator,Z_Param_Out_OutOrientation); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UNOLOVRBlueprintFunctionLibrary::GetHandPositionAndOrientation(EControllerHand(Z_Param_Hand),Z_Param_Out_OutPosition,Z_Param_Out_OutOrientation); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetTrackedDevicePositionAndOrientation) \
	{ \
		P_GET_STRUCT_REF(FVector,Z_Param_Out_OutPosition); \
		P_GET_STRUCT_REF(FRotator,Z_Param_Out_OutOrientation); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UNOLOVRBlueprintFunctionLibrary::GetTrackedDevicePositionAndOrientation(Z_Param_Out_OutPosition,Z_Param_Out_OutOrientation); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execSetHmdDeviceType) \
	{ \
		P_GET_ENUM(EMobileVR_HMDDeviceType,Z_Param_DeviceType); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UNOLOVRBlueprintFunctionLibrary::SetHmdDeviceType(EMobileVR_HMDDeviceType(Z_Param_DeviceType)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetRunningPlatform) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=UNOLOVRBlueprintFunctionLibrary::GetRunningPlatform(); \
		P_NATIVE_END; \
	}


#define NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVR_Classes_NOLOVRBlueprintFunctionLibrary_h_28_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUNOLOVRBlueprintFunctionLibrary(); \
	friend NOLOVR_API class UClass* Z_Construct_UClass_UNOLOVRBlueprintFunctionLibrary(); \
public: \
	DECLARE_CLASS(UNOLOVRBlueprintFunctionLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/NoloVR"), NO_API) \
	DECLARE_SERIALIZER(UNOLOVRBlueprintFunctionLibrary) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVR_Classes_NOLOVRBlueprintFunctionLibrary_h_28_INCLASS \
private: \
	static void StaticRegisterNativesUNOLOVRBlueprintFunctionLibrary(); \
	friend NOLOVR_API class UClass* Z_Construct_UClass_UNOLOVRBlueprintFunctionLibrary(); \
public: \
	DECLARE_CLASS(UNOLOVRBlueprintFunctionLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/NoloVR"), NO_API) \
	DECLARE_SERIALIZER(UNOLOVRBlueprintFunctionLibrary) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVR_Classes_NOLOVRBlueprintFunctionLibrary_h_28_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNOLOVRBlueprintFunctionLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNOLOVRBlueprintFunctionLibrary) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNOLOVRBlueprintFunctionLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNOLOVRBlueprintFunctionLibrary); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNOLOVRBlueprintFunctionLibrary(UNOLOVRBlueprintFunctionLibrary&&); \
	NO_API UNOLOVRBlueprintFunctionLibrary(const UNOLOVRBlueprintFunctionLibrary&); \
public:


#define NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVR_Classes_NOLOVRBlueprintFunctionLibrary_h_28_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNOLOVRBlueprintFunctionLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNOLOVRBlueprintFunctionLibrary(UNOLOVRBlueprintFunctionLibrary&&); \
	NO_API UNOLOVRBlueprintFunctionLibrary(const UNOLOVRBlueprintFunctionLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNOLOVRBlueprintFunctionLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNOLOVRBlueprintFunctionLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNOLOVRBlueprintFunctionLibrary)


#define NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVR_Classes_NOLOVRBlueprintFunctionLibrary_h_28_PRIVATE_PROPERTY_OFFSET
#define NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVR_Classes_NOLOVRBlueprintFunctionLibrary_h_25_PROLOG
#define NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVR_Classes_NOLOVRBlueprintFunctionLibrary_h_28_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVR_Classes_NOLOVRBlueprintFunctionLibrary_h_28_PRIVATE_PROPERTY_OFFSET \
	NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVR_Classes_NOLOVRBlueprintFunctionLibrary_h_28_RPC_WRAPPERS \
	NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVR_Classes_NOLOVRBlueprintFunctionLibrary_h_28_INCLASS \
	NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVR_Classes_NOLOVRBlueprintFunctionLibrary_h_28_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVR_Classes_NOLOVRBlueprintFunctionLibrary_h_28_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVR_Classes_NOLOVRBlueprintFunctionLibrary_h_28_PRIVATE_PROPERTY_OFFSET \
	NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVR_Classes_NOLOVRBlueprintFunctionLibrary_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
	NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVR_Classes_NOLOVRBlueprintFunctionLibrary_h_28_INCLASS_NO_PURE_DECLS \
	NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVR_Classes_NOLOVRBlueprintFunctionLibrary_h_28_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVR_Classes_NOLOVRBlueprintFunctionLibrary_h


#define FOREACH_ENUM_EMOBILEVR_HMDDEVICETYPE(op) \
	op(EMobileVR_HMDDeviceType::DT_GearVR) \
	op(EMobileVR_HMDDeviceType::DT_GoogleVR_Cardboard) \
	op(EMobileVR_HMDDeviceType::DT_GoogleVR_Daydream) \
	op(EMobileVR_HMDDeviceType::DT_Other) 
#define FOREACH_ENUM_ENOLODEVICETYPE(op) \
	op(ENoloDeviceType::Hmd) \
	op(ENoloDeviceType::Left) \
	op(ENoloDeviceType::Right) \
	op(ENoloDeviceType::Basestation) 
PRAGMA_ENABLE_DEPRECATION_WARNINGS
