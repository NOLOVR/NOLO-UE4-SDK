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
@echo Installing existing application. Failures here indicate a problem with the device (connection or storage permissions) and are fatal.
%ADB% %DEVICE% install NVR_Demo-armv7-es2.apk
@if "%ERRORLEVEL%" NEQ "0" goto Error
%ADB% %DEVICE% shell rm -r %STORAGE%/UE4Game/NVR_Demo
%ADB% %DEVICE% shell rm -r %STORAGE%/UE4Game/UE4CommandLine.txt
%ADB% %DEVICE% shell rm -r %STORAGE%/obb/com.NoloVR.NVRDemo
%ADB% %DEVICE% shell rm -r %STORAGE%/Android/obb/com.NoloVR.NVRDemo






@echo.
@echo Grant READ_EXTERNAL_STORAGE and WRITE_EXTERNAL_STORAGE to the apk for reading OBB file or game file in external storage.
%ADB% %DEVICE% shell pm grant com.NoloVR.NVRDemo android.permission.READ_EXTERNAL_STORAGE
%ADB% %DEVICE% shell pm grant com.NoloVR.NVRDemo android.permission.WRITE_EXTERNAL_STORAGE
@echo.
@echo Installation successful
goto:eof
:Error
@echo.
@echo There was an error installing the game or the obb file. Look above for more info.
@echo.
@echo Things to try:
@echo Check that the device (and only the device) is listed with "%ADB$ devices" from a command prompt.
@echo Make sure all Developer options look normal on the device
@echo Check that the device has an SD card.
@pause
