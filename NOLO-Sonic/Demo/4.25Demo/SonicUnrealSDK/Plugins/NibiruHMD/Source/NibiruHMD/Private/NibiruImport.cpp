// Fill out your copyright notice in the Description page of Project Settings.


#include "NibiruImport.h"
#if PLATFORM_ANDROID
#include "Android/AndroidWindow.h"
DEFINE_LOG_CATEGORY_STATIC(LogNibiruImport, Log, All);

void* NibiruImport::GSharedLibraryHandle = nullptr;
FString NibiruImport::GPluginDir;

FString NibiruImport::GetPluginDir()
{
	return GPluginDir;
}

API_NibiruInit NibiruImport::pAPI_NibiruInit = nullptr;
API_NibiruGetSensorData NibiruImport::pAPI_NibiruGetSensorData = nullptr;
API_NibiruGetSensorDataWithPosition NibiruImport::pAPI_NibiruGetSensorDataWithPosition = nullptr;
API_NibiruGetNVRConfig NibiruImport::pAPI_NibiruGetNVRConfig = nullptr;
API_NibiruResetHeadPose NibiruImport::pAPI_NibiruResetHeadPose = nullptr;
API_NibiruLockHeadPose NibiruImport::pAPI_NibiruLockHeadPose = nullptr;
API_NibiruUnLockHeadPose NibiruImport::pAPI_NibiruUnLockHeadPose = nullptr;
API_NibiruEnterVRMode NibiruImport::pAPI_NibiruEnterVRMode = nullptr;
API_NibiruLeaveVRMode NibiruImport::pAPI_NibiruLeaveVRMode = nullptr;
API_NibiruDestory NibiruImport::pAPI_NibiruDestory = nullptr;
API_NibiruGetFloatValue NibiruImport::pAPI_NibiruGetFloatValue = nullptr;
API_NibiruSetFloatValue NibiruImport::pAPI_NibiruSetFloatValue = nullptr;
API_NibiruGetIntValue NibiruImport::pAPI_NibiruGetIntValue = nullptr;
API_NibiruSetIntValue NibiruImport::pAPI_NibiruSetIntValue = nullptr;
API_NibiruGetParameter NibiruImport::pAPI_NibiruGetParameter = nullptr;
API_NibiruSetPatameter NibiruImport::pAPI_NibiruSetPatameter = nullptr;
API_NibiruComputeDistortedPoint NibiruImport::pAPI_NibiruComputeDistortedPoint = nullptr;
API_NibiruCreateTextures NibiruImport::pAPI_NibiruCreateTextures = nullptr;
API_NibiruSetTexture NibiruImport::pAPI_NibiruSetTexture = nullptr;

// 手柄接口
API_NibiruController_GetRotPos NibiruImport::pAPI_NibiruController_GetRotPos = nullptr;
API_NibiruController_IsTouchDown NibiruImport::pAPI_NibiruController_IsTouchDown = nullptr;
API_NibiruController_IsTouchUp NibiruImport::pAPI_NibiruController_IsTouchUp = nullptr;
API_NibiruController_IsTouchPressed NibiruImport::pAPI_NibiruController_IsTouchPressed = nullptr;
API_NibiruController_GetTouchPosition NibiruImport::pAPI_NibiruController_GetTouchPosition = nullptr;
API_NibiruController_IsButtonDown NibiruImport::pAPI_NibiruController_IsButtonDown = nullptr;
API_NibiruController_IsButtonUp NibiruImport::pAPI_NibiruController_IsButtonUp = nullptr;
API_NibiruController_IsButtonPressed NibiruImport::pAPI_NibiruController_IsButtonPressed = nullptr;
API_NibiruController_IsConnected NibiruImport::pAPI_NibiruController_IsConnected = nullptr;
API_NibiruController_GetKeyState NibiruImport::pAPI_NibiruController_GetKeyState = nullptr;
API_NibiruController_GetBatteryLevel NibiruImport::pAPI_NibiruController_GetBatteryLevel = nullptr;
API_NibiruController_Recenter NibiruImport::pAPI_NibiruController_Recenter = nullptr;
// 手柄接口

