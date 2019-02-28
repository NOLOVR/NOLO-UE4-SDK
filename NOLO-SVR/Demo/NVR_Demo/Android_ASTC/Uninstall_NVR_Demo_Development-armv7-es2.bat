setlocal
set ANDROIDHOME=%ANDROID_HOME%
if "%ANDROIDHOME%"=="" set ANDROIDHOME=D:/NVPACK/android-sdk-windows/android-sdk-windows
set ADB=%ANDROIDHOME%\platform-tools\adb.exe
set DEVICE=
if not "%1"=="" set DEVICE=-s %1
for /f "delims=" %%A in ('%ADB% %DEVICE% shell "echo $EXTERNAL_STORAGE"') do @set STORAGE=%%A
@echo.
@echo Uninstalling existing application. Failures here can almost always be ignored.
%ADB% %DEVICE% uninstall com.NoloVR.NVRDemo
@echo.
echo Removing old data. Failures here are usually fine - indicating the files were not on the device.
%ADB% %DEVICE% shell rm -r %STORAGE%/UE4Game/NVR_Demo
%ADB% %DEVICE% shell rm -r %STORAGE%/UE4Game/UE4CommandLine.txt
%ADB% %DEVICE% shell rm -r %STORAGE%/obb/com.NoloVR.NVRDemo
%ADB% %DEVICE% shell rm -r %STORAGE%/Android/obb/com.NoloVR.NVRDemo
@echo.
@echo Uninstall completed
