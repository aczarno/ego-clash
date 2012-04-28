/////////////////////////////////////////////////////////////////
//    File: ECInputManager.h
//  Author: Chris Blasko
// Updated: 2/29/2012
/////////////////////////////////////////////////////////////////
#pragma once

#include "Input.h"
#include "Move.h"
#include "CommandState.h"
#include <deque>
#include <list>


// Xbox gamepad index definitions
#define XBOX_GAMEPAD_BUTTON_A				0
#define XBOX_GAMEPAD_BUTTON_B				1
#define XBOX_GAMEPAD_BUTTON_X				2
#define XBOX_GAMEPAD_BUTTON_Y				3
#define XBOX_GAMEPAD_BUTTON_RB				4
#define XBOX_GAMEPAD_BUTTON_LB				5
#define XBOX_GAMEPAD_BUTTON_RS				6
#define XBOX_GAMEPAD_BUTTON_LS				7
#define XBOX_GAMEPAD_BUTTON_START			8
#define XBOX_GAMEPAD_BUTTON_BACK			9
#define XBOX_GAMEPAD_BUTTON_DPAD_UP			10
#define XBOX_GAMEPAD_BUTTON_DPAD_DOWN		11
#define XBOX_GAMEPAD_BUTTON_DPAD_LEFT		12
#define XBOX_GAMEPAD_BUTTON_DPAD_RIGHT		13
#define XBOX_GAMEPAD_BUTTON_RT				14
#define XBOX_GAMEPAD_BUTTON_LT				15
#define XBOX_GAMEPAD_BUTTON_RS_UP			16
#define XBOX_GAMEPAD_BUTTON_RS_DOWN			17
#define XBOX_GAMEPAD_BUTTON_RS_LEFT			18
#define XBOX_GAMEPAD_BUTTON_RS_RIGHT		19
#define XBOX_GAMEPAD_BUTTON_LS_UP			20
#define XBOX_GAMEPAD_BUTTON_LS_DOWN			21
#define XBOX_GAMEPAD_BUTTON_LS_LEFT			22
#define XBOX_GAMEPAD_BUTTON_LS_RIGHT		23


// Types
typedef std::deque<int>					CommandList;
typedef std::deque<CCommandState>		CommandStateList;


// Manages user input; records and validates commands
class CECInputManager
{
private:
	// Types
	typedef std::map<int, std::vector<int>>		CommandInputMap;

	// Class state
	static WORD	s_XboxGamepadButtons[];			// Xbox gamepad buttons

	// Instance state
	CommandInputMap		m_CommandInputs;		// User input associated with each command
	CommandStateList	m_CommandStates;		// List of commands that have been performed by the user; this will be cleared after a 
												// move has been performed and items older than the tolerance time frame will be removed
	CommandList			m_Commands;				// List of the previous commands which will be displayed to the user
	CCommandState		m_PrevCommandState;		// Previous command state
	KeyState			m_KeyState;				// Frame keyboard state
	XINPUT_STATE		m_GamepadState;			// Frame gamepad state
	CInput*				m_Input;				// Input instance
	int					m_Command;				// The next command to be added to the buffer
	int					m_PrevCommand;			// The most recent command added to the buffer
	unsigned int		m_XboxGamepadPort;		// Port of the gamepad to read input from
	float				m_Time;					// Time until command needs to be added to the buffer
	bool				m_CheckMoves;			// Indicates whether move maps should be examined after update
	bool				m_UsingGamepad;			// True if a gamepad should be checked for input rather than the keyboard 

	// Checks keys to see if a command has been activated
	bool CheckKeys(int command);

	// Checks gamepad to see if a command has been activated
	bool CheckGamepad(int command);

public:
	// Constructor
	CECInputManager();

	// Destructor
	~CECInputManager();

	// Accessors
	inline const CommandList* const GetCommands() const { return &m_Commands; }

	// Add command input
	inline void AddCommandInput(int command, int input){ m_CommandInputs[command].push_back(input); }

	// Set command input list
	inline void SetCommandInput(int command, std::vector<int>& inputs){ m_CommandInputs[command] = inputs; }

	// Set command input
	inline void SetCommandInput(int command, int input)
	{ 
		m_CommandInputs[command].clear();
		m_CommandInputs[command].push_back(input);
	}

	// Clear command input
	inline void ClearCommandInput(int command){ m_CommandInputs[command].clear(); }

	// Clear command input map
	inline void ClearCommandInputs(){ m_CommandInputs.clear(); }

	// Set gamepad usage
	void SetGamepad(bool use, unsigned int portNum);

	// Retrieve the gamepad associated with this manager
	CGamepad* GetGamepad();

	// Retrieves user input and updates command buffer
	void Update(float dt);

	// Checks if a move from a move map has been activated
	// Returns true if a move has been activated
	bool CheckMoves(CMove* move, CMoveMap& moves);

	// Check to see if a command has been activated
	bool CheckCommand(int command);

	// Checks the command buffer to see if a move has been activated
	// Returns true if the move has been activated
	bool CheckMove(CMove& move);
};