/////////////////////////////////////////////////////////////////
//    File: Commands.h
//  Author: Chris Blasko
// Updated: 2/28/2012
/////////////////////////////////////////////////////////////////
#pragma once


// Button commands can be modified without needing to update ECInputManager
#define COMMAND_UNKNOWN			0x00000000
#define COMMAND_PUNCHA			0x00000001
#define COMMAND_PUNCHB			0x00000002
#define COMMAND_PUNCHC			0x00000004
#define COMMAND_KICKA			0x00000008
#define COMMAND_KICKB			0x00000010
#define COMMAND_KICKC			0x00000020
#define COMMAND_PUNCH			(COMMAND_PUNCHA | COMMAND_PUNCHB | COMMAND_PUNCHC)
#define COMMAND_KICK			(COMMAND_KICKA | COMMAND_KICKB | COMMAND_KICKC)

// Button command iteration
#define BUTTON_COMMAND_BEGIN		COMMAND_PUNCHA
#define BUTTON_COMMAND_END			COMMAND_KICKC
#define FOR_EACH_BUTTON_COMMAND(i)	for(int i = BUTTON_COMMAND_BEGIN; i <= BUTTON_COMMAND_END; i <<= 1)

// Directional commands; if definitions are added or removed, 
// ECInputManager will need to be updated to reflect changes
#define COMMAND_BACK			0x00000040
#define COMMAND_FORWARD			0x00000080
#define COMMAND_UP				0x00000100
#define COMMAND_DOWN			0x00000200
#define COMMAND_UPBACK			0x00000400
#define COMMAND_UPFORWARD		0x00000800
#define COMMAND_DOWNBACK		0x00001000
#define COMMAND_DOWNFORWARD		0x00002000

// Command iteration macros
#define COMMAND_BEGIN			COMMAND_PUNCHA
#define COMMAND_END				COMMAND_DOWNFORWARD
#define FOR_EACH_COMMAND(i)		for(int i = COMMAND_BEGIN; i <= COMMAND_END; i <<= 1)
#define COMMAND_COUNT			14

// Command states; if changed, ECInputManager will need to be updated to reflect changes
#define COMMAND_STATE_INACTIVE				0
#define COMMAND_STATE_PRESSED				1
#define COMMAND_STATE_HELD					2
#define COMMAND_STATE_RELEASED				3
#define COMMAND_STATE_PRESSED_OR_HELD		4
#define COMMAND_STATE_PRESSED_OR_RELEASED	5