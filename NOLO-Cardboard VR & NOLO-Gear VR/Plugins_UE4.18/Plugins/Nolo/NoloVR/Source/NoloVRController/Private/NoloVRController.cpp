// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "NoloVRController.h"
#include "Core.h"
#include "ModuleManager.h"
#include "IPluginManager.h"
#include "Engine/Engine.h"
#include "EngineGlobals.h"
#include "GenericPlatform/IInputInterface.h"
#include "InputCoreTypes.h"
#include "IXRTrackingSystem.h"
#define LOCTEXT_NAMESPACE "NoloVRControllerPlugin"

//Left Controller
const FKey FNoloKey::Nolo_Left_TouchPadPress("Nolo_Left_TouchPadPress");
const FKey FNoloKey::Nolo_Left_Trigger("Nolo_Left_Trigger");
const FKey FNoloKey::Nolo_Left_Menu("Nolo_Left_Menu");
const FKey FNoloKey::Nolo_Left_System("Nolo_Left_System");
const FKey FNoloKey::Nolo_Left_Grip("Nolo_Left_Grip");
const FKey FNoloKey::Nolo_Left_TouchPadTouch("Nolo_Left_TouchPadTouch");
const FKey FNoloKey::Nolo_Left_TouchPadUp("Nolo_Left_TouchPadUp");
const FKey FNoloKey::Nolo_Left_TouchPadDown("Nolo_Left_TouchPadDown");
const FKey FNoloKey::Nolo_Left_TouchPadLeft("Nolo_Left_TouchPadLeft");
const FKey FNoloKey::Nolo_Left_TouchPadRight("Nolo_Left_TouchPadRight");
const FKey FNoloAxis::Nolo_Left_Thumbstick_X("Nolo_Left_Thumbstick_X");
const FKey FNoloAxis::Nolo_Left_Thumbstick_Y("Nolo_Left_Thumbstick_Y");

//Right Controller
const FKey FNoloKey::Nolo_Right_TouchPadPress("Nolo_Right_TouchPadPress");
const FKey FNoloKey::Nolo_Right_Trigger("Nolo_Right_Trigger");
const FKey FNoloKey::Nolo_Right_Menu("Nolo_Right_Menu");
const FKey FNoloKey::Nolo_Right_System("Nolo_Right_System");
const FKey FNoloKey::Nolo_Right_Grip("Nolo_Right_Grip");
const FKey FNoloKey::Nolo_Right_TouchPadTouch("Nolo_Right_TouchPadTouch");
const FKey FNoloKey::Nolo_Right_TouchPadUp("Nolo_Right_TouchPadUp");
const FKey FNoloKey::Nolo_Right_TouchPadDown("Nolo_Right_TouchPadDown");
const FKey FNoloKey::Nolo_Right_TouchPadLeft("Nolo_Right_TouchPadLeft");
const FKey FNoloKey::Nolo_Right_TouchPadRight("Nolo_Right_TouchPadRight");
const FKey FNoloAxis::Nolo_Right_Thumbstick_X("Nolo_Right_Thumbstick_X");
const FKey FNoloAxis::Nolo_Right_Thumbstick_Y("Nolo_Right_Thumbstick_Y");
//Left Controller
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_TouchPadPress("Nolo_Left_TouchPadPress");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_Trigger("Nolo_Left_Trigger");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_Menu("Nolo_Left_Menu");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_System("Nolo_Left_System");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_Grip("Nolo_Left_Grip");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_TouchPadTouch("Nolo_Left_TouchPadTouch");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_TouchPadUp("Nolo_Left_TouchPadUp");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_TouchPadDown("Nolo_Left_TouchPadDown");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_TouchPadLeft("Nolo_Left_TouchPadLeft");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_TouchPadRight("Nolo_Left_TouchPadRight");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_Thumbstick_X("Nolo_Left_Thumbstick_X");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Left_Thumbstick_Y("Nolo_Left_Thumbstick_Y");
//Right Controller
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_TouchPadPress("Nolo_Right_TouchPadPress");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_Trigger("Nolo_Right_Trigger");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_Menu("Nolo_Right_Menu");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_System("Nolo_Right_System");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_Grip("Nolo_Right_Grip");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_TouchPadTouch("Nolo_Right_TouchPadTouch");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_TouchPadUp("Nolo_Right_TouchPadUp");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_TouchPadDown("Nolo_Right_TouchPadDown");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_TouchPadLeft("Nolo_Right_TouchPadLeft");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_TouchPadRight("Nolo_Right_TouchPadRight");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_Thumbstick_X("Nolo_Right_Thumbstick_X");
const FNoloKeyNames::Type FNoloKeyNames::Nolo_Right_Thumbstick_Y("Nolo_Right_Thumbstick_Y");


