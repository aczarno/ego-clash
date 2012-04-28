/////////////////////////////////////////////////////////////////
//    File: MoveReader.h
//  Author: Chris Blasko
// Updated: 2/28/2012
/////////////////////////////////////////////////////////////////
#pragma once

#include "Move.h"


class CMoveReader
{
private:
	// Class state
	static const int	s_BufferSize = 256;
	static const char*	s_TagMove;
	static const char*	s_TagName;
	static const char*	s_PropName;
	static const char*	s_PropPriority;
	static const char*	s_PropTolerance;
	static const char*	s_PropCommand;
	static const char*	s_DefUnknown;
	static const char*	s_DefLPunch;
	static const char*	s_DefMPunch;
	static const char*	s_DefSPunch;
	static const char*	s_DefPunch;
	static const char*	s_DefLKick;
	static const char*	s_DefMKick;
	static const char*	s_DefSKick;
	static const char*	s_DefKick;
	static const char*	s_DefUp;
	static const char*	s_DefDown;
	static const char*	s_DefBack;
	static const char*	s_DefForward;
	static const char*	s_DefUpForward;
	static const char*	s_DefUpBack;
	static const char*	s_DefDownForward;
	static const char*	s_DefDownBack;
	static const char*	s_DefInactive;
	static const char*	s_DefPressed;
	static const char*	s_DefHeld;
	static const char*	s_DefReleased;
	static const char*	s_DefPressedOrHeld;
	static const char*	s_DefPressedOrReleased;
	static const char*	s_DefTrue;
	static const char*	s_DefFalse;
	static const char*	s_DefOne;
	static const char*	s_DefZero;

	// Instance state
	CMoveMap			m_Moves;
	std::string			m_Name;
	char				m_Buffer[s_BufferSize];

	// Read a move tag
	bool ReadMoveTag(FILE* file, CMove& move);

	// Read a commands property
	bool ReadCommandProp(std::string& valueStr, CMove::Command& command);

public:
	// Constructor
	CMoveReader(){};
	CMoveReader(const char* filename){ Read(filename); }

	// Destructor
	~CMoveReader(){};

	// Accessors
	inline CMoveMap* const GetMoves() { return &m_Moves; }
	inline const char* GetName() const { return m_Name.c_str(); }

	// Loads a move list file and parses it
	bool Read(const char* filename);
};