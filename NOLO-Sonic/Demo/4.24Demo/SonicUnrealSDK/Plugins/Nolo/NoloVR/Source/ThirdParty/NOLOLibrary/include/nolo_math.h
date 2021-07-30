#pragma once
#ifndef _NOLO_V_0_1_RC_MATH_H_
#define _NOLO_V_0_1_RC_MATH_H_

//#define PC_PLATFORMS (PLATFORM_WINDOWS && WINVER > 0x0502)
//#define ANDROID_PLATFORMS (PLATFORM_ANDROID)
//#define NOLOVR_SUPPORTED_EMULATOR_PLATFORMS (WITH_EDITOR)
//#define NOLOVR_SUPPORTED_PC_PLATFORMS (PC_PLATFORMS || NOLOVR_SUPPORTED_EMULATOR_PLATFORMS)
//#define NOLOVR_SUPPORTED_Android_PLATFORMS (ANDROID_PLATFORMS || NOLOVR_SUPPORTED_EMULATOR_PLATFORMS)

#include <stdlib.h>
#include <memory>

typedef struct NVector2
{
	float x;
	float y;
}NVector2;

typedef struct NVector3
{
	float x;
	float y;
	float z;
}NVector3;

typedef struct NQuaternion
{
	float x;
	float y;
	float z;
	float w;
}NQuaternion;

typedef enum ENBattery
{
	ShutDown = 0,
	Low,
	Middle,
	High,

}ENBattery;

typedef enum ENDoubleClickKeyType {

	Press = 0,
	Trigger,
	Menu,
	Grip,
	Cancel
}ENDoubleClickKeyType;

// Enumerarion of NOLO devices types 
typedef enum EDeviceType
{
	Hmd = 0,
	LeftController,
	RightController,
	BaseStationOne,
}EDeviceType;

typedef enum ENExpandMsgType {
	//180 degree turn-around
	DoubleClickKeyTurnAround = 1,
	//recenter
	DoubleClickSystemRecenter

}ENExpandMsgType;

typedef struct NTrackedDevicePose
{
	NVector3 pos;
	NQuaternion rot;
	NVector3 vecVelocity; //速度
	NVector3 vecAngularVelocity;//角速度
	int  status;
	//bool bDeviceIsConnected;
	int bDeviceIsConnected;

}NTrackedDevicePose;

typedef struct NControllerState
{
	unsigned int buttons;//按键信息位
	unsigned int touches;//触摸信息位
	NVector2 touchpadAxis;
	NVector2 rAxis1;//保留位
	NVector2 rAxis2;//保留位
	NVector2 rAxis3;//保留位
	NVector2 rAxis4;//保留位

}NControllerState;
#endif // _NOLO_IMPORT_Version2_H_