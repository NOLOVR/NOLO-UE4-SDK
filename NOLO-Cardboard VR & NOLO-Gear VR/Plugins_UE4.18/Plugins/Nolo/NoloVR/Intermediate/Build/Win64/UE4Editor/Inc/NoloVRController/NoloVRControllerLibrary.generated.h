// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectMacros.h"
#include "ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class ENoloVRTouchDPadMapping : uint8;
#ifdef NOLOVRCONTROLLER_NoloVRControllerLibrary_generated_h
#error "NoloVRControllerLibrary.generated.h already included, missing '#pragma once' in NoloVRControllerLibrary.h"
#endif
#define NOLOVRCONTROLLER_NoloVRControllerLibrary_generated_h

#define NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVRController_Private_NoloVRControllerLibrary_h_26_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execSetTouchDPadMapping) \
	{ \
		P_GET_ENUM(ENoloVRTouchDPadMapping,Z_Param_NewMapping); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UNoloVRControllerLibrary::SetTouchDPadMapping(ENoloVRTouchDPadMapping(Z_Param_NewMapping)); \
		P_NATIVE_END; \
	}


#define NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVRController_Private_NoloVRControllerLibrary_h_26_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execSetTouchDPadMapping) \
	{ \
		P_GET_ENUM(ENoloVRTouchDPadMapping,Z_Param_NewMapping); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UNoloVRControllerLibrary::SetTouchDPadMapping(ENoloVRTouchDPadMapping(Z_Param_NewMapping)); \
		P_NATIVE_END; \
	}


#define NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVRController_Private_NoloVRControllerLibrary_h_26_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUNoloVRControllerLibrary(); \
	friend NOLOVRCONTROLLER_API class UClass* Z_Construct_UClass_UNoloVRControllerLibrary(); \
public: \
	DECLARE_CLASS(UNoloVRControllerLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/NoloVRController"), NO_API) \
	DECLARE_SERIALIZER(UNoloVRControllerLibrary) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVRController_Private_NoloVRControllerLibrary_h_26_INCLASS \
private: \
	static void StaticRegisterNativesUNoloVRControllerLibrary(); \
	friend NOLOVRCONTROLLER_API class UClass* Z_Construct_UClass_UNoloVRControllerLibrary(); \
public: \
	DECLARE_CLASS(UNoloVRControllerLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/NoloVRController"), NO_API) \
	DECLARE_SERIALIZER(UNoloVRControllerLibrary) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVRController_Private_NoloVRControllerLibrary_h_26_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNoloVRControllerLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNoloVRControllerLibrary) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNoloVRControllerLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNoloVRControllerLibrary); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNoloVRControllerLibrary(UNoloVRControllerLibrary&&); \
	NO_API UNoloVRControllerLibrary(const UNoloVRControllerLibrary&); \
public:


#define NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVRController_Private_NoloVRControllerLibrary_h_26_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNoloVRControllerLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNoloVRControllerLibrary(UNoloVRControllerLibrary&&); \
	NO_API UNoloVRControllerLibrary(const UNoloVRControllerLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNoloVRControllerLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNoloVRControllerLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNoloVRControllerLibrary)


#define NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVRController_Private_NoloVRControllerLibrary_h_26_PRIVATE_PROPERTY_OFFSET
#define NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVRController_Private_NoloVRControllerLibrary_h_23_PROLOG
#define NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVRController_Private_NoloVRControllerLibrary_h_26_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVRController_Private_NoloVRControllerLibrary_h_26_PRIVATE_PROPERTY_OFFSET \
	NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVRController_Private_NoloVRControllerLibrary_h_26_RPC_WRAPPERS \
	NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVRController_Private_NoloVRControllerLibrary_h_26_INCLASS \
	NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVRController_Private_NoloVRControllerLibrary_h_26_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVRController_Private_NoloVRControllerLibrary_h_26_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVRController_Private_NoloVRControllerLibrary_h_26_PRIVATE_PROPERTY_OFFSET \
	NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVRController_Private_NoloVRControllerLibrary_h_26_RPC_WRAPPERS_NO_PURE_DECLS \
	NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVRController_Private_NoloVRControllerLibrary_h_26_INCLASS_NO_PURE_DECLS \
	NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVRController_Private_NoloVRControllerLibrary_h_26_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID NVR_Demo_Plugins_Nolo_NoloVR_Source_NoloVRController_Private_NoloVRControllerLibrary_h


#define FOREACH_ENUM_ENOLOVRTOUCHDPADMAPPING(op) \
	op(ENoloVRTouchDPadMapping::FaceButtons) \
	op(ENoloVRTouchDPadMapping::ThumbstickDirections) \
	op(ENoloVRTouchDPadMapping::Disabled) 
PRAGMA_ENABLE_DEPRECATION_WARNINGS
