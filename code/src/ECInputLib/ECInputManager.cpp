#include "ECInputManager.h"

#define COMMANDBUFFER_LIFETIME		2.0f
#define COMMANDBUFFER_FRAMETIME		0.064f
#define DISPLAYEDBUFFER_SIZE		32


WORD	CECInputManager::s_XboxGamepadButtons[14] = 
{ 
	XINPUT_GAMEPAD_A, 
	XINPUT_GAMEPAD_B, 
	XINPUT_GAMEPAD_X, 
	XINPUT_GAMEPAD_Y, 
	XINPUT_GAMEPAD_RIGHT_SHOULDER, 
	XINPUT_GAMEPAD_LEFT_SHOULDER, 
	XINPUT_GAMEPAD_RIGHT_THUMB, 
	XINPUT_GAMEPAD_LEFT_THUMB, 
	XINPUT_GAMEPAD_START, 
	XINPUT_GAMEPAD_BACK, 
	XINPUT_GAMEPAD_DPAD_UP, 
	XINPUT_GAMEPAD_DPAD_DOWN, 
	XINPUT_GAMEPAD_DPAD_LEFT, 
	XINPUT_GAMEPAD_DPAD_RIGHT 
};



CECInputManager::CECInputManager() :
	m_Time(0.0f),
	m_Command(COMMAND_UNKNOWN),
	m_PrevCommand(COMMAND_UNKNOWN),
	m_UsingGamepad(false),
	m_XboxGamepadPort(0)
{
	m_Input = CInput::GetInstance();
	ZeroMemory(&m_KeyState, sizeof(m_KeyState));
	ZeroMemory(&m_GamepadState, sizeof(m_GamepadState));
}


CECInputManager::~CECInputManager()
{
}


void CECInputManager::SetGamepad(bool use, unsigned int portNum)
{
	m_UsingGamepad = use;
	m_XboxGamepadPort = portNum;
}


CGamepad* CECInputManager::GetGamepad()
{
	if(m_UsingGamepad == true)
		return m_Input->GetXboxGamepad(m_XboxGamepadPort);
	return NULL;
}


void CECInputManager::Update(float dt)
{
	m_CheckMoves = false;

	// Increment command buffer ages and remove record if age has passed the tolerance
	for(int i = m_CommandStates.size()-1; i >= 0; --i)
	{
		m_CommandStates[i].AddAge(dt);
		if(m_CommandStates[i].GetAge() >= COMMANDBUFFER_LIFETIME)
			m_CommandStates.pop_back();
	}

	// Update next command
	m_Input->Read();

	if(m_UsingGamepad == false)
	{
		KeyState Keys;
		m_Input->GetKeyState(&Keys);

		for(int i = 0; i < 256; i+=4)
		{
			m_KeyState.Keys[i] |= Keys.Keys[i];
			m_KeyState.Keys[i+1] |= Keys.Keys[i+1];
			m_KeyState.Keys[i+2] |= Keys.Keys[i+2];
			m_KeyState.Keys[i+3] |= Keys.Keys[i+3];
		}
	}
	else
	{
		CGamepad* Gamepad = m_Input->GetXboxGamepad(m_XboxGamepadPort);
		XINPUT_STATE State = Gamepad->GetState();
		m_GamepadState.Gamepad.wButtons |= State.Gamepad.wButtons;
		m_GamepadState.Gamepad.bLeftTrigger = State.Gamepad.bLeftTrigger;
		m_GamepadState.Gamepad.bRightTrigger = State.Gamepad.bRightTrigger;
		m_GamepadState.Gamepad.sThumbLX = State.Gamepad.sThumbLX;
		m_GamepadState.Gamepad.sThumbLY = State.Gamepad.sThumbLY;
		m_GamepadState.Gamepad.sThumbRX = State.Gamepad.sThumbRX;
		m_GamepadState.Gamepad.sThumbRY = State.Gamepad.sThumbRY;
	}

	m_Time += dt;
	if(m_Time > COMMANDBUFFER_FRAMETIME)
	{
		// Combine buttons
		FOR_EACH_BUTTON_COMMAND(i)
		{
			if(CheckCommand(i))
				m_Command |= i;
		}

		// Combine directions
		if(CheckCommand(COMMAND_UP))
		{
			if(CheckCommand(COMMAND_BACK))
				m_Command |= COMMAND_UPBACK;
			else if(CheckCommand(COMMAND_FORWARD))
				m_Command |= COMMAND_UPFORWARD;
			else
				m_Command |= COMMAND_UP;
		}
		else if(CheckCommand(COMMAND_DOWN))
		{
			if(CheckCommand(COMMAND_BACK))
				m_Command |= COMMAND_DOWNBACK;
			else if(CheckCommand(COMMAND_FORWARD))
				m_Command |= COMMAND_DOWNFORWARD;
			else
				m_Command |= COMMAND_DOWN;
		}
		else
		{
			if(CheckCommand(COMMAND_BACK))
				m_Command |= COMMAND_BACK;
			else if(CheckCommand(COMMAND_FORWARD))
				m_Command |= COMMAND_FORWARD;
		}

		ZeroMemory(m_KeyState.Keys, sizeof(m_KeyState.Keys));
		ZeroMemory(&m_GamepadState, sizeof(m_GamepadState));

		// Create new command state, add to deque if it is not empty
		CCommandState NewCommandState(m_PrevCommandState, m_Command, m_Time);
		if(NewCommandState.IsEmpty() == false)
		{
			m_CommandStates.push_front(NewCommandState);
			m_CheckMoves = true;

			if(NewCommandState.GetPressed() != COMMAND_UNKNOWN)
			{
				if(m_Commands.size() == DISPLAYEDBUFFER_SIZE)
					m_Commands.pop_back();
				m_Commands.push_front(NewCommandState.GetPressed());
			}
		}

		m_PrevCommandState = NewCommandState;
		m_PrevCommand = m_Command;
		m_Command = COMMAND_UNKNOWN;
		m_Time = 0.0f;
	}
}


