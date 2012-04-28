/////////////////////////////////////////////////////////////////
//    File: CommandState.h
//  Author: Chris Blasko
// Updated: 2/28/2012
/////////////////////////////////////////////////////////////////
#pragma once

#include <map>


// Command state
class CCommandState
{
private:
	// Instance state
	std::map<int, float>	m_HoldTimes;					// Amount of time commands have been held down
	float					m_Age;							// Time since command activation
	int						m_Pressed, m_Held, m_Released;	// Active command states

public:
	// Constructor
	CCommandState();
	CCommandState(CCommandState& prevState, int command, float time);

	// Destructor
	~CCommandState(){};

	// Initializes command state
	void Init(CCommandState& prevState, int command, float time);

	// Accessors
	inline float GetAge() const { return m_Age; }
	inline int GetPressed() const { return m_Pressed; }
	inline int GetHeld() const { return m_Held; }
	inline int GetReleased() const { return m_Released; }
	inline bool IsEmpty() const { return !(m_Released || m_Pressed || m_Held); }

	// Add age to the state
	inline void AddAge(float dt){ m_Age += dt; }

	// Get the hold time of a specified command
	float GetHoldTime(int command);
};