bool NibiruImport::Init()
{
	UE_LOG(LogNibiruImport, Log, TEXT("Init()"));
	GSharedLibraryHandle = dlopen("libnvr_v2.so", 0);
	if (GSharedLibraryHandle != NULL)
	{
 
		pAPI_NibiruInit = (API_NibiruInit) dlsym(GSharedLibraryHandle, "NibiruInit");
		if (!pAPI_NibiruInit) 
			UE_LOG(LogNibiruImport, Warning, TEXT("API NibiruInit not found!"));

		pAPI_NibiruGetSensorData = (API_NibiruGetSensorData)dlsym(GSharedLibraryHandle, "NibiruGetSensorData");
		if (!pAPI_NibiruGetSensorData) 
			UE_LOG(LogNibiruImport, Warning, TEXT("API NibiruGetSensorData not found!"));

		pAPI_NibiruGetSensorDataWithPosition = (API_NibiruGetSensorDataWithPosition)dlsym(GSharedLibraryHandle, "NibiruGetSensorDataWithPosition");
		if (!pAPI_NibiruGetSensorDataWithPosition)
			UE_LOG(LogNibiruImport, Warning, TEXT("API NibiruGetSensorDataWithPosition not found!"));

		pAPI_NibiruGetNVRConfig = (API_NibiruGetNVRConfig)dlsym(GSharedLibraryHandle, "NibiruGetNVRConfig");
		if (!pAPI_NibiruGetNVRConfig) 
			UE_LOG(LogNibiruImport, Warning, TEXT("API NibiruGetNVRConfig not found!"));

		pAPI_NibiruResetHeadPose = (API_NibiruResetHeadPose)dlsym(GSharedLibraryHandle, "NibiruResetHeadPose");
		if (!pAPI_NibiruResetHeadPose) 
			UE_LOG(LogNibiruImport, Warning, TEXT("API NibiruResetHeadPose not found!"));

		pAPI_NibiruLockHeadPose = (API_NibiruLockHeadPose)dlsym(GSharedLibraryHandle, "NibiruLockHeadPose");
		if (!pAPI_NibiruLockHeadPose) 
			UE_LOG(LogNibiruImport, Warning, TEXT("API NibiruLockHeadPose not found!"));

		pAPI_NibiruUnLockHeadPose = (API_NibiruUnLockHeadPose)dlsym(GSharedLibraryHandle, "NibiruUnLockHeadPose");
		if (!pAPI_NibiruUnLockHeadPose) 
			UE_LOG(LogNibiruImport, Warning, TEXT("API NibiruUnLockHeadPose not found!"));

		pAPI_NibiruEnterVRMode = (API_NibiruEnterVRMode)dlsym(GSharedLibraryHandle, "NibiruEnterVRMode");
		if (!pAPI_NibiruEnterVRMode) 
			UE_LOG(LogNibiruImport, Warning, TEXT("API NibiruEnterVRMode not found!"));

		pAPI_NibiruLeaveVRMode = (API_NibiruLeaveVRMode)dlsym(GSharedLibraryHandle, "NibiruLeaveVRMode");
		if (!pAPI_NibiruLeaveVRMode) 
			UE_LOG(LogNibiruImport, Warning, TEXT("API NibiruLeaveVRMode not found!"));

		pAPI_NibiruDestory = (API_NibiruDestory)dlsym(GSharedLibraryHandle, "NibiruDestory");
		if (!pAPI_NibiruDestory) 
			UE_LOG(LogNibiruImport, Warning, TEXT("API NibiruDestory not found!"));

		pAPI_NibiruGetFloatValue = (API_NibiruGetFloatValue)dlsym(GSharedLibraryHandle, "NibiruGetFloatValue");
		if (!pAPI_NibiruGetFloatValue) 
			UE_LOG(LogNibiruImport, Warning, TEXT("API NibiruGetFloatValue not found!"));

		pAPI_NibiruSetFloatValue = (API_NibiruSetFloatValue)dlsym(GSharedLibraryHandle, "NibiruSetFloatValue");
		if (!pAPI_NibiruSetFloatValue) 
			UE_LOG(LogNibiruImport, Warning, TEXT("API NibiruSetFloatValue not found!"));

		pAPI_NibiruGetIntValue = (API_NibiruGetIntValue)dlsym(GSharedLibraryHandle, "NibiruGetIntValue");
		if (!pAPI_NibiruGetIntValue) 
			UE_LOG(LogNibiruImport, Warning, TEXT("API NibiruGetIntValue not found!"));

		pAPI_NibiruSetIntValue = (API_NibiruSetIntValue)dlsym(GSharedLibraryHandle, "NibiruSetIntValue");
		if (!pAPI_NibiruSetIntValue) 
			UE_LOG(LogNibiruImport, Warning, TEXT("API NibiruSetIntValue not found!"));

		pAPI_NibiruGetParameter = (API_NibiruGetParameter)dlsym(GSharedLibraryHandle, "NibiruGetParameter");
		if (!pAPI_NibiruGetParameter) 
			UE_LOG(LogNibiruImport, Warning, TEXT("API NibiruGetParameter not found!"));

		pAPI_NibiruSetPatameter = (API_NibiruSetPatameter)dlsym(GSharedLibraryHandle, "NibiruSetPatameter");
		if (!pAPI_NibiruSetPatameter) 
			UE_LOG(LogNibiruImport, Warning, TEXT("API NibiruSetPatameter not found!"));

		pAPI_NibiruComputeDistortedPoint = (API_NibiruComputeDistortedPoint)dlsym(GSharedLibraryHandle, "NibiruComputeDistortedPoint");
		if (!pAPI_NibiruComputeDistortedPoint) 
			UE_LOG(LogNibiruImport, Warning, TEXT("API NibiruComputeDistortedPoint not found!"));

		pAPI_NibiruCreateTextures = (API_NibiruCreateTextures)dlsym(GSharedLibraryHandle, "NibiruCreateTextures");
		if (!pAPI_NibiruCreateTextures) 
			UE_LOG(LogNibiruImport, Warning, TEXT("API NibiruCreateTextures not found!"));

		pAPI_NibiruSetTexture = (API_NibiruSetTexture)dlsym(GSharedLibraryHandle, "NibiruSetTexture");
		if (!pAPI_NibiruSetTexture) 
			UE_LOG(LogNibiruImport, Warning, TEXT("API NibiruSetTexture not found!"));

		// 手柄接口
		pAPI_NibiruController_GetRotPos = (API_NibiruController_GetRotPos) dlsym(GSharedLibraryHandle, "NibiruGetControllerRotPos");
		pAPI_NibiruController_IsTouchDown = (API_NibiruController_IsTouchDown) dlsym(GSharedLibraryHandle, "NibiruGetControllerTouchDown");
		pAPI_NibiruController_IsTouchUp = (API_NibiruController_IsTouchDown) dlsym(GSharedLibraryHandle, "NibiruGetControllerTouchUp");
		pAPI_NibiruController_IsTouchPressed = (API_NibiruController_IsTouchPressed) dlsym(GSharedLibraryHandle, "NibiruGetControllerTouchPressed");
		pAPI_NibiruController_GetTouchPosition = (API_NibiruController_GetTouchPosition) dlsym(GSharedLibraryHandle, "NibiruGetControllerTouchPosition");
		pAPI_NibiruController_IsButtonDown = (API_NibiruController_IsButtonDown) dlsym(GSharedLibraryHandle, "NibiruGetButtonDown");
		pAPI_NibiruController_IsButtonUp = (API_NibiruController_IsButtonUp) dlsym(GSharedLibraryHandle, "NibiruGetButtonUp");
		pAPI_NibiruController_IsButtonPressed = (API_NibiruController_IsButtonPressed) dlsym(GSharedLibraryHandle, "NibiruGetButtonPressed");
		pAPI_NibiruController_IsConnected = (API_NibiruController_IsConnected) dlsym(GSharedLibraryHandle, "NibiruIsControllerConnected");
		pAPI_NibiruController_GetKeyState = (API_NibiruController_GetKeyState) dlsym(GSharedLibraryHandle, "NibiruGetControllerKeyState");
		pAPI_NibiruController_GetBatteryLevel = (API_NibiruController_GetBatteryLevel) dlsym(GSharedLibraryHandle, "NibiruGetControllerBatteryLevel");
		pAPI_NibiruController_Recenter = (API_NibiruController_Recenter) dlsym(GSharedLibraryHandle, "NibiruResetController");
		// 手柄接口

        UE_LOG(LogNibiruImport, Log, TEXT("Nibiru Import Load V2 Successs."));
		return true;
	} else {
		UE_LOG(LogNibiruImport, Error, TEXT("Nibiru Import Load V2 Failed."));
	}
	return false;
}

