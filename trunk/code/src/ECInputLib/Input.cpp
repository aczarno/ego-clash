#include "Input.h"
#include <assert.h>


CInput*			CInput::s_Instance = NULL;



CInput::CInput()
{
	for(int i = 0; i < s_XboxGamepadCount; ++i)
	{
		m_XboxGamepads[i] = new CGamepad(i);
		m_XboxGamepads[i]->ReadConnection();
	}
}


CInput::~CInput()
{
	for(int i = 0; i < s_XboxGamepadCount; ++i)
		delete m_XboxGamepads[i];
}


CInput* CInput::GetInstance()
{
	if(s_Instance == NULL)
		s_Instance = new CInput;
	return s_Instance;
}


void CInput::DeleteInstance()
{
	if(s_Instance)
		delete s_Instance;
	s_Instance = NULL;
}


void CInput::Read()
{
	m_PrevKeys = m_Keys;

	for(int i = 0; i < 256; i+=4)
	{
		m_Keys.Keys[i] = (GetAsyncKeyState(i) != 0);
		m_Keys.Keys[i+1] = (GetAsyncKeyState(i+1) != 0);
		m_Keys.Keys[i+2] = (GetAsyncKeyState(i+2) != 0);
		m_Keys.Keys[i+3] = (GetAsyncKeyState(i+3) != 0);
	}

	for(int i = 0; i < s_XboxGamepadCount; ++i)
	{
		if(m_XboxGamepads[i]->IsConnected())
			m_XboxGamepads[i]->ReadState();
	}
}


void CInput::GetKeyState(KeyState* keys)
{ 
	assert(keys);
	*keys = m_Keys; 
}


void CInput::GetPrevKeyState(KeyState* keys)
{ 
	assert(keys);
	*keys = m_PrevKeys; 
}


bool CInput::GetKey(int key) 
{ 
	return m_Keys.Keys[key] == 1; 
}


bool CInput::GetBufferedKey(int key)
{ 
	return (m_Keys.Keys[key] == 1) && !(m_PrevKeys.Keys[key] == 1); 
}


CGamepad* CInput::GetXboxGamepad(unsigned int i)
{ 
	assert(i < s_XboxGamepadCount); 
	return m_XboxGamepads[i]; 
}


void CInput::OnDeviceChange(WPARAM wParam, LPARAM lParam)
{
	for(int i = 0; i < s_XboxGamepadCount; ++i)
		m_XboxGamepads[i]->ReadConnection();
}