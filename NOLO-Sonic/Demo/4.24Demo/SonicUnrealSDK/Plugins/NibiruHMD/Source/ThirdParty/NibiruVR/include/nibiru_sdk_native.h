/************************************************************************************
Filename    :   nibiru_sdk_native.h
Content     :
Created     :   02-13, 2017
Authors     :   nibiru.com
Copyright   :   Copyright 2017 Nibiru, Inc. All Rights reserved.
************************************************************************************/
#ifndef _NIBIRU_SDK_NATIVE_H_
#define _NIBIRU_SDK_NATIVE_H_
#define API_EXPORT __attribute__((visibility("default")))
#include <stdint.h>
#include "nvr_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NIBIRU_RUNTIME_VERSION(major, minor, revision)  ((((major) & 0xff) << 16) | (((minor) & 0xff) << 8) | ((revision) & 0xff))

#define NIB_KEY_MESH_X "key_mesh_x" // 畸变网格格式
#define NIB_KEY_MESH_Y "key_mesh_y"
#define NIB_KEY_SMALL_TEXTUTRE_SIZE "small_texture_size" // 纹理大小
#define NIB_KEY_ENABLE_POINT "enable_point"  // 白点显示
#define NIB_KEY_BEGIN_FRAME_NUM "begin_frame_num"
#define NIB_KEY_POINT_Z "point_z" // 白点z距离
 
API_EXPORT nvr_init_info NibiruInit(int pluginVersion ,long pointer ,const nvrModeParms * parms );
API_EXPORT nvr_mat4f NibiruGetSensorData(int *viewNumber);
API_EXPORT void NibiruGetNVRConfig(float* profile);
API_EXPORT void NibiruResetHeadPose();
API_EXPORT void NibiruLockHeadPose();
API_EXPORT void NibiruUnLockHeadPose();
API_EXPORT void NibiruEnterVRMode(const nvrModeParms * params);
API_EXPORT void NibiruLeaveVRMode();
API_EXPORT void NibiruDestory();
API_EXPORT float NibiruGetFloatValue(const char * property_name, float default_value);
API_EXPORT bool NibiruSetFloatValue(const char * property_name, float value);
// int
API_EXPORT int NibiruGetIntValue(const char * property_name, int default_value);
API_EXPORT bool NibiruSetIntValue(const char * property_name, int value);
// 参数获取设置
API_EXPORT char* NibiruGetParameter(const char * property_name);
API_EXPORT bool  NibiruSetPatameter(const char * property_name, char* default_data);

/// @param eye The nvr_eye type (left or right).
/// @param uv_in A point in screen eye Viewport Space in [0,1]^2 with (0, 0)
///     in the lower left corner of the eye's viewport and (1, 1) in the
///     upper right corner of the eye's viewport.
/// @param uv_out A pointer to an array of (at least) 3 elements, with each
///     element being a Point2f representing a point in render texture eye
///     Viewport Space in [0,1]^2 with (0, 0) in the lower left corner of the
///     eye's viewport and (1, 1) in the upper right corner of the eye's
///     viewport.
///     `uv_out[0]` is the corrected position of `uv_in` for the red channel
///     `uv_out[1]` is the corrected position of `uv_in` for the green channel
///     `uv_out[2]` is the corrected position of `uv_in` for the blue channel
API_EXPORT void NibiruComputeDistortedPoint(const int32_t eye, const nvr_vec2f uv_in, nvr_vec2f uv_out[3]);

// gen textures for double eyes
API_EXPORT void NibiruCreateTextures(int* ids);
// notify the texture has render ok
API_EXPORT bool NibiruSetTexture(void * texture, int viewNum);

#ifdef __cplusplus
}
#endif




#endif /* _NIBIRU_SDK_NATIVE_H_ */