void NibiruImport::Uninit()
{
	GPluginDir.Empty();

	FreeDependency(GSharedLibraryHandle);
}

void NibiruImport::FreeDependency(void*& Handle)
{
	if (Handle != nullptr)
	{
		dlclose(Handle);
		Handle = nullptr;
	}
}

bool NibiruImport::LoadDependency(const FString& Dir, const FString& Name, void*& Handle)
{
	return true;
}

	//===================== APIS =====================
nvr_init_info NibiruImport::NibiruInit(int pluginVersion ,long pointer ,const nvrModeParms * parms)
{
	if(NibiruImport::pAPI_NibiruInit) {
		return NibiruImport::pAPI_NibiruInit(pluginVersion, pointer, parms);
	}
	nvr_init_info tmp;
	tmp.sdk_version = 0;
	tmp.init_result = 0;
	return tmp;
}

nvr_mat4f NibiruImport::NibiruGetSensorData(int *viewNumber)
{
	if(NibiruImport::pAPI_NibiruGetSensorData)
	{
		return NibiruImport::pAPI_NibiruGetSensorData(viewNumber);
	}
	nvr_mat4f tmp;
	return tmp;
}

nvr_mat4f NibiruImport::NibiruGetSensorDataWithPosition(int *viewNumber, float* position)
{
	position[0] = 0;
	position[1] = 0;
	position[2] = 0;
	if (NibiruImport::pAPI_NibiruGetSensorDataWithPosition)
	{
		return NibiruImport::pAPI_NibiruGetSensorDataWithPosition(viewNumber, position);
	}
	nvr_mat4f tmp;
	return tmp;
}

