#include "MoveReader.h"
#include "Commands.h"
#include <stdio.h>
#include <string>


const char*	CMoveReader::s_TagMove					= "[MOVE]";
const char*	CMoveReader::s_TagName					= "[NAME]";
const char*	CMoveReader::s_PropName					= "Name";
const char*	CMoveReader::s_PropPriority				= "Priority";
const char*	CMoveReader::s_PropTolerance			= "Tolerance";
const char*	CMoveReader::s_PropCommand				= "Command";
const char*	CMoveReader::s_DefUnknown				= "Unknown";
const char*	CMoveReader::s_DefLPunch				= "LPunch";
const char*	CMoveReader::s_DefMPunch				= "MPunch";
const char*	CMoveReader::s_DefSPunch				= "SPunch";
const char*	CMoveReader::s_DefPunch					= "Punch";
const char*	CMoveReader::s_DefLKick					= "LKick";
const char*	CMoveReader::s_DefMKick					= "MKick";
const char*	CMoveReader::s_DefSKick					= "SKick";
const char*	CMoveReader::s_DefKick					= "Kick";
const char*	CMoveReader::s_DefUp					= "Up";
const char*	CMoveReader::s_DefDown					= "Down";
const char*	CMoveReader::s_DefBack					= "Back";
const char*	CMoveReader::s_DefForward				= "Forward";
const char*	CMoveReader::s_DefUpForward				= "UpForward";
const char*	CMoveReader::s_DefUpBack				= "UpBack";
const char*	CMoveReader::s_DefDownForward			= "DownForward";
const char*	CMoveReader::s_DefDownBack				= "DownBack";
const char*	CMoveReader::s_DefInactive				= "Inactive";
const char*	CMoveReader::s_DefPressed				= "Pressed";
const char*	CMoveReader::s_DefHeld					= "Held";
const char*	CMoveReader::s_DefReleased				= "Released";
const char*	CMoveReader::s_DefPressedOrHeld			= "PressedOrHeld";
const char*	CMoveReader::s_DefPressedOrReleased		= "PressedOrReleased";
const char*	CMoveReader::s_DefTrue					= "True";
const char*	CMoveReader::s_DefFalse					= "False";
const char*	CMoveReader::s_DefOne					= "1";
const char*	CMoveReader::s_DefZero					= "0";



bool CMoveReader::ReadMoveTag(FILE* file, CMove& move)
{
	bool Res = true;

	bool Continue = true;
	while(Continue == true)
	{
		if(fgets(m_Buffer, s_BufferSize, file) != NULL)
		{
			std::string LineStr = m_Buffer;
			size_t Pos = LineStr.find('=');
			if(Pos != std::string::npos)
			{
				std::string PropertyStr = LineStr;
				std::string ValueStr = LineStr;
				PropertyStr.erase(Pos);
				ValueStr.erase(0, Pos+1);

				if(PropertyStr == s_PropName)
					move.Name = ValueStr;
				else if(PropertyStr == s_PropPriority)
					move.Priority = atoi(ValueStr.c_str());
				else if(PropertyStr == s_PropTolerance)
					move.Tolerance = (float)atof(ValueStr.c_str());
				else if(PropertyStr == s_PropCommand)
				{
					CMove::Command NewCommand;
					if(ReadCommandProp(ValueStr, NewCommand) == true)
						move.Commands.push_back(NewCommand);
				}
				else
					Continue = false;
			}
			else
				Continue = false;
		}
		else
			Continue = false;
	}

	return Res;
}