namespace NoloVRControllerKeyNames
{
	const FGamepadKeyNames::Type Touch0("Steam_Touch_0");
	const FGamepadKeyNames::Type Touch1("Steam_Touch_1");
}

FName FNoloVRController::DeviceTypeName(TEXT("NoloVRController"));
ENoloVRTouchDPadMapping FNoloVRController::DefaultDPadMapping = ENoloVRTouchDPadMapping::FaceButtons;

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


	Buttons[(int32)EControllerHand::Left][(int32)ENoloVRControllerButton::System] = FGamepadKeyNames::SpecialLeft;
	Buttons[(int32)EControllerHand::Left][(int32)ENoloVRControllerButton::Menu] = FGamepadKeyNames::MotionController_Left_Shoulder;
	Buttons[(int32)EControllerHand::Left][(int32)ENoloVRControllerButton::TouchPadPress] = FGamepadKeyNames::MotionController_Left_Thumbstick;
	Buttons[(int32)EControllerHand::Left][(int32)ENoloVRControllerButton::TouchPadTouch] = NoloVRControllerKeyNames::Touch0;
	Buttons[(int32)EControllerHand::Left][(int32)ENoloVRControllerButton::Trigger] = FGamepadKeyNames::MotionController_Left_Trigger;
	Buttons[(int32)EControllerHand::Left][(int32)ENoloVRControllerButton::Grip] = FGamepadKeyNames::MotionController_Left_Grip1;

	Buttons[(int32)EControllerHand::Right][(int32)ENoloVRControllerButton::System] = FGamepadKeyNames::SpecialRight;
	Buttons[(int32)EControllerHand::Right][(int32)ENoloVRControllerButton::Menu] = FGamepadKeyNames::MotionController_Right_Shoulder;
	Buttons[(int32)EControllerHand::Right][(int32)ENoloVRControllerButton::TouchPadPress] = FGamepadKeyNames::MotionController_Right_Thumbstick;
	Buttons[(int32)EControllerHand::Right][(int32)ENoloVRControllerButton::TouchPadTouch] = NoloVRControllerKeyNames::Touch1;
	Buttons[(int32)EControllerHand::Right][(int32)ENoloVRControllerButton::Trigger] = FGamepadKeyNames::MotionController_Right_Trigger;
	Buttons[(int32)EControllerHand::Right][(int32)ENoloVRControllerButton::Grip] = FGamepadKeyNames::MotionController_Right_Grip1;
	// Init Left & Right, TouchPadUp/Down/Left/Right button mappings
	SetTouchDPadMapping(DefaultDPadMapping);

	//Left Controller
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Left_TouchPadPress, LOCTEXT("Nolo_Left_TouchPadPress", "Nolo(L)TouchPadPress"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Left_Trigger, LOCTEXT("Nolo_Left_Trigger", "Nolo(L)Trigger"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Left_Menu, LOCTEXT("Nolo_Left_Menu", "Nolo(L)Menu"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Left_System, LOCTEXT("Nolo_Left_System", "Nolo(L)System"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Left_Grip, LOCTEXT("Nolo_Left_Grip", "Nolo(L)Grip"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Left_TouchPadTouch, LOCTEXT("Nolo_Left_TouchPadTouch", "Nolo(L)TouchPadTouch"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Left_TouchPadUp, LOCTEXT("Nolo_Left_TouchPadUp", "Nolo(L)TouchPadUp"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Left_TouchPadDown, LOCTEXT("Nolo_Left_TouchPadDown", "Nolo(L)TouchPadDown"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Left_TouchPadLeft, LOCTEXT("Nolo_Left_TouchPadLeft", "Nolo(L)TouchPadLeft"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Left_TouchPadRight, LOCTEXT("Nolo_Left_TouchPadRight", "Nolo(L)TouchPadRight"), FKeyDetails::GamepadKey, "Nolo"));

	EKeys::AddKey(FKeyDetails(FNoloAxis::Nolo_Left_Thumbstick_X, LOCTEXT("Nolo_Left_Thumbstick_X", "Nolo(L)Thumbstick_X"), FKeyDetails::FloatAxis, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloAxis::Nolo_Left_Thumbstick_Y, LOCTEXT("Nolo_Left_Thumbstick_Y", "Nolo(L)Thumbstick_Y"), FKeyDetails::FloatAxis, "Nolo"));
	//Right Controller 
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Right_TouchPadPress, LOCTEXT("Nolo_Right_TouchPadPress", "Nolo(R)TouchPadPress"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Right_Trigger, LOCTEXT("Nolo_Right_Trigger", "Nolo(R)Trigger"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Right_Menu, LOCTEXT("Nolo_Right_Menu", "Nolo(R)Menu"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Right_System, LOCTEXT("Nolo_Right_System", "Nolo(R)System"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Right_Grip, LOCTEXT("Nolo_Right_Grip", "Nolo(R)Grip"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Right_TouchPadTouch, LOCTEXT("Nolo_Right_TouchPadTouch", "Nolo(R)TouchPadTouch"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Right_TouchPadUp, LOCTEXT("Nolo_Right_TouchPadUp", "Nolo(R)TouchPadUp"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Right_TouchPadDown, LOCTEXT("Nolo_Right_TouchPadDown", "Nolo(R)TouchPadDown"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Right_TouchPadLeft, LOCTEXT("Nolo_Right_TouchPadLeft", "Nolo(R)TouchPadLeft"), FKeyDetails::GamepadKey, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloKey::Nolo_Right_TouchPadRight, LOCTEXT("Nolo_Right_TouchPadRight", "Nolo(R)TouchPadRight"), FKeyDetails::GamepadKey, "Nolo"));

	EKeys::AddKey(FKeyDetails(FNoloAxis::Nolo_Right_Thumbstick_X, LOCTEXT("Nolo_Right_Thumbstick_X", "Nolo(R)Thumbstick_X"), FKeyDetails::FloatAxis, "Nolo"));
	EKeys::AddKey(FKeyDetails(FNoloAxis::Nolo_Right_Thumbstick_Y, LOCTEXT("Nolo_Right_Thumbstick_Y", "Nolo(R)Thumbstick_Y"), FKeyDetails::FloatAxis, "Nolo"));
}

void FNoloVRController::SetTouchDPadMapping(ENoloVRTouchDPadMapping NewMapping)
{
	DefaultDPadMapping = NewMapping;

	switch (NewMapping)
	{
	case ENoloVRTouchDPadMapping::FaceButtons:

		Buttons[(int32)EControllerHand::Left][(int32)ENoloVRControllerButton::TouchPadUp] = FGamepadKeyNames::MotionController_Left_FaceButton1;
		Buttons[(int32)EControllerHand::Left][(int32)ENoloVRControllerButton::TouchPadDown] = FGamepadKeyNames::MotionController_Left_FaceButton3;
		Buttons[(int32)EControllerHand::Left][(int32)ENoloVRControllerButton::TouchPadLeft] = FGamepadKeyNames::MotionController_Left_FaceButton4;
		Buttons[(int32)EControllerHand::Left][(int32)ENoloVRControllerButton::TouchPadRight] = FGamepadKeyNames::MotionController_Left_FaceButton2;

		Buttons[(int32)EControllerHand::Right][(int32)ENoloVRControllerButton::TouchPadUp] = FGamepadKeyNames::MotionController_Right_FaceButton1;
		Buttons[(int32)EControllerHand::Right][(int32)ENoloVRControllerButton::TouchPadDown] = FGamepadKeyNames::MotionController_Right_FaceButton3;
		Buttons[(int32)EControllerHand::Right][(int32)ENoloVRControllerButton::TouchPadLeft] = FGamepadKeyNames::MotionController_Right_FaceButton4;
		Buttons[(int32)EControllerHand::Right][(int32)ENoloVRControllerButton::TouchPadRight] = FGamepadKeyNames::MotionController_Right_FaceButton2;
		break;

	case ENoloVRTouchDPadMapping::ThumbstickDirections:
		Buttons[(int32)EControllerHand::Left][(int32)ENoloVRControllerButton::TouchPadUp] = FGamepadKeyNames::MotionController_Left_Thumbstick_Up;
		Buttons[(int32)EControllerHand::Left][(int32)ENoloVRControllerButton::TouchPadDown] = FGamepadKeyNames::MotionController_Left_Thumbstick_Down;
		Buttons[(int32)EControllerHand::Left][(int32)ENoloVRControllerButton::TouchPadLeft] = FGamepadKeyNames::MotionController_Left_Thumbstick_Left;
		Buttons[(int32)EControllerHand::Left][(int32)ENoloVRControllerButton::TouchPadRight] = FGamepadKeyNames::MotionController_Left_Thumbstick_Right;

		Buttons[(int32)EControllerHand::Right][(int32)ENoloVRControllerButton::TouchPadUp] = FGamepadKeyNames::MotionController_Right_Thumbstick_Up;
		Buttons[(int32)EControllerHand::Right][(int32)ENoloVRControllerButton::TouchPadDown] = FGamepadKeyNames::MotionController_Right_Thumbstick_Down;
		Buttons[(int32)EControllerHand::Right][(int32)ENoloVRControllerButton::TouchPadLeft] = FGamepadKeyNames::MotionController_Right_Thumbstick_Left;
		Buttons[(int32)EControllerHand::Right][(int32)ENoloVRControllerButton::TouchPadRight] = FGamepadKeyNames::MotionController_Right_Thumbstick_Right;
		break;

	default:
		//UE_LOG(LogSteamVRController, Warning, TEXT("Unsupported d-pad mapping (%d). Defaulting to disabled."), (int32)NewMapping);
	case ENoloVRTouchDPadMapping::Disabled:
		Buttons[(int32)EControllerHand::Left][(int32)ENoloVRControllerButton::TouchPadUp] = FGamepadKeyNames::Invalid;
		Buttons[(int32)EControllerHand::Left][(int32)ENoloVRControllerButton::TouchPadDown] = FGamepadKeyNames::Invalid;
		Buttons[(int32)EControllerHand::Left][(int32)ENoloVRControllerButton::TouchPadLeft] = FGamepadKeyNames::Invalid;
		Buttons[(int32)EControllerHand::Left][(int32)ENoloVRControllerButton::TouchPadRight] = FGamepadKeyNames::Invalid;

		Buttons[(int32)EControllerHand::Right][(int32)ENoloVRControllerButton::TouchPadUp] = FGamepadKeyNames::Invalid;
		Buttons[(int32)EControllerHand::Right][(int32)ENoloVRControllerButton::TouchPadDown] = FGamepadKeyNames::Invalid;
		Buttons[(int32)EControllerHand::Right][(int32)ENoloVRControllerButton::TouchPadLeft] = FGamepadKeyNames::Invalid;
		Buttons[(int32)EControllerHand::Right][(int32)ENoloVRControllerButton::TouchPadRight] = FGamepadKeyNames::Invalid;
		break;
	}
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
		for (int32 HandIndex = 0; HandIndex < 2; HandIndex++) {
			const bool bIsLeft = (HandIndex == (int32)EControllerHand::Left);
			NControllerState nc = (bIsLeft ? noloVR->GetControllerStateByDeviceType(1) : noloVR->GetControllerStateByDeviceType(2));

			const float NoloThumbstick_X = nc.touchpadAxis.x;
			const float NoloThumbstick_Y = nc.touchpadAxis.y;

			if (NoloThumbstick_X != ControllerStates[HandIndex].ThumbstickAxes.X) {

				ControllerStates[HandIndex].ThumbstickAxes.X = NoloThumbstick_X;
				MessageHandler->OnControllerAnalog(bIsLeft ? FNoloKeyNames::Nolo_Left_Thumbstick_X : FNoloKeyNames::Nolo_Right_Thumbstick_X, 0, ControllerStates[HandIndex].ThumbstickAxes.X);
			}
			if (NoloThumbstick_Y != ControllerStates[HandIndex].ThumbstickAxes.Y) {

				ControllerStates[HandIndex].ThumbstickAxes.Y = NoloThumbstick_Y;
				MessageHandler->OnControllerAnalog(bIsLeft ? FNoloKeyNames::Nolo_Left_Thumbstick_Y : FNoloKeyNames::Nolo_Right_Thumbstick_Y, 0, ControllerStates[HandIndex].ThumbstickAxes.Y);
			}

			for (int32 ButtonIndex = 0; ButtonIndex < (int32)ENoloVRControllerButton::TotalButtonCount; ++ButtonIndex)
			{
				bool bButtonPressed = false;

				switch ((ENoloVRControllerButton)ButtonIndex)
				{
				case ENoloVRControllerButton::TouchPadPress:
					bButtonPressed = (nc.buttons & (0x01 << 0))>0 ? true : false;
					break;
				case ENoloVRControllerButton::Trigger:
					bButtonPressed = (nc.buttons & (0x01 << 1))>0 ? true : false;
					break;
				case ENoloVRControllerButton::Menu:
					bButtonPressed = (nc.buttons & (0x01 << 2))>0 ? true : false;
					break;
				case ENoloVRControllerButton::System:
					bButtonPressed = (nc.buttons & (0x01 << 3))>0 ? true : false;
					break;

				case ENoloVRControllerButton::Grip:
					bButtonPressed = (nc.buttons & (0x01 << 4))>0 ? true : false;
					break;

				case ENoloVRControllerButton::TouchPadTouch:
					bButtonPressed = nc.touches>0 ? true : false;
					
					break;
				case ENoloVRControllerButton::TouchPadUp:
					bButtonPressed = (nc.buttons & (0x01 << 8))>0 ? true : false;
				
					break;
				case ENoloVRControllerButton::TouchPadDown:
					bButtonPressed = (nc.buttons & (0x01 << 9))>0 ? true : false;
					
					break;
				case ENoloVRControllerButton::TouchPadLeft:
					bButtonPressed = (nc.buttons & (0x01 << 10))>0 ? true : false;
					
					break;
				case ENoloVRControllerButton::TouchPadRight:

					bButtonPressed = (nc.buttons & (0x01 << 11))>0 ? true : false;
					break;
				default:
					check(0);
					break;
				}

				//Doublie click left system  to ResetOrientation
				if (ControllerStates[HandIndex].Buttons[ButtonIndex].Key == FNoloKeyNames::Nolo_Left_System && ControllerStates[HandIndex].Buttons[ButtonIndex].bIsPressed && (!bButtonPressed)) {
					curTime = FPlatformTime::ToMilliseconds(FPlatformTime::Cycles());
					if (curTime - preLSDoubleSystemTime < 300)
					{
						//UE_LOG(LogTemp, Log, TEXT("=====================Doublie click system=====================\n"));
						if (GEngine->XRSystem.IsValid())
						{
							GEngine->XRSystem.Get()->ResetOrientation();
						}

						preLSDoubleSystemTime = 0;
					}
					else
					{
						preLSDoubleSystemTime = curTime;
					}
				}
				//Doublie click right system to ResetOrientation
				if (ControllerStates[HandIndex].Buttons[ButtonIndex].Key == FNoloKeyNames::Nolo_Right_System && ControllerStates[HandIndex].Buttons[ButtonIndex].bIsPressed && (!bButtonPressed)) {
					curTime = FPlatformTime::ToMilliseconds(FPlatformTime::Cycles());
					if (curTime - preRSDoubleSystemTime < 300)
					{
						//UE_LOG(LogTemp, Log, TEXT("=====================Doublie click system=====================\n"));
						if (GEngine->XRSystem.IsValid())
						{
							GEngine->XRSystem.Get()->ResetOrientation();
						}

						preRSDoubleSystemTime = 0.0;
					}
					else
					{
						preRSDoubleSystemTime = curTime;
					}
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
		noloVR->TriggerHapticPulse(Hand, Value * 100 > 100.0f ? 100 : Value);
	}
}

void FNoloVRController::SetChannelValues(int32 ControllerId, const FForceFeedbackValues & values)
{
	FNoloVRHMD *noloVR = GetNoloVRHMD();
	if (noloVR != nullptr) {
		noloVR->TriggerHapticPulse(EControllerHand::Left, (values.LeftLarge * 100) >100 ? 100 : values.LeftLarge * 100);
		noloVR->TriggerHapticPulse(EControllerHand::Right, (values.RightLarge * 100) >100 ? 100 : values.RightLarge * 100);
	}
	return;
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
	if (noloVR != nullptr) {
		FQuat DeviceOrientation = FQuat::Identity;
		RetVal = noloVR->GetControllerOrientationAndPosition(DeviceHand, OutPosition, DeviceOrientation);
		OutOrientation = DeviceOrientation.Rotator();
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
		noloVR->TriggerHapticPulse((EControllerHand)Hand, (Values.Frequency > 0.0f) ? Values.Amplitude * 100 : 0.0f);
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

// defined here in this .cpp file so we have access to FSteamVRController
void UNoloVRControllerLibrary::SetTouchDPadMapping(ENoloVRTouchDPadMapping NewMapping)
{

	// modify the default mapping in case we haven't instantiated a FSteamVRController yet
	FNoloVRController::DefaultDPadMapping = NewMapping;


	TArray<IMotionController*> MotionControllers = IModularFeatures::Get().GetModularFeatureImplementations<IMotionController>(IMotionController::GetModularFeatureName());
	
	for (IMotionController* MotionController : MotionControllers)
	{
		if (MotionController != nullptr && MotionController->GetMotionControllerDeviceTypeName() == FNoloVRController::DeviceTypeName)
		{
			static_cast<FNoloVRController*>(MotionController)->SetTouchDPadMapping(NewMapping);
		}
	}
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