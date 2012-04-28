/////////////////////////////////////////////////////////////////
//    File: Gamepad.h
//  Author: Chris Blasko
// Updated: 2/28/2012
/////////////////////////////////////////////////////////////////
#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>

#pragma comment(lib, "XInput.lib")


class CGamepad
{
private:
	//XINPUT_BATTERY_INFORMATION	m_BatteryInfo;
	XINPUT_CAPABILITIES			m_Capabilities;
	XINPUT_STATE				m_State, m_PrevState;
	unsigned int				m_PortNum;
	bool						m_IsConnected;

public:
	// Constructor
	CGamepad(int portNum);

	// Destructor
	~CGamepad(){};

	// Accessors
	//inline XINPUT_BATTERY_INFORMATION GetBatteryInfo(){ return m_BatteryInfo; }
	inline XINPUT_CAPABILITIES GetCapabilities(){ return m_Capabilities; }
	inline XINPUT_STATE GetState(){ return m_State; }
	inline unsigned int GetPortNum() { return m_PortNum; }
	inline bool IsConnected() const { return m_IsConnected; }
	//inline bool HasBattery() const { return (m_BatteryInfo.BatteryType != BATTERY_TYPE_WIRED); }

	// Read the gamepad's state
	XINPUT_STATE ReadState();

	// Check gamepad connection
	void ReadConnection();

	// Read gamepad capabilities
	void ReadCapabilities();

	// Read the gamepad's battery info
	//void ReadBatteryInfo()

	// Vibrate the gamepad
	void Vibrate(int left, int right);

	// Check gamepad's sub type
	// Use XINPUT_DEVSUBTYPE_XXXX
	inline bool IsSubTypeOf(WORD subType){ return ((m_Capabilities.SubType & subType) != 0); }
	//inline bool IsGamePad() { return IsSubTypeOf(XINPUT_DEVSUBTYPE_GAMEPAD); }
	//inline bool IsWheel() { return IsSubTypeOf(XINPUT_DEVSUBTYPE_WHEEL); }
	//inline bool IsArcadeStick() { return IsSubTypeOf(XINPUT_DEVSUBTYPE_ARCADE_STICK); }
	//inline bool IsGuitar() { return IsSubTypeOf(XINPUT_DEVSUBTYPE_GUITAR); }
	//inline bool IsDancePad() { return IsSubTypeOf(XINPUT_DEVSUBTYPE_DANCE_PAD); }
	//inline bool IsDrumKit() { return IsSubTypeOf(XINPUT_DEVSUBTYPE_DRUM_KIT); }
	//inline bool IsFlightStick() { return IsSubTypeOf(XINPUT_DEVSUBTYPE_FLIGHT_SICK); }

	// Check if button is pressed: use for d-pad, face buttons (A, B, X, Y), 
	// right shoulder (RB), left shoulder (LB), start and back
	// Use XINPUT_GAMEPAD_XXXX as argument
	inline bool IsButtonPressed(WORD button){ return ((m_State.Gamepad.wButtons & button) != 0); }
	inline bool IsAPressed(){ return IsButtonPressed(XINPUT_GAMEPAD_A); }
	inline bool IsBPressed(){ return IsButtonPressed(XINPUT_GAMEPAD_B); }
	inline bool IsXPressed(){ return IsButtonPressed(XINPUT_GAMEPAD_X); }
	inline bool IsYPressed(){ return IsButtonPressed(XINPUT_GAMEPAD_Y); }
	inline bool IsStartPressed(){ return IsButtonPressed(XINPUT_GAMEPAD_START); }
	inline bool IsBackPressed(){ return IsButtonPressed(XINPUT_GAMEPAD_BACK); }
	inline bool IsLBPressed(){ return IsButtonPressed(XINPUT_GAMEPAD_LEFT_SHOULDER); }
	inline bool IsRBPressed(){ return IsButtonPressed(XINPUT_GAMEPAD_RIGHT_SHOULDER); }
	inline bool IsLSPressed(){ return IsButtonPressed(XINPUT_GAMEPAD_LEFT_THUMB); }
	inline bool IsRSPressed(){ return IsButtonPressed(XINPUT_GAMEPAD_RIGHT_THUMB); }
	inline bool IsDPadUpPressed(){ return IsButtonPressed(XINPUT_GAMEPAD_DPAD_UP); }
	inline bool IsDPadDownPressed(){ return IsButtonPressed(XINPUT_GAMEPAD_DPAD_DOWN); }
	inline bool IsDPadLeftPressed(){ return IsButtonPressed(XINPUT_GAMEPAD_DPAD_LEFT); }
	inline bool IsDPadRightPressed(){ return IsButtonPressed(XINPUT_GAMEPAD_DPAD_RIGHT); }

