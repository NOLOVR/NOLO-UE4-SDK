#pragma once
#ifndef _NOLO_V_0_1_RC_API_H_
#define _NOLO_V_0_1_RC_API_H_
#include "nolo_math.h"
#include <stdlib.h>
#include <memory>
#include <string>
//#ifndef NOLO_IMPORT
//#define NOLO_IMPORT  __declspec(dllimport)
//#else
//#define NOLO_IMPORT
//#endif
//#if PLATFORM_WINDOWS
//typedef void(__cdecl *funcCallBack)(void * context);
//typedef void(__cdecl *expandMsgCallBack)(ENExpandMsgType expandMsgType, void * context);
//#endif

#ifdef __cplusplus
extern "C" {
#endif

	/**
	******************************************************************************
	* Function description��Search for NOLO device
	* Parameter��NULL
	* Return Value��NULL
	* Remarks��NULL
	******************************************************************************
	*/
	void  OpenNoloDevice();
	/*
	******************************************************************************
	* Function description��Close the connection with NOLO device and release resources
	* Parameter��NULL
	* Return Value��NULL
	* Remarks��NULL
	******************************************************************************
	*/
	void  CloseNoloDevice();

	//------------------------------------Android API--------------------------------------
	/**
	******************************************************************************
	* Function description��Get devices power information
	* Parameter��int
	0:hmd
	1:Left conroller
	2:Right controller
	3:basestation
	* Return Value��int
	******************************************************************************
	*/
	int  getElectricityByDeviceType(int type);
	/**
	******************************************************************************
	* Function description��Get devices power information
	* Parameter��int
	0:hmd
	1:Left conroller
	2:Right controller
	3:basestation
	* Return Value��int
	******************************************************************************
	*/
	int  getElectricityNumberByDeviceType(int type);

	/*
	******************************************************************************
	* Function description��Set vibration functions of NOLO controller
	* Parameter��Parameter devicetype is an enumeration type,Parameter intensity : Vibration intensity range from 0~100, the bigger the stronger
	* Return Value��Return bool type
	* Remarks��Parameter devicetype ��
	0:hmd
	1:Left conroller
	2:Left controller
	3:basestation
	******************************************************************************
	*/
	bool triggerHapticPulse(int deviceType, int intensity);

	void setHmdType(int hmdType);
	
	/**
	******************************************************************************
	* Function description��Get device tracking information
	* Parameter��int
	0:hmd
	1:Left conroller
	2:Right controller
	3:basestation
	* Return Value��Nolo_Pose
	******************************************************************************
	*/
	NTrackedDevicePose  getPoseByDeviceType(int type);

	/**
	******************************************************************************
	* Function description��Get the handle status information
	* Parameter��int
	0:hmd
	1:Left conroller
	2:Left controller
	3:basestation
	* Return Value��Nolo_ControllerStates
	******************************************************************************
	*/
	NControllerState  getControllerStatesByDeviceType(int type);

	/**
	******************************************************************************
	* Function description��
	* Parameter��
	******************************************************************************
	*/
	void setAppKey(const char* data);

	/**
	******************************************************************************
	* Function description��
	* Parameter��
	******************************************************************************
	*/

	void reportError(const char* data);

	/**
	******************************************************************************
	* Function description��
	* Parameter��
	******************************************************************************
	*/
	bool isInstallNoloHome();
	/**
	******************************************************************************
	* Function description��
	* Parameter��
	******************************************************************************
	*/
	bool isStartUpNoloHome();

	/**
	******************************************************************************
	* Function description：获取产品类型
	* Parameter：    
	C1 = 0,
    CV1 = 1,
    CV1Pro = 2,
    Air = 3,
    M1 = 4
	******************************************************************************
	*/
	int getNoloProductType();
	/**
	******************************************************************************
	* Function description:线性马达震动接口
	* Parameter：
	******************************************************************************
	*/
	void hapticWithArg(int deviceType, float duration, float frequency, float amplitude);

	//将音频文件转为震动并播放
	void hapticWithAudioFile(char* path , int channel_number);
	
	/**音频震动
	* @param layout         //1 为单声道，2为双声道
	* @param format         //1为 FMT_S16 signed 16 bits
	* @param sample_rate    //采样率
	* @param channel_number //使用哪个声道，默认可以使用0
	*/
	void setHapticAudioConfig(int layout, int format, int sample_rate, int channel_number);
	
	/**音频震动
	* @param buffer         音频数据
	* @param nb_samples     采样点个数
	* @param channel_number //使用哪个声道，默认可以使用0
	*/
	void hapticWithAudioBuffer(uint8_t* buffer, int nb_samples, int channel_number);

	/*
	channel_number:1-left、2-right、3-left and right
	*/
	bool stopHaptic(int channel_number);
	/*
	channel_number:1-left、2-right、3-left and right
	loopCount:0-loop、not 0 -count
	*/
	bool hapticWithAudioFileLoop(char* path, int channel_number, int loopCount);
	
	bool m1Write(const void *buffer, uint32_t size);

	bool hapticWithConfig(float strength,int filtering,int channel_number);

	bool action(char *actionJson);
#ifdef __cplusplus
}
#endif

namespace nolovr {

	class NoloVrApi {
	public:

		NoloVrApi() {

		}
		// Deprecated factory-style create method.
		// TODO(btco): remove this once no one is using it.
		static std::unique_ptr<NoloVrApi> Create() {
			return std::unique_ptr<NoloVrApi>(new NoloVrApi());
		}