bool CECInputManager::CheckKeys(int command)
{
	bool Res = false;

	std::vector<int>* Inputs = &m_CommandInputs[command];
	for(std::vector<int>::iterator It = Inputs->begin();
		It != Inputs->end(); ++It)
	{
		if(m_KeyState.Keys[*It] != 0)
		{
			Res = true;
			break;
		}
	}

	return Res;
}


bool CECInputManager::CheckGamepad(int command)
{
	bool Res = false;

	std::vector<int>* Inputs = &m_CommandInputs[command];
	for(std::vector<int>::iterator It = Inputs->begin();
		It != Inputs->end(); ++It)
	{
		int Input = (*It);
		if(Input < 14)
			Res = ((m_GamepadState.Gamepad.wButtons & s_XboxGamepadButtons[Input]) != 0);
		else if(Input == XBOX_GAMEPAD_BUTTON_RT)
			Res = (m_GamepadState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		else if(Input == XBOX_GAMEPAD_BUTTON_LT)
			Res = (m_GamepadState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		else if(Input == XBOX_GAMEPAD_BUTTON_LS_UP)
			Res = (m_GamepadState.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		else if(Input == XBOX_GAMEPAD_BUTTON_LS_DOWN)
			Res = (m_GamepadState.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		else if(Input == XBOX_GAMEPAD_BUTTON_LS_LEFT)
			Res = (m_GamepadState.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		else if(Input == XBOX_GAMEPAD_BUTTON_LS_RIGHT)
			Res = (m_GamepadState.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		else if(Input == XBOX_GAMEPAD_BUTTON_RS_UP)
			Res = (m_GamepadState.Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
		else if(Input == XBOX_GAMEPAD_BUTTON_RS_DOWN)
			Res = (m_GamepadState.Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
		else if(Input == XBOX_GAMEPAD_BUTTON_RS_LEFT)
			Res = (m_GamepadState.Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
		else if(Input == XBOX_GAMEPAD_BUTTON_RS_RIGHT)
			Res = (m_GamepadState.Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);

		if(Res == true)
			break;
	}

	return Res;
}


bool CECInputManager::CheckCommand(int command)
{
	bool Res = false;

	if(m_UsingGamepad == false)
		Res = CheckKeys(command);
	else
		Res = CheckGamepad(command);

	return Res;
}


bool CECInputManager::CheckMoves(CMove* move, CMoveMap& moves)
{
	bool Res = false;

	if(m_CheckMoves == true)
	{
		for(moves.Begin(); moves.End() == false; moves.Step())
		{
			if(CheckMove(*moves.Curr()) == true)
			{
				*move = *moves.Curr();
				m_CommandStates.clear();
				Res = true;
				break;
			}
		}
	}

	return Res;
}


bool CECInputManager::CheckMove(CMove& move)
{
	bool Found = false;

	CommandStateList::iterator JIt = m_CommandStates.begin();
	for(int i = move.Commands.size()-1; i >= 0; --i)
	{
		Found = false;

		for( ; JIt != m_CommandStates.end() && Found == false; )
		{
			if(JIt->GetAge() >= move.Tolerance)
				break;

			int Sum = COMMAND_UNKNOWN;
			if(move.Commands[i].State != COMMAND_STATE_HELD)
			{
				switch(move.Commands[i].State)
				{
				case(COMMAND_STATE_PRESSED):
					Sum = JIt->GetPressed();
					break;

				case(COMMAND_STATE_RELEASED):
					Sum = JIt->GetReleased();
					break;

				case(COMMAND_STATE_PRESSED_OR_HELD):
					Sum = (JIt->GetPressed() | JIt->GetHeld());
					break;

				case(COMMAND_STATE_PRESSED_OR_RELEASED):
					Sum = (JIt->GetPressed() | JIt->GetReleased());
					break;

				default:
					break;
				}

				if(move.Commands[i].Match)
					Found = (Sum == move.Commands[i].Commands);
				else
					Found = ((Sum & move.Commands[i].Commands) != COMMAND_UNKNOWN);
			}
			else
			{
				Sum = JIt->GetHeld();
				if((Sum == move.Commands[i].Commands) && 
				   (JIt->GetHoldTime(move.Commands[i].Commands) >= move.Commands[i].HoldTime))
				{
					Found = true;
				}
			}

			if(Found == false || move.Commands[i].CheckPrev == false)
				++JIt;
		}

		if(Found == false)
			break;
	}

	return Found;
}