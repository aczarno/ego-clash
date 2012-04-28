#include "CommandState.h"
#include "Commands.h"



CCommandState::CCommandState() :
	m_Age(0.0f),
	m_Pressed(COMMAND_UNKNOWN),
	m_Held(COMMAND_UNKNOWN),
	m_Released(COMMAND_UNKNOWN)
{

}


CCommandState::CCommandState(CCommandState& prevState, int command, float time)
{
	Init(prevState, command, time);
}


void CCommandState::Init(CCommandState& prevState, int command, float time)
{
	int PrevDown = prevState.m_Pressed | prevState.m_Held;
	m_Pressed = command & (~PrevDown);
	m_Released = (~command) & PrevDown;
	m_Held = command & PrevDown;

	if(m_Held != COMMAND_UNKNOWN)
	{
		FOR_EACH_COMMAND(i)
		{
			if((i & m_Held) == i)
				m_HoldTimes[i] = prevState.m_HoldTimes[i] + time;
		}

		m_HoldTimes[m_Held] = prevState.m_HoldTimes[m_Held] + time;
	}

	m_Age = 0.0f;
}


float CCommandState::GetHoldTime(int command) 
{
	float Res = 0.0f;
	if(m_HoldTimes.count(command) == 1)
		Res = m_HoldTimes[command];
	return Res;
}