// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "NoloVRController.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
//#include "IPluginManager.h"
#include "Engine/Engine.h"
#include "EngineGlobals.h"
#include "GenericPlatform/IInputInterface.h"
#include "InputCoreTypes.h"
#include "IXRTrackingSystem.h"
#define LOCTEXT_NAMESPACE "NoloVRControllerPlugin"

//Left Controller
const FKey FNoloKey::Nolo_Left_ThumbstickPress("Nolo_Left_ThumbstickPress");
const FKey FNoloKey::Nolo_Left_Trigger("Nolo_Left_Trigger");
const FKey FNoloKey::Nolo_Left_Menu("Nolo_Left_Menu");
const FKey FNoloKey::Nolo_Left_Grip("Nolo_Left_Grip");
const FKey FNoloKey::Nolo_Left_Thumbstick_Touch("Nolo_Left_Thumbstick_Touch");
const FKey FNoloKey::Nolo_Left_Thumbstick_Up("Nolo_Left_Thumbstick_Up");
const FKey FNoloKey::Nolo_Left_Thumbstick_Down("Nolo_Left_Thumbstick_Down");
const FKey FNoloKey::Nolo_Left_Thumbstick_Left("Nolo_Left_Thumbstick_Left");
const FKey FNoloKey::Nolo_Left_Thumbstick_Right("Nolo_Left_Thumbstick_Right");
const FKey FNoloKey::Nolo_Left_X("Nolo_Left_X");
const FKey FNoloKey::Nolo_Left_Y("Nolo_Left_Y");
const FKey FNoloKey::Nolo_Left_X_Touch("Nolo_Left_X_Touch");
const FKey FNoloKey::Nolo_Left_Y_Touch("Nolo_Left_Y_Touch");
const FKey FNoloKey::Nolo_Left_Trigger_Touch("Nolo_Left_Trigger_Touch");
const FKey FNoloAxis::Nolo_Left_Thumbstick_X("Nolo_Left_Thumbstick_X");
const FKey FNoloAxis::Nolo_Left_Thumbstick_Y("Nolo_Left_Thumbstick_Y");
const FKey FNoloAxis::Nolo_Left_Trigger_Value("Nolo_Left_Trigger_Value");

//Right Controller
const FKey FNoloKey::Nolo_Right_ThumbstickPress("Nolo_Right_ThumbstickPress");
const FKey FNoloKey::Nolo_Right_Trigger("Nolo_Right_Trigger");
const FKey FNoloKey::Nolo_Right_Menu("Nolo_Right_Menu");
const FKey FNoloKey::Nolo_Right_Grip("Nolo_Right_Grip");
const FKey FNoloKey::Nolo_Right_Thumbstick_Touch("Nolo_Right_Thumbstick_Touch");
const FKey FNoloKey::Nolo_Right_Thumbstick_Up("Nolo_Right_Thumbstick_Up");
const FKey FNoloKey::Nolo_Right_Thumbstick_Down("Nolo_Right_Thumbstick_Down");
const FKey FNoloKey::Nolo_Right_Thumbstick_Left("Nolo_Right_Thumbstick_Left");
const FKey FNoloKey::Nolo_Right_Thumbstick_Right("Nolo_Right_Thumbstick_Right");
const FKey FNoloKey::Nolo_Right_A("Nolo_Right_A");
const FKey FNoloKey::Nolo_Right_B("Nolo_Right_B");
const FKey FNoloKey::Nolo_Right_A_Touch("Nolo_Right_A_Touch");
const FKey FNoloKey::Nolo_Right_B_Touch("Nolo_Right_B_Touch");
const FKey FNoloKey::Nolo_Right_Trigger_Touch("Nolo_Right_Trigger_Touch");
const FKey FNoloAxis::Nolo_Right_Thumbstick_X("Nolo_Right_Thumbstick_A");
const FKey FNoloAxis::Nolo_Right_Thumbstick_Y("Nolo_Right_Thumbstick_B");
const FKey FNoloAxis::Nolo_Right_Trigger_Value("Nolo_Right_Trigger_Value");


