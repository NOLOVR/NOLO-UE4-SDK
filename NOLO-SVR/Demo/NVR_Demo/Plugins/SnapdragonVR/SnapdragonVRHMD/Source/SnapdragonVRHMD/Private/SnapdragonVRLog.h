#pragma once
#include "HMDPrivatePCH.h"
#include "HeadMountedDisplay.h"

#define NSVR_LOG_ANDROID_LOG (PLATFORM_ANDROID)

#if NSVR_LOG_ANDROID_LOG
#include <android/Log.h>
#define LOGV(TAG, fmt, ...) __android_log_print(ANDROID_LOG_VERBOSE, #TAG, fmt, __VA_ARGS__)
#define LOGD(TAG, fmt, ...) __android_log_print(ANDROID_LOG_DEBUG, #TAG, fmt, __VA_ARGS__)
#define LOG_NOARG(TAG, fmt) __android_log_print(ANDROID_LOG_DEBUG, #TAG, fmt)
#define LOGI(TAG, fmt, ...) __android_log_print(ANDROID_LOG_INFO, #TAG, fmt, __VA_ARGS__)
#define LOGW(TAG, fmt, ...) __android_log_print(ANDROID_LOG_WARN, #TAG, fmt, __VA_ARGS__)
#define LOGE(TAG, fmt, ...) __android_log_print(ANDROID_LOG_ERROR, #TAG, fmt, __VA_ARGS__)
#define USEWIDE(str) str
#else  // !NSVR_LOG_ANDROID_LOG
// fallback to UE_LOG
#define LOGV(CategoryName, Format, ...) UE_LOG(CategoryName, Verbose, TEXT(Format), __VA_ARGS__)
#define LOGD(CategoryName, Format, ...) UE_LOG(CategoryName, Display, TEXT(Format), __VA_ARGS__)
#define LOG_NOARG(CategoryName, Format) UE_LOG(CategoryName, Display, TEXT(Format));
#define LOGI(CategoryName, Format, ...) UE_LOG(CategoryName, Log, TEXT(Format), __VA_ARGS__)
#define LOGW(CategoryName, Format, ...) UE_LOG(CategoryName, Warning, TEXT(Format), __VA_ARGS__)
#define LOGE(CategoryName, Format, ...) UE_LOG(CategoryName, Error, TEXT(Format), __VA_ARGS__)
#define USEWIDE(str) *FString(str)  // Performance may not good.
#endif

#define NSVR_LOG_SHOW_ALL_ENTRY  0
#define NSVR_LOG_ENTRY_RENDER    (NSVR_LOG_SHOW_ALL_ENTRY || 0)
#define NSVR_LOG_ENTRY_LIFECYCLE (NSVR_LOG_SHOW_ALL_ENTRY || 1)
#define NSVR_LOG_ENTRY_HMD       (NSVR_LOG_SHOW_ALL_ENTRY || 0)
#define NSVR_LOG_ENTRY_STEREO    (NSVR_LOG_SHOW_ALL_ENTRY || 0)
#define NSVR_LOG_ENTRY_SCENEVIEW (NSVR_LOG_SHOW_ALL_ENTRY || 0)

#ifndef __FUNCTION__
// The g++ __func__ is too long to read.
#define NSVR_FUNCTION_STRING USEWIDE(__func__)
#else
#define WVR_FUNCTION_STRING USEWIDE(__FUNCTION__)
#endif

#if NSVR_LOG_SHOW_ALL_ENTRY && NSVR_SUPPORTED_PLATFORMS
#define LOG_FUNC() LOGD(LogSVR, "%s", NSVR_FUNCTION_STRING);
#else
#define LOG_FUNC()
#endif
#define LOG_FUNC_IF(expr) do { constexpr decltype(expr) var = (expr); if (var) { LOGD(LogSVR, "%s", NSVR_FUNCTION_STRING); } } while (0)