/**
* 系统支持获取6dof，如果不支持，头部/手柄全部不能使用6dof
*/
bool NibiruImport::DoesSupport6DofData()
{
	return NibiruImport::pAPI_NibiruGetSensorDataWithPosition != nullptr;
}

void NibiruImport::NibiruGetNVRConfig(float* profile)
{
	if(NibiruImport::pAPI_NibiruGetNVRConfig)
	{
		NibiruImport::pAPI_NibiruGetNVRConfig(profile);
	}
}

void NibiruImport::NibiruResetHeadPose()
{
    if(NibiruImport::pAPI_NibiruResetHeadPose)
	{
		NibiruImport::pAPI_NibiruResetHeadPose();
	}
}

void NibiruImport::NibiruLockHeadPose()
{
	if(NibiruImport::pAPI_NibiruLockHeadPose)
	{
		NibiruImport::pAPI_NibiruLockHeadPose();
	}
}

void NibiruImport::NibiruUnLockHeadPose()
{
	if(NibiruImport::pAPI_NibiruUnLockHeadPose)
	{
		NibiruImport::pAPI_NibiruUnLockHeadPose();
	}
}

void NibiruImport::NibiruEnterVRMode(const nvrModeParms * params)
{
	if(NibiruImport::pAPI_NibiruEnterVRMode)
	{
		NibiruImport::pAPI_NibiruEnterVRMode(params);
	}
}

void NibiruImport::NibiruLeaveVRMode()
{
	if(NibiruImport::pAPI_NibiruLeaveVRMode)
	{
		NibiruImport::pAPI_NibiruLeaveVRMode();
	}
}

void NibiruImport::NibiruDestory()
{
	if(NibiruImport::pAPI_NibiruDestory)
	{
		NibiruImport::pAPI_NibiruDestory();
	}
}

float NibiruImport::NibiruGetFloatValue(const char * property_name, float default_value)
{
	if(NibiruImport::pAPI_NibiruGetFloatValue)
	{
		return NibiruImport::pAPI_NibiruGetFloatValue(property_name, default_value);
	}
	return -1;
}

bool NibiruImport::NibiruSetFloatValue(const char * property_name, float value)
{
	if(NibiruImport::pAPI_NibiruSetFloatValue)
	{
		return NibiruImport::pAPI_NibiruSetFloatValue(property_name, value);
	}
	return false;
}

// int
int NibiruImport::NibiruGetIntValue(const char * property_name, int default_value)
{
	if(NibiruImport::pAPI_NibiruGetIntValue) 
	{
       return NibiruImport::pAPI_NibiruGetIntValue(property_name, default_value);
	}
	return -1;
}

bool NibiruImport::NibiruSetIntValue(const char * property_name, int value)
{
	if(NibiruImport::pAPI_NibiruSetIntValue)
	{
		return NibiruImport::pAPI_NibiruSetIntValue(property_name, value);
	}
	return false;
}

// 参数获取设置
char* NibiruImport::NibiruGetParameter(const char * property_name)
{
	if(NibiruImport::pAPI_NibiruGetParameter)
	{
		return NibiruImport::pAPI_NibiruGetParameter(property_name);
	}
	return nullptr;
}


bool  NibiruImport::NibiruSetPatameter(const char * property_name, char* default_data)
{
	if(NibiruImport::pAPI_NibiruSetPatameter)
	{
		return NibiruImport::pAPI_NibiruSetPatameter(property_name, default_data);
	}
	return false;
}