//Left Controller
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_ThumbstickPress("Nolo_Left_ThumbstickPress");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_Trigger("Nolo_Left_Trigger");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_Menu("Nolo_Left_Menu");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_Grip("Nolo_Left_Grip");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_Thumbstick_Touch("Nolo_Left_Thumbstick_Touch");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_Thumbstick_Up("Nolo_Left_Thumbstick_Up");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_Thumbstick_Down("Nolo_Left_Thumbstick_Down");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_Thumbstick_Left("Nolo_Left_Thumbstick_Left");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_Thumbstick_Right("Nolo_Left_Thumbstick_Right");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_X("Nolo_Left_X");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_Y("Nolo_Left_Y");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_X_Touch("Nolo_Left_X_Touch");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_Y_Touch("Nolo_Left_Y_Touch");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_Trigger_Touch("Nolo_Left_Trigger_Touch");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_Thumbstick_X("Nolo_Left_Thumbstick_X");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_Thumbstick_Y("Nolo_Left_Thumbstick_Y");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_Trigger_Value("Nolo_Left_Trigger_Value");
//Right Controller
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_ThumbstickPress("Nolo_Right_ThumbstickPress");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_Trigger("Nolo_Right_Trigger");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_Menu("Nolo_Right_Menu");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_Grip("Nolo_Right_Grip");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_Thumbstick_Touch("Nolo_Right_Thumbstick_Touch");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_Thumbstick_Up("Nolo_Right_Thumbstick_Up");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_Thumbstick_Down("Nolo_Right_Thumbstick_Down");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_Thumbstick_Left("Nolo_Right_Thumbstick_Left");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_Thumbstick_Right("Nolo_Right_Thumbstick_Right");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_A("Nolo_Right_A");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_B("Nolo_Right_B");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_A_Touch("Nolo_Right_A_Touch");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_B_Touch("Nolo_Right_B_Touch");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_Trigger_Touch("Nolo_Right_Trigger_Touch");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_Thumbstick_X("Nolo_Right_Thumbstick_A");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_Thumbstick_Y("Nolo_Right_Thumbstick_B");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_Trigger_Value("Nolo_Right_Trigger_Value");

namespace NoloVRControllerKeyNames
{
	const FGamepadKeyNames::Type Touch0("Steam_Touch_0");
	const FGamepadKeyNames::Type Touch1("Steam_Touch_1");
}

FName FNoloVRController::DeviceTypeName(TEXT("NoloVRController"));

FNoloVRController::FNoloVRController(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) : MessageHandler(InMessageHandler)
{
	// Register motion controller!
	IModularFeatures::Get().RegisterModularFeature(GetModularFeatureName(), this);

	ControllerStates[(int32)EControllerHand::Left] = FNoloControllerState(EControllerHand::Left);
	ControllerStates[(int32)EControllerHand::Right] = FNoloControllerState(EControllerHand::Right);
	// Initialize button repeat delays
	InitialButtonRepeatDelay = 0.2f;
	ButtonRepeatDelay = 0.1f;
	curTime = 0.0;
	preLSDoubleSystemTime = 0.0;
	preRSDoubleSystemTime = 0.0;
	PreInit();
}

FNoloVRController::~FNoloVRController()
{

	IModularFeatures::Get().UnregisterModularFeature(GetModularFeatureName(), this);

}

