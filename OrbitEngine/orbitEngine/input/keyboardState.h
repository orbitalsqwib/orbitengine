// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Keyboard State Container Class Specification
// ===========================================================================

#ifndef _ORBIT_INPUT_KEYBOARDSTATE_H
#define _ORBIT_INPUT_KEYBOARDSTATE_H

// import windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "../utils/textQueue.h"
#include <limits.h>
#include <string>

// related constructs

// limit constants
namespace
{
	// key array size
	const int KEYS_ARRAY_LEN = UCHAR_MAX;

	// max text input buffer size
	const int MAX_TEXT_BUFFER_SIZE = UCHAR_MAX; // 256 characters
}

// specifies bit flags for each keyboard state buffer
namespace KeyboardBuffers
{
	const UCHAR KEYS_DOWN		= 0b001;
	const UCHAR KEYS_PRESSED	= 0b010;
	const UCHAR TEXT_IN			= 0b100;
	const UCHAR ALL_INPUT		= 0b111;
}


// main definition

// keyboard state container
class KeyboardState
{
private:

	// members

	// specifies the keys that are currently being held down by the user
	bool keysDown[KEYS_ARRAY_LEN];

	// specifies the keys that were pressed in the current frame. resets at
	// the end of each frame.
	bool keysPressed[KEYS_ARRAY_LEN];

	// text input buffer - records the previous MAX_INPUT_BUFFER_SIZE chars
	TextQueue textBuffer;

	// stores the last character pressed by the user
	char charBuffer;

	// indicates if it is currently the start of a new line
	bool isNewline;

public:

	// default constructor
	KeyboardState();


	// setters

	// updates the relevant key-states for the virtual key on keydown
	void notifyKeyDown(const UCHAR& vkey);

	// updates the relevant key-states for the virtual key on keyup
	void notifyKeyUp(const UCHAR& vkey);

	// saves the character entered by the user into the text buffer
	void notifyTextIn(const UCHAR& vkey);

	// clears the buffers for the input types whose bit flags are passed into
	// this method. multiple states can be reset at once by using multiple
	// bit flags at once through applying the bitwise-or operator to each flag
	void clear(UCHAR bufferFlags);


	// convenience setters

	// clears the text input buffer
	void clearText() { textBuffer.clear(); }

	// clears the specified key press
	void clearKeyPressed(const UCHAR& vkey);

	// clears the keys pressed buffer
	void clearKeyPresses() { clear(KeyboardBuffers::KEYS_PRESSED); }

	// clears all input buffers
	void clearAll() { clear(KeyboardBuffers::ALL_INPUT); }


	// getters

	// checks if the specified key is currently being held down by the user
	bool isKeyDown(const UCHAR& vkey) const;

	// checks if the specified key was pressed in the current frame
	bool wasKeyPressed(const UCHAR& vkey) const;

	// checks if any keys were pressed in the current frame
	bool anyKeyPressed() const;

	// retrieves the value of the text input buffer
	std::string getTextBuffer() { return textBuffer.getString(); }

	// retrieves the most recently entered character
	char getCharBuffer() { return charBuffer; }

};

#endif // !_ORBIT_INPUT_KEYBOARDSTATE_H