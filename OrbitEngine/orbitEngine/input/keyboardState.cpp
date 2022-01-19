// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Keyboard State Container Class Implementation
// ===========================================================================

// import necessary specification
#include "keyboardState.h"


// ===========================================================================
// default constructor
// ===========================================================================
KeyboardState::KeyboardState():

	// members
	keysDown	(),
	keysPressed	(),
	textBuffer	(MAX_TEXT_BUFFER_SIZE),
	charBuffer	('\0'),
	isNewline	(false)
{
	// initialize key state arrays
	for (size_t i = 0; i < KEYS_ARRAY_LEN; i++)
	{
		keysDown[i] = keysPressed[i] = false;
	}
}


// setters

// ===========================================================================
// updates the relevant key-states for the virtual key on keydown
// ===========================================================================
void KeyboardState::notifyKeyDown(
	const UCHAR&	vkey
) {
	// ensure virtual key code is within key state array range
	if (vkey >= KEYS_ARRAY_LEN) return;

	// update both keyDown and keyPressed to true
	keysDown	[vkey] = true;
	keysPressed	[vkey] = true;
}

// ===========================================================================
// updates the relevant key-states for the virtual key on keyup
// ===========================================================================
void KeyboardState::notifyKeyUp(
	const UCHAR&	vkey
) {
	// ensure virtual key code is within key state array range
	if (vkey < KEYS_ARRAY_LEN)
	{
		// update keyDown to false (keyPressed is cleared at end of frame)
		keysDown[vkey] = false;
	}
}

// ===========================================================================
// saves the character entered by the user into the text buffer
// ===========================================================================
void KeyboardState::notifyTextIn(
	const UCHAR&	vkey
) {
	// handle start of newline
	if (isNewline) {

		// clear textIn and remove newline status
		textBuffer.clear();
		isNewline = false;
	}

	// handle backspace
	if (static_cast<char>(vkey) == '\b') {

		// if characters exist, erase last character entered
		if (textBuffer.length() > 0) textBuffer.popBack();
	}

	// handle all other characters
	else {

		// add character to textIn
		textBuffer += vkey;

		// save last character entered to charIn
		charBuffer = vkey;
	}

	// handle return by starting newline
	if (static_cast<char>(vkey) == '\r') isNewline = true;
}

// ===========================================================================
// clears the buffers for the input types whose bit flags are passed into
// this method. multiple states can be reset at once by using multiple
// bit flags at once through applying the bitwise-or operator to each flag
// ===========================================================================
void KeyboardState::clear(
	UCHAR	bufferFlags
) {
	// clear keydown buffer if specified
	if (bufferFlags & KeyboardBuffers::KEYS_DOWN) {
		for (size_t i = 0; i < KEYS_ARRAY_LEN; i++)
			keysDown[i] = false;
	}

	// clear keypressed buffer if specified
	if (bufferFlags & KeyboardBuffers::KEYS_PRESSED) {
		for (size_t i = 0; i < KEYS_ARRAY_LEN; i++)
			keysPressed[i] = false;
	}

	// clear textIn input buffer if specified
	if (bufferFlags & KeyboardBuffers::TEXT_IN) textBuffer.clear();
}

// ===========================================================================
// clears the specified key press
// ===========================================================================
void KeyboardState::clearKeyPressed(
	const UCHAR&	vkey
) {
	// ensure vkey is within buffer range and update states accordingly
	if (vkey < KEYS_ARRAY_LEN) keysPressed[vkey] = false;
}


// getters

// ===========================================================================
// checks if the specified key is currently being held down by the user
// ===========================================================================
bool KeyboardState::isKeyDown(
	const UCHAR&	vkey
) const {
	// if vkey is inside buffer range, return key status, else false
	return vkey < KEYS_ARRAY_LEN ? keysDown[vkey] : false;
}

// ===========================================================================
// checks if the specified key was pressed in the current frame
// ===========================================================================
bool KeyboardState::wasKeyPressed(
	const UCHAR& vkey
) const {
	// if vkey is inside buffer range, return key status, else false
	return vkey < KEYS_ARRAY_LEN ? keysPressed[vkey] : false;
}

// ===========================================================================
// checks if any keys were pressed in the current frame
// ===========================================================================
bool KeyboardState::anyKeyPressed() const
{
	// scan through the relevant buffer for a pressed key
	for (size_t i = 0; i < KEYS_ARRAY_LEN; i++)

		// if a key was pressed, return true
		if (keysPressed[i] == true) return true;

	// else return false
	return false;
}
