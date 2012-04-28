/////////////////////////////////////////////////////////////////
//    File: Move.h
//  Author: Chris Blasko
// Updated: 2/28/2012
/////////////////////////////////////////////////////////////////
#pragma once

#include "Commands.h"
#include <string>
#include <vector>
#include <map>


class CMove
{
public:
	// Move command structure
	struct Command
	{
		// Instance state
		float	HoldTime;		// If state is COMMAND_STATE_HOLD, this signifies the amount of time the 
								// command must be active for the action to be valid
		int		Commands;		// Commands that need to be active for the action to be valid
		int		State;			// State that the commands must be in for the action to be valid
		bool	Match;			// If true, every command must be activated for the action to be valid; 
								// if false, any of the commands can be active for the action to be valid 
		bool	CheckPrev;		// If true, indicates that the input for the previous action should also be 
								// used to check if this action is valid; if false, previous input is ignored

		Command(int commands = COMMAND_UNKNOWN, int state = COMMAND_STATE_PRESSED, bool match = true, 
				bool checkPrev = false, float holdTime = 0.0f) : 
			Commands(commands), 
			State(state), 
			Match(match), 
			HoldTime(holdTime),
			CheckPrev(checkPrev)
		{
		};
	};

	// Types
	typedef std::vector<Command>		CommandSequence;

	// Instance state
	std::string			Name;			// Move identification string
	CommandSequence		Commands;		// Sequence of command criteria which must be met to activate move
	float				Tolerance;		// Time frame the command sequence must be entered in to activate move
	int					Priority;		// Determines the order in which moves are checked for activation by input manager
	int					ValidStates;	// Valid states that the fighter can be in to activate this move
	int					EndState;		// State the fighter returns to when the move has ended
	int					HurtReaction;	// Reaction for this attack (0 = Light, 1 = Medium, 2 = Heavy)
	bool				KnocksDown;		// True if this move knocks down its target
	bool				StandsUp;		// True if this move puts a crouching target into the standing state on hit

	// Constructor
	CMove(){};
	CMove(const char* name, CommandSequence& commands, float tolerance, int priority) :
		Name(name),
		Commands(commands),
		Tolerance(tolerance),
		Priority(priority)
	{
	};

	// Destructor
	~CMove(){};
};


class CMoveMap
{
private:
	// Types
	typedef std::map<int, CMove>		MoveMap;

	// Instance state
	MoveMap				m_Moves;
	MoveMap::iterator	m_It;

public:
	// Constructor
	CMoveMap(){};

	// Destructor
	~CMoveMap(){};

	// Get a move using a key value
	inline CMove* const GetMove(int key)
	{ 
		if(m_Moves.count(key) != 0)
			return &m_Moves[key];
		return NULL;
	}

	// Set a move in the map
	inline void SetMove(CMove& move){ m_Moves[move.Priority] = move; }

	// Begin map iteration
	inline void Begin(){ m_It = m_Moves.begin(); }

	// Iterate map
	inline void Step(){ ++m_It; }

	// Check for end of map iteration
	inline bool End(){ return (m_It == m_Moves.end()); }

	// Get current move from iterator
	inline CMove* Curr() const { return &m_It->second; }

	// Clear the map
	inline void Clear(){ m_Moves.clear(); m_It = m_Moves.end(); }
};