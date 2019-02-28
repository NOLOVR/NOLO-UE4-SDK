// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectMacros.h"
#include "ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class USnapdragonVRHMDEventManager;
#ifdef SNAPDRAGONVRHMD_SnapdragonVRHMDFunctionLibrary_generated_h
#error "SnapdragonVRHMDFunctionLibrary.generated.h already included, missing '#pragma once' in SnapdragonVRHMDFunctionLibrary.h"
#endif
#define SNAPDRAGONVRHMD_SnapdragonVRHMDFunctionLibrary_generated_h

#define TEST419_Plugins_SnapdragonVR_SnapdragonVRHMD_Source_SnapdragonVRHMD_Public_SnapdragonVRHMDFunctionLibrary_h_10_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetSnapdragonVRHMDEventManager) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(USnapdragonVRHMDEventManager**)Z_Param__Result=USnapdragonVRHMDFunctionLibrary::GetSnapdragonVRHMDEventManager(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execSetCpuAndGpuLevelsSVR) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_CpuLevel); \
		P_GET_PROPERTY(UIntProperty,Z_Param_GpuLevel); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		USnapdragonVRHMDFunctionLibrary::SetCpuAndGpuLevelsSVR(Z_Param_CpuLevel,Z_Param_GpuLevel); \
		P_NATIVE_END; \
	}


#define TEST419_Plugins_SnapdragonVR_SnapdragonVRHMD_Source_SnapdragonVRHMD_Public_SnapdragonVRHMDFunctionLibrary_h_10_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetSnapdragonVRHMDEventManager) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(USnapdragonVRHMDEventManager**)Z_Param__Result=USnapdragonVRHMDFunctionLibrary::GetSnapdragonVRHMDEventManager(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execSetCpuAndGpuLevelsSVR) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_CpuLevel); \
		P_GET_PROPERTY(UIntProperty,Z_Param_GpuLevel); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		USnapdragonVRHMDFunctionLibrary::SetCpuAndGpuLevelsSVR(Z_Param_CpuLevel,Z_Param_GpuLevel); \
		P_NATIVE_END; \
	}


#define TEST419_Plugins_SnapdragonVR_SnapdragonVRHMD_Source_SnapdragonVRHMD_Public_SnapdragonVRHMDFunctionLibrary_h_10_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUSnapdragonVRHMDFunctionLibrary(); \
	friend SNAPDRAGONVRHMD_API class UClass* Z_Construct_UClass_USnapdragonVRHMDFunctionLibrary(); \
public: \
	DECLARE_CLASS(USnapdragonVRHMDFunctionLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/SnapdragonVRHMD"), NO_API) \
	DECLARE_SERIALIZER(USnapdragonVRHMDFunctionLibrary) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define TEST419_Plugins_SnapdragonVR_SnapdragonVRHMD_Source_SnapdragonVRHMD_Public_SnapdragonVRHMDFunctionLibrary_h_10_INCLASS \
private: \
	static void StaticRegisterNativesUSnapdragonVRHMDFunctionLibrary(); \
	friend SNAPDRAGONVRHMD_API class UClass* Z_Construct_UClass_USnapdragonVRHMDFunctionLibrary(); \
public: \
	DECLARE_CLASS(USnapdragonVRHMDFunctionLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/SnapdragonVRHMD"), NO_API) \
	DECLARE_SERIALIZER(USnapdragonVRHMDFunctionLibrary) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define TEST419_Plugins_SnapdragonVR_SnapdragonVRHMD_Source_SnapdragonVRHMD_Public_SnapdragonVRHMDFunctionLibrary_h_10_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API USnapdragonVRHMDFunctionLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USnapdragonVRHMDFunctionLibrary) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USnapdragonVRHMDFunctionLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USnapdragonVRHMDFunctionLibrary); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USnapdragonVRHMDFunctionLibrary(USnapdragonVRHMDFunctionLibrary&&); \
	NO_API USnapdragonVRHMDFunctionLibrary(const USnapdragonVRHMDFunctionLibrary&); \
public:


#define TEST419_Plugins_SnapdragonVR_SnapdragonVRHMD_Source_SnapdragonVRHMD_Public_SnapdragonVRHMDFunctionLibrary_h_10_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API USnapdragonVRHMDFunctionLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USnapdragonVRHMDFunctionLibrary(USnapdragonVRHMDFunctionLibrary&&); \
	NO_API USnapdragonVRHMDFunctionLibrary(const USnapdragonVRHMDFunctionLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USnapdragonVRHMDFunctionLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USnapdragonVRHMDFunctionLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USnapdragonVRHMDFunctionLibrary)


#define TEST419_Plugins_SnapdragonVR_SnapdragonVRHMD_Source_SnapdragonVRHMD_Public_SnapdragonVRHMDFunctionLibrary_h_10_PRIVATE_PROPERTY_OFFSET
#define TEST419_Plugins_SnapdragonVR_SnapdragonVRHMD_Source_SnapdragonVRHMD_Public_SnapdragonVRHMDFunctionLibrary_h_7_PROLOG
#define TEST419_Plugins_SnapdragonVR_SnapdragonVRHMD_Source_SnapdragonVRHMD_Public_SnapdragonVRHMDFunctionLibrary_h_10_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TEST419_Plugins_SnapdragonVR_SnapdragonVRHMD_Source_SnapdragonVRHMD_Public_SnapdragonVRHMDFunctionLibrary_h_10_PRIVATE_PROPERTY_OFFSET \
	TEST419_Plugins_SnapdragonVR_SnapdragonVRHMD_Source_SnapdragonVRHMD_Public_SnapdragonVRHMDFunctionLibrary_h_10_RPC_WRAPPERS \
	TEST419_Plugins_SnapdragonVR_SnapdragonVRHMD_Source_SnapdragonVRHMD_Public_SnapdragonVRHMDFunctionLibrary_h_10_INCLASS \
	TEST419_Plugins_SnapdragonVR_SnapdragonVRHMD_Source_SnapdragonVRHMD_Public_SnapdragonVRHMDFunctionLibrary_h_10_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define TEST419_Plugins_SnapdragonVR_SnapdragonVRHMD_Source_SnapdragonVRHMD_Public_SnapdragonVRHMDFunctionLibrary_h_10_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TEST419_Plugins_SnapdragonVR_SnapdragonVRHMD_Source_SnapdragonVRHMD_Public_SnapdragonVRHMDFunctionLibrary_h_10_PRIVATE_PROPERTY_OFFSET \
	TEST419_Plugins_SnapdragonVR_SnapdragonVRHMD_Source_SnapdragonVRHMD_Public_SnapdragonVRHMDFunctionLibrary_h_10_RPC_WRAPPERS_NO_PURE_DECLS \
	TEST419_Plugins_SnapdragonVR_SnapdragonVRHMD_Source_SnapdragonVRHMD_Public_SnapdragonVRHMDFunctionLibrary_h_10_INCLASS_NO_PURE_DECLS \
	TEST419_Plugins_SnapdragonVR_SnapdragonVRHMD_Source_SnapdragonVRHMD_Public_SnapdragonVRHMDFunctionLibrary_h_10_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class SnapdragonVRHMDFunctionLibrary."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID TEST419_Plugins_SnapdragonVR_SnapdragonVRHMD_Source_SnapdragonVRHMD_Public_SnapdragonVRHMDFunctionLibrary_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