void FNoloVRController::PreInit()
{
	EKeys::AddMenuCategoryDisplayInfo("Nolo", LOCTEXT("Nolo Controller", "Nolo"), TEXT("GraphEditor.PadEvent_16x"));

	//Buttons[(int32)EControllerHand::Left][(int32)ENoloVRControllerButton::Menu] = FGamepadKeyNames::MotionController_Left_Shoulder;
	//Buttons[(int32)EControllerHand::Left][(int32)ENoloVRControllerButton::TouchPadPress] = FGamepadKeyNames::MotionController_Left_Thumbstick;
	Buttons[(int32)EControllerHand::Left][(int32)ENoloVRControllerButton::Thumbstick_Touch] = NoloVRControllerKeyNames::Touch0;
	//Buttons[(int32)EControllerHand::Left][(int32)ENoloVRControllerButton::Trigger] = FGamepadKeyNames::MotionController_Left_Trigger;
	//Buttons[(int32)EControllerHand::Left][(int32)ENoloVRControllerButton::Grip] = FGamepadKeyNames::MotionController_Left_Grip1;

	//Buttons[(int32)EControllerHand::Right][(int32)ENoloVRControllerButton::Menu] = FGamepadKeyNames::MotionController_Right_Shoulder;
	//Buttons[(int32)EControllerHand::Right][(int32)ENoloVRControllerButton::TouchPadPress] = FGamepadKeyNames::MotionController_Right_Thumbstick;
	Buttons[(int32)EControllerHand::Right][(int32)ENoloVRControllerButton::Thumbstick_Touch] = NoloVRControllerKeyNames::Touch1;
	//Buttons[(int32)EControllerHand::Right][(int32)ENoloVRControllerButton::Trigger] = FGamepadKeyNames::MotionController_Right_Trigger;
	//Buttons[(int32)EControllerHand::Right][(int32)ENoloVRControllerButton::Grip] = FGamepadKeyNames::MotionController_Right_Grip1;
	// Init Left & Right, TouchPadUp/Down/Left/Right button mappings

	//Left Controller
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Left_ThumbstickPress, LOCTEXT("Nolo_Left_ThumbstickPress", "Nolo(L)ThumbstickPress"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Left_Trigger, LOCTEXT("Nolo_Left_Trigger", "Nolo(L)Trigger"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Left_Menu, LOCTEXT("Nolo_Left_Menu", "Nolo(L)Menu"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Left_Grip, LOCTEXT("Nolo_Left_Grip", "Nolo(L)Grip"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Left_Thumbstick_Touch, LOCTEXT("Nolo_Left_Thumbstick_Touch", "Nolo(L)ThumbstickTouch"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Left_Thumbstick_Up, LOCTEXT("Nolo_Left_Thumbstick_Up", "Nolo(L)ThumbstickUp"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Left_Thumbstick_Down, LOCTEXT("Nolo_Left_Thumbstick_Down", "Nolo(L)ThumbstickDown"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Left_Thumbstick_Left, LOCTEXT("Nolo_Left_Thumbstick_Left", "Nolo(L)ThumbstickLeft"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Left_Thumbstick_Right, LOCTEXT("Nolo_Left_Thumbstick_Right", "Nolo(L)ThumbstickRight"), FKeyDetails::GamepadKey, "Nolo"));

	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Left_X, LOCTEXT("Nolo_Left_X", "Nolo(L)X"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Left_Y, LOCTEXT("Nolo_Left_Y", "Nolo(L)Y"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Left_X_Touch, LOCTEXT("Nolo_Left_X_Touch", "Nolo(L)XTouch"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Left_Y_Touch, LOCTEXT("Nolo_Left_Y_Touch", "Nolo(L)YTouch"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Left_Trigger_Touch, LOCTEXT("Nolo_Left_Trigger_Touch", "Nolo(L)TriggerTouch"), FKeyDetails::GamepadKey, "Nolo"));

	EKeys::AddKey(FKeyDetails(FNoloAxis::Nolo_Left_Thumbstick_X, LOCTEXT("Nolo_Left_Thumbstick_X", "Nolo(L)Thumbstick_X"), FKeyDetails::FloatAxis, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloAxis::Nolo_Left_Thumbstick_Y, LOCTEXT("Nolo_Left_Thumbstick_Y", "Nolo(L)Thumbstick_Y"), FKeyDetails::FloatAxis, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloAxis::Nolo_Left_Trigger_Value, LOCTEXT("Nolo_Left_Trigger_Value", "Nolo(L)TriggerValue"), FKeyDetails::FloatAxis, "Nolo"));
	//Right Controller 
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Right_ThumbstickPress, LOCTEXT("Nolo_Right_ThumbstickPress", "Nolo(R)ThumbstickPress"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Right_Trigger, LOCTEXT("Nolo_Right_Trigger", "Nolo(R)Trigger"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Right_Menu, LOCTEXT("Nolo_Right_Menu", "Nolo(R)Menu"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Right_Grip, LOCTEXT("Nolo_Right_Grip", "Nolo(R)Grip"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Right_Thumbstick_Touch, LOCTEXT("Nolo_Right_Thumbstick_Touch", "Nolo(R)ThumbstickTouch"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Right_Thumbstick_Up, LOCTEXT("Nolo_Right_Thumbstick_Up", "Nolo(R)ThumbstickUp"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Right_Thumbstick_Down, LOCTEXT("Nolo_Right_Thumbstick_Down", "Nolo(R)ThumbstickDown"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Right_Thumbstick_Left, LOCTEXT("Nolo_Right_Thumbstick_Left", "Nolo(R)ThumbstickLeft"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Right_Thumbstick_Right, LOCTEXT("Nolo_Right_Thumbstick_Right", "Nolo(R)ThumbstickRight"), FKeyDetails::GamepadKey, "Nolo"));

	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Right_A, LOCTEXT("Nolo_Right_A", "Nolo(R)A"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Right_B, LOCTEXT("Nolo_Right_Y", "Nolo(R)B"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Right_A_Touch, LOCTEXT("Nolo_Right_A_Touch", "Nolo(R)ATouch"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Right_B_Touch, LOCTEXT("Nolo_Right_B_Touch", "Nolo(R)BTouch"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Right_Trigger_Touch, LOCTEXT("Nolo_Right_Trigger_Touch", "Nolo(R)TriggerTouch"), FKeyDetails::GamepadKey, "Nolo"));

	EKeys::AddKey(FKeyDetails(FNoloAxis::Nolo_Right_Thumbstick_X, LOCTEXT("Nolo_Right_Thumbstick_X", "Nolo(R)Thumbstick_X"), FKeyDetails::FloatAxis, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloAxis::Nolo_Right_Thumbstick_Y, LOCTEXT("Nolo_Right_Thumbstick_Y", "Nolo(R)Thumbstick_Y"), FKeyDetails::FloatAxis, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloAxis::Nolo_Right_Trigger_Value, LOCTEXT("Nolo_Right_Trigger_Value", "Nolo(R)TriggerValue"), FKeyDetails::FloatAxis, "Nolo"));
}

void FNoloVRController::Tick(float DeltaTime)
{
}

void FNoloVRController::SendControllerEvents()
{
	FNoloVRHMD *noloVR = GetNoloVRHMD();
	if (MessageHandler.IsValid() && INoloVRControllerPlugin::IsAvailable() && noloVR != nullptr) {

		int controllerIndex = 0; // Apparantly I was lazy so there is only one controller firing events today!

		const double CurrentTime = FPlatformTime::Seconds();
		const float CurrentTimeFloat = FPlatformTime::ToSeconds(FPlatformTime::Cycles()); // Works with FMath functions
																						  // This weard statement simulates user holding down the button 1/3 of the time
		int noloProductType = noloVR->GetNoloProductType();
		for (int32 HandIndex = 0; HandIndex < 2; HandIndex++) {
			const bool bIsLeft = (HandIndex == (int32)EControllerHand::Left);
			NControllerState nc = (bIsLeft ? noloVR->GetControllerStateByDeviceType(1) : noloVR->GetControllerStateByDeviceType(2));
			
			const float NoloThumbstick_X = nc.touchpadAxis.x;
			const float NoloThumbstick_Y = nc.touchpadAxis.y;
			const float NoloTrigger_Value = nc.rAxis1.x;
			if (NoloThumbstick_X != ControllerStates[HandIndex].ThumbstickAxes.X) {

				ControllerStates[HandIndex].ThumbstickAxes.X = NoloThumbstick_X;
				MessageHandler->OnControllerAnalog(bIsLeft ? FNoloKeyNames::Nolo_Left_Thumbstick_X : FNoloKeyNames::Nolo_Right_Thumbstick_X, 0, ControllerStates[HandIndex].ThumbstickAxes.X);
			}
			if (NoloThumbstick_Y != ControllerStates[HandIndex].ThumbstickAxes.Y) {

				ControllerStates[HandIndex].ThumbstickAxes.Y = NoloThumbstick_Y;
				MessageHandler->OnControllerAnalog(bIsLeft ? FNoloKeyNames::Nolo_Left_Thumbstick_Y : FNoloKeyNames::Nolo_Right_Thumbstick_Y, 0, ControllerStates[HandIndex].ThumbstickAxes.Y);
			}
			if (NoloTrigger_Value != ControllerStates[HandIndex].TriggerAxis) {

				ControllerStates[HandIndex].TriggerAxis = NoloTrigger_Value;
				MessageHandler->OnControllerAnalog(bIsLeft ? FNoloKeyNames::Nolo_Left_Trigger_Value : FNoloKeyNames::Nolo_Right_Trigger_Value, 0, ControllerStates[HandIndex].TriggerAxis);
			}
			for (int32 ButtonIndex = 0; ButtonIndex < (int32)ENoloVRControllerButton::TotalButtonCount; ++ButtonIndex)
			{
				bool bButtonPressed = false;

				switch ((ENoloVRControllerButton)ButtonIndex)
				{
				case ENoloVRControllerButton::ThumbstickPress:
					bButtonPressed = (nc.buttons & (0x01 << 0))>0 ? true : false;
					break;
				case ENoloVRControllerButton::Trigger:
					bButtonPressed = (nc.buttons & (0x01 << 1))>0 ? true : false;
					break;
				case ENoloVRControllerButton::Menu:
					bButtonPressed = (nc.buttons & (0x01 << 2))>0 ? true : false;
					break;
				case ENoloVRControllerButton::Grip:
					bButtonPressed = (nc.buttons & (0x01 << 4))>0 ? true : false;
					break;

				case ENoloVRControllerButton::Thumbstick_Touch:
					bButtonPressed = (nc.touches & (0x01 << 0))>0 ? true : false;
					break;
				case ENoloVRControllerButton::XA_Touch:
					{
						if (noloProductType == 4)
						{
							bButtonPressed = bIsLeft? ((nc.touches & (0x01 << 3)) > 0 ? true : false) : ((nc.touches & (0x01 << 1)) > 0 ? true : false);
						}else
						{
							if ((nc.buttons & (0x01 << 0))>0 ? false : true )
							{
								bButtonPressed = NoloThumbstick_Y < -0.2f ? true : false;
							}	
						}
						break;
					}					
				case ENoloVRControllerButton::YB_Touch:
					{
						if (noloProductType == 4)
						{
							bButtonPressed = bIsLeft ? ((nc.touches & (0x01 << 4)) > 0 ? true : false) : ((nc.touches & (0x01 << 2)) > 0 ? true : false);
						}else
						{
							if ((nc.buttons & (0x01 << 0))>0 ? false : true )
							{
								bButtonPressed = NoloThumbstick_Y > 0.2f ? true : false;
							}	
						}					
						break;
					}
				case ENoloVRControllerButton::Trigger_Touch:
					bButtonPressed = ((nc.touches & (0x01 << 5)) > 0 ? true : false);
					break;
				case ENoloVRControllerButton::XA:
					{
						if (noloProductType == 4)
						{
							bButtonPressed = bIsLeft ? ((nc.buttons & (0x01 << 14)) > 0 ? true : false) : ((nc.buttons & (0x01 << 12)) > 0 ? true : false);
						}else
						{
							if ((nc.buttons & (0x01 << 0))>0 ? true : false )
							{
								bButtonPressed = NoloThumbstick_Y < -0.2f ? true : false;
							}	
						}					
						break;
					}
				case ENoloVRControllerButton::YB:
					{
						if (noloProductType == 4)
						{
							bButtonPressed = bIsLeft ? ((nc.buttons & (0x01 << 15)) > 0 ? true : false) : ((nc.buttons & (0x01 << 13)) > 0 ? true : false);
						}else
						{
							if ((nc.buttons & (0x01 << 0))>0 ? true : false )
							{
								bButtonPressed = NoloThumbstick_Y > 0.2f ? true : false;
							}	
						}					
						break;
					}
				case ENoloVRControllerButton::Thumbstick_Up:
					{
						if (noloProductType == 4 && ControllerStates[HandIndex].ThumbstickAxes.Size()>0.7) {
							float Angle = FMath::Atan2(ControllerStates[HandIndex].ThumbstickAxes.X, ControllerStates[HandIndex].ThumbstickAxes.Y);
							bButtonPressed = Angle >= (-1.0f / 4.0f) * PI && Angle <= (1.0f/4.0f)*PI;
						}
						break;
					}
					
				case ENoloVRControllerButton::Thumbstick_Down:
					{
						if (noloProductType == 4 && ControllerStates[HandIndex].ThumbstickAxes.Size() > 0.7) {
							float Angle = FMath::Atan2(ControllerStates[HandIndex].ThumbstickAxes.X, ControllerStates[HandIndex].ThumbstickAxes.Y);
							bButtonPressed = Angle >= (3.0f / 4.0f) * PI || Angle <= (-3.0f / 4.0f) * PI;
						}
						break;
					}
				case ENoloVRControllerButton::Thumbstick_Left:
					{
						if (noloProductType == 4 && ControllerStates[HandIndex].ThumbstickAxes.Size() > 0.7) {
							float Angle = FMath::Atan2(ControllerStates[HandIndex].ThumbstickAxes.X, ControllerStates[HandIndex].ThumbstickAxes.Y);
							bButtonPressed = Angle >= (-3.0f / 4.0f) * PI && Angle <= (-1.0f / 4.0f) * PI;
						}
						break;
					}
				case ENoloVRControllerButton::Thumbstick_Right:
					{
						if (noloProductType == 4 && ControllerStates[HandIndex].ThumbstickAxes.Size() > 0.7) {
							float Angle = FMath::Atan2(ControllerStates[HandIndex].ThumbstickAxes.X, ControllerStates[HandIndex].ThumbstickAxes.Y);
							bButtonPressed = Angle >= (1.0f / 4.0f) * PI && Angle <= (3.0f / 4.0f) * PI;
						}
						break;
					}
				default:
					check(0);
					break;
				}

				// Update button state
				if (bButtonPressed != ControllerStates[HandIndex].Buttons[ButtonIndex].bIsPressed) {

					const bool bIsRepeat = false;
					ControllerStates[HandIndex].Buttons[ButtonIndex].bIsPressed = bButtonPressed;
					if (ControllerStates[HandIndex].Buttons[ButtonIndex].bIsPressed)
					{
						const FGamepadKeyNames::Type ButtonId = Buttons[HandIndex][ButtonIndex];
						if (ButtonId != FGamepadKeyNames::Invalid)
						{
							MessageHandler->OnControllerButtonPressed(ButtonId, 0, /*IsRepeat =*/bIsRepeat);
						}
						MessageHandler->OnControllerButtonPressed(ControllerStates[HandIndex].Buttons[ButtonIndex].Key, 0, bIsRepeat);
						// Set the timer for the first repeat
						ControllerStates[HandIndex].Buttons[ButtonIndex].NextRepeatTime = CurrentTime + ButtonRepeatDelay;
					}
					else
					{
						const FGamepadKeyNames::Type ButtonId = Buttons[HandIndex][ButtonIndex];
						if (ButtonId != FGamepadKeyNames::Invalid)
						{
							MessageHandler->OnControllerButtonReleased(ButtonId, 0, /*IsRepeat =*/bIsRepeat);
						}
						MessageHandler->OnControllerButtonReleased(ControllerStates[HandIndex].Buttons[ButtonIndex].Key, 0, bIsRepeat);
					}
				}

				// Apply key repeat, if its time for that
				if (ControllerStates[HandIndex].Buttons[ButtonIndex].bIsPressed && ControllerStates[HandIndex].Buttons[ButtonIndex].NextRepeatTime <= CurrentTime)
				{
					const bool bIsRepeat = true;
					const FGamepadKeyNames::Type ButtonId = Buttons[HandIndex][ButtonIndex];
					if (ButtonId != FGamepadKeyNames::Invalid)
					{
						MessageHandler->OnControllerButtonPressed(ButtonId, 0, /*IsRepeat =*/bIsRepeat);
					}
					MessageHandler->OnControllerButtonPressed(ControllerStates[HandIndex].Buttons[ButtonIndex].Key, 0, bIsRepeat);
					// Set the timer for the next repeat
					ControllerStates[HandIndex].Buttons[ButtonIndex].NextRepeatTime = CurrentTime + ButtonRepeatDelay;
				}

			}
		}

	}
}

void FNoloVRController::SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
{
	MessageHandler = InMessageHandler;
}

bool FNoloVRController::Exec(UWorld * InWorld, const TCHAR * Cmd, FOutputDevice & Ar)
{
	return false;
}

void FNoloVRController::SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value)
{
	// Skip unless this is the left or right large channel, which we consider to be the only SteamVRController feedback channel
	if (ChannelType != FForceFeedbackChannelType::LEFT_LARGE && ChannelType != FForceFeedbackChannelType::RIGHT_LARGE)
	{
		return;
	}
	const EControllerHand Hand = (ChannelType == FForceFeedbackChannelType::LEFT_LARGE) ? EControllerHand::Left : EControllerHand::Right;
	FNoloVRHMD *noloVR = GetNoloVRHMD();
	if (noloVR != nullptr) {
		if (noloVR->GetNoloProductType() == 4)
		{
			noloVR->HapticWithArg(Hand, 0.05f,100.f,Value * 100 > 100.0f ? 100 : Value);

		}else
		{
			noloVR->TriggerHapticPulse(Hand, Value * 100 > 100.0f ? 100 : Value);
		}
	}
}



bool FNoloVRController::IsGamepadAttached() const
{
	FNoloVRHMD *noloVR = GetNoloVRHMD();
	if (noloVR != nullptr) {
		int32 PlayerIndex = 0;
		ETrackingStatus LeftHandTrackingStatus = GetControllerTrackingStatus(PlayerIndex, EControllerHand::Left);
		ETrackingStatus RightHandTrackingStatus = GetControllerTrackingStatus(PlayerIndex, EControllerHand::Right);
		return LeftHandTrackingStatus == ETrackingStatus::Tracked || RightHandTrackingStatus == ETrackingStatus::Tracked;
	}
	return false;
}

bool FNoloVRController::GetControllerOrientationAndPosition(const int32 ControllerIndex, const EControllerHand DeviceHand, FRotator & OutOrientation, FVector & OutPosition, float WorldToMetersScale) const
{
	bool RetVal = false;
	FNoloVRHMD *noloVR = GetNoloVRHMD();
	if (noloVR != nullptr)
	{
		FQuat DeviceOrientation = FQuat::Identity;
		RetVal = noloVR->GetControllerOrientationAndPosition(DeviceHand, OutPosition, DeviceOrientation);
		OutOrientation = DeviceOrientation.Rotator();
		if (RetVal && noloVR->GetNoloProductType() == 4 && GEngine && GEngine->XRSystem.IsValid())
		{
			FQuat HmdOrientation;
			FVector HmdPosition;
			RetVal = GEngine->XRSystem->GetCurrentPose(IXRTrackingSystem::HMDDeviceId, HmdOrientation, HmdPosition);
			OutOrientation = (HmdOrientation * DeviceOrientation).Rotator();
			OutPosition = HmdPosition + HmdOrientation * OutPosition;
		}
		return RetVal;
	}
	return false;
}

ETrackingStatus FNoloVRController::GetControllerTrackingStatus(const int32 ControllerIndex, const EControllerHand DeviceHand) const
{
	FNoloVRHMD *noloVR = GetNoloVRHMD();
	if (noloVR != nullptr) {
		return noloVR->GetTrackingStatusByDeviceType((int32)DeviceHand)>0 ? ETrackingStatus::Tracked : ETrackingStatus::NotTracked;
	}
	return ETrackingStatus::NotTracked;
}


void FNoloVRController::SetChannelValues(int32 ControllerId, const FForceFeedbackValues & values)
{
	FNoloVRHMD *noloVR = GetNoloVRHMD();
	if (noloVR != nullptr) {
		if (noloVR->GetNoloProductType() == 4)
		{
			if (values.LeftLarge>0)
			{
				noloVR->HapticWithArg(EControllerHand::Left, 0.05f,100.f,(values.LeftLarge * 100) >100 ? 100 : values.LeftLarge * 100);
			}
			if (values.RightLarge>0)
			{
				noloVR->HapticWithArg(EControllerHand::Right, 0.05f,100.f,(values.RightLarge * 100) >100 ? 100 : values.RightLarge * 100);
			}	
		}else
		{
			if (values.LeftLarge>0)
			{
				noloVR->TriggerHapticPulse(EControllerHand::Left, (values.LeftLarge * 100) >100 ? 100 : values.LeftLarge * 100);
			}
			if (values.RightLarge>0)
			{
				noloVR->TriggerHapticPulse(EControllerHand::Right, (values.RightLarge * 100) >100 ? 100 : values.RightLarge * 100);
			}
		}
		
	}
	return;
}

void FNoloVRController::SetHapticFeedbackValues(int32 ControllerId, int32 Hand, const FHapticFeedbackValues & Values)
{
	//UE_LOG(LogTemp, Log, TEXT("=====================SetHapticFeedbackValues=====================\n"));
	if (Hand != (int32)EControllerHand::Left && Hand != (int32)EControllerHand::Right)
	{
		return;
	}
	FNoloVRHMD *noloVR = GetNoloVRHMD();
	if (noloVR != nullptr) {
		int intensity = Values.Amplitude * 100 > 100 ? 100 : (int)Values.Amplitude * 100;
		if (noloVR->GetNoloProductType() == 4)
		{
			noloVR->HapticWithArg((EControllerHand)Hand, 0.01f,(Values.Frequency > 0.0f) ? Values.Frequency * 100 : 0.0f,(Values.Amplitude > 0.0f) ? Values.Amplitude * 100 : 0.0f);
		}else
		{
			noloVR->TriggerHapticPulse((EControllerHand)Hand, (Values.Frequency > 0.0f) ? Values.Amplitude * 100 : 0.0f);
		}	
	}
}

void FNoloVRController::GetHapticFrequencyRange(float & MinFrequency, float & MaxFrequency) const
{
	MinFrequency = 0.0f;
	MaxFrequency = 1.0f;
}

float FNoloVRController::GetHapticAmplitudeScale() const
{
	return 1.0f;
}


class FNoloVRControllerPlugin : public IInputDeviceModule
{
	virtual TSharedPtr< class IInputDevice > CreateInputDevice(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler) override
	{
		//UE_LOG(LogTemp, Log, TEXT("=========================CreateNoloVRDevice======================================\n"));
		return TSharedPtr< class IInputDevice >(new FNoloVRController(InMessageHandler));
	}
};
#undef LOCTEXT_NAMESPACE
IMPLEMENT_MODULE(FNoloVRControllerPlugin, NoloVRController)