		void Search_Nolo_Device() {
#ifdef __ANDROID__
#else
			//search_Nolo_Device();
			OpenNoloDevice();
#endif 
		}

		void Close_Nolo_Device(){
#ifdef __ANDROID__
#else
			//close_Nolo_Device();
			 CloseNoloDevice();
#endif 
		}
		
		void SetHmdTrackingCenterByDeviceType(int deviceType) {
			//setHmdType(deviceType);
		}

		bool TriggerHapticPulse(int deviceType, int intensity) {
			if(intensity>0){
				triggerHapticPulse(deviceType,intensity);
			}
			return true;
		}
		
		NTrackedDevicePose GetPoseByDeviceType(int type) {
			static NTrackedDevicePose nTrackedDevicePose{ { 0,0,0 },{ 0,0,0,0 },{ 0,0,0 },{ 0,0,0 },1,true };
			nTrackedDevicePose = getPoseByDeviceType(type);
			if (isnan(nTrackedDevicePose.pos.x)|| isnan(nTrackedDevicePose.rot.w )) {
				nTrackedDevicePose.pos.x = 0.0; nTrackedDevicePose.pos.y = 0.0; nTrackedDevicePose.pos.z = 0.0;
				nTrackedDevicePose.rot.w = 1; nTrackedDevicePose.rot.x = 0; nTrackedDevicePose.rot.y = 0; nTrackedDevicePose.rot.z = 0;
			}
#if PLATFORM_ANDROID
			if (getNoloProductType() == 4 && type == 0)
			{
				nTrackedDevicePose.bDeviceIsConnected = 1;
			}
#endif
			return nTrackedDevicePose;
		}

		int GetElectricityByDeviceType(int deviceType) {
			int battery = 0;
#if PLATFORM_ANDROID
			battery = getElectricityNumberByDeviceType(deviceType);
#else
			battery = getElectricityByDeviceType(deviceType);
#endif
			return battery;
		}

		NControllerState GetControllerStateByDeviceType(int type) {
			static NControllerState nControllerState{ 0,0,{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 } };
			nControllerState = getControllerStatesByDeviceType(type);
			return nControllerState;
		}

		void SetAppKey(const char *data) {

#ifdef __ANDROID__
			setAppKey(data);
#else
			OpenNoloDevice();
#endif 
		}	
		void ReportError(const char* data) {
#ifdef __ANDROID__
			reportError(data);
#else
#endif 
		}

		bool IsInstallNoloHome() {
#ifdef __ANDROID__
			return isInstallNoloHome();
#else
			return true;
#endif 
			
		}

		bool IsStartUpNolohome() {
#ifdef __ANDROID__
			return isInstallNoloHome();
#else
			return true;
#endif 
		}

		int GetNoloProductType() {
#ifdef __ANDROID__
			return getNoloProductType();
#else
			return 2;
#endif 
		}

		void HapticWithArg(int deviceType, float duration, float frequency, float amplitude) {
#ifdef __ANDROID__
			hapticWithArg(deviceType,duration,frequency,amplitude);
#else
#endif 
		}

		void HapticWithAudioFile(char* path, int channel_number) {
#ifdef __ANDROID__
			if(getNoloProductType() == 4)
			{
				hapticWithAudioFile(path,channel_number);
			}			
#else
#endif 
		}

		void SetHapticAudioConfig(int layout, int format, int sample_rate, int channel_number) {
#ifdef __ANDROID__
			if(getNoloProductType() == 4)
			{
				setHapticAudioConfig(layout, format, sample_rate, channel_number);
			}
#else
#endif 
		}

		void HapticWithAudioBuffer(uint8_t *buffer, int nb_samples, int channel_number) {
#ifdef __ANDROID__
			if(getNoloProductType() == 4)
			{
				hapticWithAudioBuffer(buffer, nb_samples, channel_number);
			}
#else
#endif 
		}

		bool StopHaptic(int channel_number)
		{
#ifdef __ANDROID__
			if(getNoloProductType() == 4)
			{
				stopHaptic(channel_number);
				return true;
			}
			return false;
#else
			return false;
#endif 
		}
		
		bool HapticWithAudioFileLoop(char* path, int channel_number, int loopCount){
#ifdef __ANDROID__
			if(getNoloProductType() == 4)
			{
				hapticWithAudioFileLoop(path, channel_number, loopCount);
				return true;
			}
			return false;
#else
			return false;
#endif 
		}
		
		bool HapticWithConfig(float strength,int filtering,int channel_number){
#ifdef __ANDROID__
			if(getNoloProductType() == 4)
			{
				hapticWithConfig(strength,filtering,channel_number);
				UE_LOG(LogTemp,Log,TEXT("hapticWithConfig %f,%d,%d"),strength, filtering,channel_number);
				return true;
			}
			return false;
#else
			return false;
#endif 
		}

		bool Action(char *actionJson){
#ifdef __ANDROID__
			if(getNoloProductType() == 4)
			{
				action(actionJson);
				return true;
			}
			return false;
#else
			return false;
#endif 
		}
		
		bool m1Write(const void *buffer,uint32_t size){
#ifdef __ANDROID__
			if(getNoloProductType() == 4)
			{
				return m1Write(buffer, size);
			}
			return false;
#else
			return false;
#endif 
		}
		
	};
}

#endif // _NOLO_IMPORT_Version2_H_