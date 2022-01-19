// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Gamepad Handler Class Implementation
// ===========================================================================

// import specification
#include "gamepad.h"


// ===========================================================================
// constructor
// ===========================================================================
GamepadHandler::GamepadHandler(): gamepads()
{
	// initalize all gamepad states and input buffers and attempt to connect
	// controllers on handler creation
	resetAllGamepads();
}


// methods

// ===========================================================================
// resets the input buffers and states of all gamepads
// ===========================================================================
void GamepadHandler::resetAllGamepads()
{
	// initialize gamepad vibration states
	for (int i = 0; i < MAX_GAMEPADS; i++) {
		gamepadVibrateLeft(i, 0, 0);
		gamepadVibrateRight(i, 0, 0);

		// tell dx to stop vibrations
		XInputSetState(i, &gamepads[i].vibration);
	}

	// zero out controllers' states (possible since arr uses contiguous mem)
	ZeroMemory(gamepads, sizeof(GamepadInputBuffer) * MAX_GAMEPADS);

	// attempt to reconnect controllers
	refreshConnections();
}

// ===========================================================================
// updates the connection status for all gamepads
// ===========================================================================
void GamepadHandler::refreshConnections()
{
	// initialise temp result container
	DWORD result;

	// iterate through all supported gamepads
	for (DWORD i = 0; i < MAX_GAMEPADS; i++) {

		// attempt to retrieve state for gamepad i
		result = XInputGetState(i, &gamepads[i].state);

		// update connection state according to result
		if (result == ERROR_SUCCESS)	gamepads[i].connected = true;
		else							gamepads[i].connected = false;
	}
}

// ===========================================================================
// updates the input buffers of all connected gamepads
// ===========================================================================
void GamepadHandler::updateInputs()
{
	// initialise temp result container
	DWORD result;

	// iterate through all gamepads
	for (DWORD i = 0; i < MAX_GAMEPADS; i++) {

		// ensure gamepad is connected before polling state
		if (!gamepads[i].connected) return;

		// read and save result to state
		result = XInputGetState(i, &gamepads[i].state);

		// if gamepad is not connected
		if (result == ERROR_DEVICE_NOT_CONNECTED)

			// update state to reflect connection status
			gamepads[i].connected = false;
	}
}

// ===========================================================================
// updates the behaviour of connected gamepads with respect to the game's
// internal timer. should be called within the main update loop.
// ===========================================================================
void GamepadHandler::updateGamepads(
	const float&	frameTime
) {
	// iterate through all gamepads
	for (int i = 0; i < MAX_GAMEPADS; i++) {

		// ensure gamepads are connected before continuing
		if (!gamepads[i].connected) return;

		// decrement remaining vibration time
		gamepads[i].vibrateTimeLeft -= frameTime;
		gamepads[i].vibrateTimeRight -= frameTime;

		// if remaining time is below zero, reset vibration states
		if (gamepads[i].vibrateTimeLeft < 0) gamepadVibrateLeft(i, 0, 0);
		if (gamepads[i].vibrateTimeRight < 0) gamepadVibrateRight(i, 0, 0);

		// tell dx to update gamepad behaviours accordingly
		XInputSetState(i, &gamepads[i].vibration);
	}
}
