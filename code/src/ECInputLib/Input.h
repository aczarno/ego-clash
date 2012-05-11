/////////////////////////////////////////////////////////////////
//    File: Input.h
//  Author: Chris Blasko
// Updated: 2/28/2012
/////////////////////////////////////////////////////////////////
#pragma once

#include "Gamepad.h"
#include <map>


struct KeyState
{
	BYTE	Keys[256];
};

struct SimplePoint
{
	int x;
	int y;

	SimplePoint(int _x, int _y) : x(_x), y(_y) {}
};

class CInput
{
protected:
	// Class state
	static const int		s_XboxGamepadCount	= 4;
	static CInput*			s_Instance;

	// Instance state
	CGamepad*				m_XboxGamepads[s_XboxGamepadCount];		// XInput-supported gamepads
	KeyState				m_Keys;									// Current keyboard state
	KeyState				m_PrevKeys;								// Previous keyboard state

	// Constructor
	CInput();

	// Destructor
	~CInput();

public:
	// Retrieve singleton instance
	static CInput* GetInstance();

	// Delete singleton instance
	static void DeleteInstance();

	// Retrieve keyboard state
	void GetKeyState(KeyState* keys);

	// Retrieve previous keyboard state
	void GetPrevKeyState(KeyState* keys);

	// Reads user input
	virtual void Read();

	// Retrieve key state
	bool GetKey(int key);

	// Retrieve buffered key state
	bool GetBufferedKey(int key);

	// Retrieve gamepad
	CGamepad* GetXboxGamepad(unsigned int i);

	// Reacts to a device change
	void OnDeviceChange(WPARAM wParam, LPARAM lParam);

	POINT GetMousePos();
};