#include "Gamepad.h"
#include <assert.h>



CGamepad::CGamepad(int portNum) : m_PortNum(portNum), m_IsConnected(false) 
{
	assert(portNum < 4);

	ZeroMemory(&m_State, sizeof(m_State)); 
	ZeroMemory(&m_Capabilities, sizeof(m_Capabilities));
}


XINPUT_STATE CGamepad::ReadState()
{
	assert(m_PortNum < 4);

	m_PrevState = m_State;
	DWORD Result = XInputGetState(m_PortNum, &m_State);
	m_IsConnected = (Result == ERROR_SUCCESS);
	return m_State;
}


void CGamepad::ReadConnection()
{
	assert(m_PortNum < 4);

	DWORD Res = XInputGetState(m_PortNum, &m_State);
	m_IsConnected = (Res == ERROR_SUCCESS);
}


void CGamepad::ReadCapabilities()
{
	assert(m_PortNum < 4);

	DWORD Res = XInputGetCapabilities(m_PortNum, XINPUT_FLAG_GAMEPAD, &m_Capabilities);
	m_IsConnected = (Res != ERROR_DEVICE_NOT_CONNECTED);
}


//void CGamepad::ReadBatteryInfo()
//{
//	assert(m_PortNum < 4);
//
//	DWORD Res = XInputGetBatteryInformation(m_PortNum, BATTERY_DEVTYPE_GAMEPAD, &m_BatteryInfo);
//}


void CGamepad::Vibrate(int left, int right)
{
	assert(m_PortNum < 4);

	XINPUT_VIBRATION Vibration;
	ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));
	Vibration.wLeftMotorSpeed = left;
	Vibration.wRightMotorSpeed = right;
	XInputSetState(m_PortNum, &Vibration);
}