	// Check if button is pressed and buffered: use for d-pad, face buttons (A, B, X, Y), 
	// right shoulder (RB), left shoulder (LB), start and back
	// Use XINPUT_GAMEPAD_XXXX as argument
	inline bool IsButtonPressedBuffered(WORD button){ return !(m_PrevState.Gamepad.wButtons & button) & ((m_State.Gamepad.wButtons & button) != 0); }
	inline bool IsAPressedBuffered(){ return IsButtonPressedBuffered(XINPUT_GAMEPAD_A); }
	inline bool IsBPressedBuffered(){ return IsButtonPressedBuffered(XINPUT_GAMEPAD_B); }
	inline bool IsXPressedBuffered(){ return IsButtonPressedBuffered(XINPUT_GAMEPAD_X); }
	inline bool IsYPressedBuffered(){ return IsButtonPressedBuffered(XINPUT_GAMEPAD_Y); }
	inline bool IsStartPressedBuffered(){ return IsButtonPressedBuffered(XINPUT_GAMEPAD_START); }
	inline bool IsBackPressedBuffered(){ return IsButtonPressedBuffered(XINPUT_GAMEPAD_BACK); }
	inline bool IsLBPressedBuffered(){ return IsButtonPressedBuffered(XINPUT_GAMEPAD_LEFT_SHOULDER); }
	inline bool IsRBPressedBuffered(){ return IsButtonPressedBuffered(XINPUT_GAMEPAD_RIGHT_SHOULDER); }
	inline bool IsLSPressedBuffered(){ return IsButtonPressedBuffered(XINPUT_GAMEPAD_LEFT_THUMB); }
	inline bool IsRSPressedBuffered(){ return IsButtonPressedBuffered(XINPUT_GAMEPAD_RIGHT_THUMB); }
	inline bool IsDPadUpPressedBuffered(){ return IsButtonPressedBuffered(XINPUT_GAMEPAD_DPAD_UP); }
	inline bool IsDPadDownPressedBuffered(){ return IsButtonPressedBuffered(XINPUT_GAMEPAD_DPAD_DOWN); }
	inline bool IsDPadLeftPressedBuffered(){ return IsButtonPressedBuffered(XINPUT_GAMEPAD_DPAD_LEFT); }
	inline bool IsDPadRightPressedBuffered(){ return IsButtonPressedBuffered(XINPUT_GAMEPAD_DPAD_RIGHT); }

	// Check if trigger is pressed according to threshold value
	// Threshold is the value the trigger must exceed to be considered pressed;
	// Can be any value from 0-255, defaults to 30	
	inline bool IsLTPressed(int threshold = XINPUT_GAMEPAD_TRIGGER_THRESHOLD){ return (m_State.Gamepad.bLeftTrigger > threshold); }
	inline bool IsRTPressed(int threshold = XINPUT_GAMEPAD_TRIGGER_THRESHOLD){ return (m_State.Gamepad.bRightTrigger > threshold); }
	inline bool IsLTPressedBuffered(int threshold = XINPUT_GAMEPAD_TRIGGER_THRESHOLD){ return !(m_PrevState.Gamepad.bLeftTrigger > threshold) & IsLTPressed(threshold); }
	inline bool IsRTPressedBuffered(int threshold = XINPUT_GAMEPAD_TRIGGER_THRESHOLD){ return !(m_PrevState.Gamepad.bRightTrigger > threshold) & IsRTPressed(threshold); }

	// Check if the left thumb stick has been moved into a direction
	// Deadzone represents the area in which the stick is considered inactive
	// Stick positions range from -32768 to 32767; Default deadzone is 7849
	inline bool IsLThumbUp(int deadzone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE){ return (m_State.Gamepad.sThumbLY > deadzone); }
	inline bool IsLThumbDown(int deadzone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE){ return (m_State.Gamepad.sThumbLY < -deadzone); }
	inline bool IsLThumbRight(int deadzone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE){ return (m_State.Gamepad.sThumbLX > deadzone); }
	inline bool IsLThumbLeft(int deadzone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE){ return (m_State.Gamepad.sThumbLX < -deadzone); }
	inline bool IsLThumbUpBuffered(int deadzone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE){ return !(m_State.Gamepad.sThumbLY > deadzone) & IsLThumbUp(deadzone); }
	inline bool IsLThumbDownBuffered(int deadzone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE){ return !(m_State.Gamepad.sThumbLY > deadzone) & IsLThumbDown(deadzone);  }
	inline bool IsLThumbRightBuffered(int deadzone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE){ return !(m_State.Gamepad.sThumbLX > deadzone) & IsLThumbLeft(deadzone);  }
	inline bool IsLThumbLeftBuffered(int deadzone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE){ return !(m_State.Gamepad.sThumbLX > deadzone) & IsLThumbRight(deadzone);  }

	// Check if the right thumb stick has been moved into a direction
	// Deadzone represents the area in which the stick is considered inactive
	// Stick positions range from -32768 to 32767; Default deadzone is 8689
	inline bool IsRThumbUp(int deadzone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE){ return (m_State.Gamepad.sThumbRY > deadzone); }
	inline bool IsRThumbDown(int deadzone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE){ return (m_State.Gamepad.sThumbRY < -deadzone); }
	inline bool IsRThumbRight(int deadzone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE){ return (m_State.Gamepad.sThumbRX > deadzone); }
	inline bool IsRThumbLeft(int deadzone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE){ return (m_State.Gamepad.sThumbRX < -deadzone); }
	inline bool IsRThumbUpBuffered(int deadzone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE){ return !(m_State.Gamepad.sThumbRY > deadzone) & IsRThumbUp(deadzone); }
	inline bool IsRThumbDownBuffered(int deadzone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE){ return !(m_State.Gamepad.sThumbRY > deadzone) & IsRThumbDown(deadzone);  }
	inline bool IsRThumbRightBuffered(int deadzone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE){ return !(m_State.Gamepad.sThumbRX > deadzone) & IsRThumbLeft(deadzone);  }
	inline bool IsRThumbLeftBuffered(int deadzone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE){ return !(m_State.Gamepad.sThumbRX > deadzone) & IsRThumbRight(deadzone);  }
};