void NibiruImport::NibiruComputeDistortedPoint(const int32_t eye, const nvr_vec2f uv_in, nvr_vec2f uv_out[3])
{
	if(NibiruImport::pAPI_NibiruComputeDistortedPoint) {
		NibiruImport::pAPI_NibiruComputeDistortedPoint(eye, uv_in, uv_out);
	}
}
// gen textures for double eyes
void NibiruImport::NibiruCreateTextures(int* ids)
{
	if(NibiruImport::pAPI_NibiruCreateTextures)
	{
		NibiruImport::pAPI_NibiruCreateTextures(ids);
	}
}

// notify the texture has render ok
bool NibiruImport::NibiruSetTexture(void * texture, int viewNum)
{
	if(NibiruImport::pAPI_NibiruSetTexture)
	{
		return NibiruImport::pAPI_NibiruSetTexture(texture, viewNum);
	}
	return false;
}

// 手柄接口
void NibiruImport::NibiruGetControllerRotPos(nvr_controller_type hand, float *dest, int length)
{
	if(NibiruImport::pAPI_NibiruController_GetRotPos)
	{
		NibiruImport::pAPI_NibiruController_GetRotPos(hand, dest, length);
	}
}

bool NibiruImport::NibiruGetControllerTouchDown(nvr_controller_type handType)
{
	if(NibiruImport::pAPI_NibiruController_IsTouchDown){
		return NibiruImport::pAPI_NibiruController_IsTouchDown(handType);
	}
	return false;
}

bool NibiruImport::NibiruGetControllerTouchUp(nvr_controller_type handType)
{
	if(NibiruImport::pAPI_NibiruController_IsTouchUp)
	{
       return NibiruImport::pAPI_NibiruController_IsTouchUp(handType);
	}
	return false;
}

bool NibiruImport::NibiruGetControllerTouchPressed(nvr_controller_type handType)
{
	if(NibiruImport::pAPI_NibiruController_IsTouchPressed)
	{
       return NibiruImport::pAPI_NibiruController_IsTouchPressed(handType);
	}
	return false;
}

void NibiruImport::NibiruGetControllerTouchPosition(nvr_controller_type handType, nvr_vec2f &position)
{
	if(NibiruImport::pAPI_NibiruController_GetTouchPosition)
	{
       NibiruImport::pAPI_NibiruController_GetTouchPosition(handType, position);
	}
}

bool NibiruImport::NibiruGetButtonDown(nvr_controller_type handType, nvr_keycode keyCode)
{
	if(NibiruImport::pAPI_NibiruController_IsButtonDown)
	{
       return NibiruImport::pAPI_NibiruController_IsButtonDown(handType, keyCode);
	}
	return false;
}

bool NibiruImport::NibiruGetButtonUp(nvr_controller_type handType, nvr_keycode keyCode)
{
	if(NibiruImport::pAPI_NibiruController_IsButtonUp)
	{
       return NibiruImport::pAPI_NibiruController_IsButtonUp(handType, keyCode);
	}
	return false;
}

bool NibiruImport::NibiruGetButtonPressed(nvr_controller_type handType, nvr_keycode keyCode)
{
	if(NibiruImport::pAPI_NibiruController_IsButtonPressed)
	{
       return NibiruImport::pAPI_NibiruController_IsButtonPressed(handType, keyCode);
	}
	return false;
}

bool NibiruImport::NibiruIsControllerConnected(nvr_controller_type handType)
{
	if(NibiruImport::pAPI_NibiruController_IsConnected)
	{
       return NibiruImport::pAPI_NibiruController_IsConnected(handType);
	}
	return false;
}

int  NibiruImport::NibiruGetControllerKeyState(nvr_controller_type handType)
{
	if(NibiruImport::pAPI_NibiruController_GetKeyState)
	{
       return NibiruImport::pAPI_NibiruController_GetKeyState(handType);
	}
	return 0;
}

int  NibiruImport::NibiruGetControllerBatteryLevel(nvr_controller_type handType)
{
	if(NibiruImport::pAPI_NibiruController_GetBatteryLevel)
	{
       return NibiruImport::pAPI_NibiruController_GetBatteryLevel(handType);
	}
	return 0;
}

void NibiruImport::NibiruResetController()
{
	if(NibiruImport::pAPI_NibiruController_Recenter)
	{
       NibiruImport::pAPI_NibiruController_Recenter();
	}
}

// 手柄接口
//===================== APIS =====================

#endif