bool CMoveReader::ReadCommandProp(std::string& valueStr, CMove::Command& command)
{
	bool Res = true;

	std::string CommandStr, StateStr, MatchStr, CheckPrevStr, HoldTimeStr;

	size_t Begin = valueStr.find('{');
	if(Begin != std::string::npos)
	{
		size_t End = valueStr.find('}', Begin);
		if(End != std::string::npos)
		{
			size_t Pos = Begin;

			bool GoGoGo = true;
			for(int i = 0; GoGoGo == true && Pos < End; ++i)
			{
				size_t Sep = valueStr.find(',', Pos);
				if(Sep == std::string::npos)
					Sep = End;

				if(Sep != std::string::npos)
				{
					std::string AttrStr = valueStr.substr(Pos+1, Sep-Pos-1);

					switch(i)
					{
					case 0:
						CommandStr = AttrStr.c_str();
						break;

					case 1:
						StateStr = AttrStr.c_str();
						break;

					case 2:
						MatchStr = AttrStr.c_str();
						break;

					case 3:
						CheckPrevStr = AttrStr.c_str();
						break;

					case 4:
						HoldTimeStr = AttrStr.c_str();
						break;

					default:
						break;
					}

					Pos = Sep+1;
				}
				else
					GoGoGo = false;
			}
		}
	}

	// Update command properties

	// Parse command string
	size_t Pos = CommandStr.find('+'); 
	if(Pos == std::string::npos)
	{
		if		(CommandStr == s_DefUnknown)		command.Commands = COMMAND_UNKNOWN;
		else if	(CommandStr == s_DefLPunch)			command.Commands = COMMAND_PUNCHA;
		else if	(CommandStr == s_DefMPunch)			command.Commands = COMMAND_PUNCHB;
		else if	(CommandStr == s_DefSPunch)			command.Commands = COMMAND_PUNCHC;
		else if	(CommandStr == s_DefPunch)			command.Commands = COMMAND_PUNCH;
		else if	(CommandStr == s_DefLKick)			command.Commands = COMMAND_KICKA;
		else if	(CommandStr == s_DefMKick)			command.Commands = COMMAND_KICKB;
		else if	(CommandStr == s_DefSKick)			command.Commands = COMMAND_KICKC;
		else if	(CommandStr == s_DefKick)			command.Commands = COMMAND_KICK;
		else if	(CommandStr == s_DefUp)				command.Commands = COMMAND_UP;
		else if	(CommandStr == s_DefDown)			command.Commands = COMMAND_DOWN;
		else if	(CommandStr == s_DefBack)			command.Commands = COMMAND_BACK;
		else if	(CommandStr == s_DefForward)		command.Commands = COMMAND_FORWARD;
		else if	(CommandStr == s_DefUpForward)		command.Commands = COMMAND_UPFORWARD;
		else if	(CommandStr == s_DefUpBack)			command.Commands = COMMAND_UPBACK;
		else if	(CommandStr == s_DefDownForward)	command.Commands = COMMAND_DOWNFORWARD;
		else if	(CommandStr == s_DefDownBack)		command.Commands = COMMAND_DOWNBACK;
	}
	else
	{
		command.Commands = COMMAND_UNKNOWN;

		std::string CopyCommandStr = CommandStr;
		while(CopyCommandStr.empty() == false)
		{
			std::string NextCommandStr = CopyCommandStr.substr(0, Pos);
			CopyCommandStr.erase(0, Pos+1);

			if		(NextCommandStr == s_DefUnknown)		command.Commands |= COMMAND_UNKNOWN;
			else if	(NextCommandStr == s_DefLPunch)			command.Commands |= COMMAND_PUNCHA;
			else if	(NextCommandStr == s_DefMPunch)			command.Commands |= COMMAND_PUNCHB;
			else if	(NextCommandStr == s_DefSPunch)			command.Commands |= COMMAND_PUNCHC;
			else if	(NextCommandStr == s_DefPunch)			command.Commands |= COMMAND_PUNCH;
			else if	(NextCommandStr == s_DefLKick)			command.Commands |= COMMAND_KICKA;
			else if	(NextCommandStr == s_DefMKick)			command.Commands |= COMMAND_KICKB;
			else if	(NextCommandStr == s_DefSKick)			command.Commands |= COMMAND_KICKC;
			else if	(NextCommandStr == s_DefKick)			command.Commands |= COMMAND_KICK;
			else if	(NextCommandStr == s_DefUp)				command.Commands |= COMMAND_UP;
			else if	(NextCommandStr == s_DefDown)			command.Commands |= COMMAND_DOWN;
			else if	(NextCommandStr == s_DefBack)			command.Commands |= COMMAND_BACK;
			else if	(NextCommandStr == s_DefForward)		command.Commands |= COMMAND_FORWARD;
			else if	(NextCommandStr == s_DefUpForward)		command.Commands |= COMMAND_UPFORWARD;
			else if	(NextCommandStr == s_DefUpBack)			command.Commands |= COMMAND_UPBACK;
			else if	(NextCommandStr == s_DefDownForward)	command.Commands |= COMMAND_DOWNFORWARD;
			else if	(NextCommandStr == s_DefDownBack)		command.Commands |= COMMAND_DOWNBACK;

			size_t Pos = CopyCommandStr.find('+');
		}
	}

	if		(StateStr == s_DefInactive)				command.State = COMMAND_STATE_INACTIVE;
	else if	(StateStr == s_DefPressed)				command.State = COMMAND_STATE_PRESSED;
	else if	(StateStr == s_DefHeld)					command.State = COMMAND_STATE_HELD;
	else if	(StateStr == s_DefReleased)				command.State = COMMAND_STATE_RELEASED;
	else if	(StateStr == s_DefPressedOrHeld)		command.State = COMMAND_STATE_PRESSED_OR_HELD;
	else if	(StateStr == s_DefPressedOrReleased)	command.State = COMMAND_STATE_PRESSED_OR_RELEASED;

	if		(MatchStr == s_DefTrue)				command.Match = true;
	else if	(MatchStr == s_DefOne)				command.Match = true;
	else if	(MatchStr == s_DefFalse)			command.Match = false;
	else if	(MatchStr == s_DefZero)				command.Match = false;

	if		(CheckPrevStr == s_DefTrue)			command.CheckPrev = true;
	else if	(CheckPrevStr == s_DefOne)			command.CheckPrev = true;
	else if	(CheckPrevStr == s_DefFalse)		command.CheckPrev = false;
	else if	(CheckPrevStr == s_DefZero)			command.CheckPrev = false;

	command.HoldTime = (float)atof(HoldTimeStr.c_str());

	return Res;
}


bool CMoveReader::Read(const char* filename)
{
	bool Res = false;

	m_Name.clear();
	m_Moves.Clear();

	FILE* File;
	fopen_s(&File, filename, "r");
	if (File != NULL)
	{
		bool Continue = true;
		while (Continue && feof(File) == false)
		{
			if(fgets(m_Buffer, s_BufferSize, File) != NULL)
			{
				std::string BufferStr = m_Buffer;
				BufferStr.erase(BufferStr.size()-1);

				if(BufferStr.compare(s_TagMove) == 0)
				{
					CMove NewMove;
					if(ReadMoveTag(File, NewMove) == true)
						m_Moves.SetMove(NewMove);
				}
				else if(BufferStr.compare(s_TagName) == 0)
				{
					if(fgets(m_Buffer, s_BufferSize, File) != NULL)
						m_Name = m_Buffer;
				}
			}
			else
				Continue = false;
		}

		fclose(File);
		Res = true;
	}

	return Res;
}
