// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Gamepad Handler Class Specification
// ===========================================================================

#ifndef _ORBIT_INPUT_GAMEPADHANDLER_H
#define _ORBIT_INPUT_GAMEPADHANDLER_H

// import windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// include xinput header and libs
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")

// related constructs

// general constants
namespace
{
	// thumbstick deadzone - default 20%
	const DWORD GAMEPAD_THUMBSTICK_DEADZONE = (DWORD)(0.20f * 0x7FFF);

	// trigger deadzone - default 30/255
	const DWORD GAMEPAD_TRIGGER_DEADZONE = 30;

	// maximum controllers allowed
	const DWORD	MAX_GAMEPADS = 4;
}

// gamepad button bit flags (according to state.Gamepad.wButtons)
namespace GamepadButtons
{
	const DWORD DPAD_UP			= 0x0001;
	const DWORD DPAD_DOWN		= 0x0002;
	const DWORD DPAD_LEFT		= 0x0004;
	const DWORD DPAD_RIGHT		= 0x0008;
	const DWORD START_BUTTON	= 0x0010;
	const DWORD BACK_BUTTON		= 0x0020;
	const DWORD LEFT_THUMB		= 0x0040;
	const DWORD RIGHT_THUMB		= 0x0080;
	const DWORD LEFT_SHOULDER	= 0x0100;
	const DWORD RIGHT_SHOULDER	= 0x0200;
	const DWORD A				= 0x1000;
	const DWORD B				= 0x2000;
	const DWORD X				= 0x4000;
	const DWORD Y				= 0x8000;
}

// controller input buffer
struct GamepadInputBuffer
{
	XINPUT_STATE		state;
	XINPUT_VIBRATION	vibration;
	float				vibrateTimeLeft;
	float				vibrateTimeRight;
	bool				connected;
};


// main definition

// gamepad handler object, responsible for managing gamepads, storing gamepad
// states and updating them in real-time.
class GamepadHandler
{
private:

	// members

	// controller states
	GamepadInputBuffer gamepads[MAX_GAMEPADS];


	// private convenience methods

	// sanitizes incoming indexes such that n: 0 <= n < MAX_GAMEPADS, n E I
	int sanitizeIndex(int n)
	{ return n >= 0 ? n < MAX_GAMEPADS ? n : MAX_GAMEPADS - 1 : 0; }
	
public:

	// constructor
	GamepadHandler();


	// methods

	// resets the input buffers and states of all gamepads, and also attempts
	// to refresh the connection state of each gamepad
	void resetAllGamepads();

	// updates the connection status for all gamepads
	void refreshConnections();

	// updates the input buffers of all connected gamepads
	void updateInputs();

	// updates the behaviour of connected gamepads with respect to the game's
	// internal timer. should be called within the main update loop.
	void updateGamepads(const float& frameTime);


	// setters

	// configures a gamepad to vibrate its left (low frequency) motor for a
	// specific number of seconds at a specific motor speed
	void gamepadVibrateLeft(const UINT& n, WORD speed, float sec)
	{
		gamepads[sanitizeIndex(n)].vibration.wLeftMotorSpeed = speed;
		gamepads[sanitizeIndex(n)].vibrateTimeLeft = sec;
	}

	// configures a gamepad to vibrate its right (high frequency) motor for a
	// specific number of seconds at a specific motor speed
	void gamepadVibrateRight(const UINT& n, WORD speed, float sec)
	{
		gamepads[sanitizeIndex(n)].vibration.wRightMotorSpeed = speed;
		gamepads[sanitizeIndex(n)].vibrateTimeRight = sec;
	}


	// getters

	// returns a reference to the input buffer for the specified gamepad
	const GamepadInputBuffer& getGamepad(const UINT& n)
	{
		return gamepads[sanitizeIndex(n)];
	}

	// returns the button states for the specified game gamepad
	const WORD getGamepadBtns(const UINT& n) {
		return getGamepad(n).state.Gamepad.wButtons;
	}

	// returns the d-pad up button state for the specified gamepad
	bool getGamepadDPadUp(const UINT& n) {
		return (getGamepadBtns(n) & GamepadButtons::DPAD_UP) != 0;
	}

	// returns the d-pad down button state for the specified gamepad
	bool getGamepadDPadDown(const UINT& n) {
		return (getGamepadBtns(n) & GamepadButtons::DPAD_DOWN) != 0;
	}

	// returns the d-pad left button state for the specified gamepad
	bool getGamepadDPadLeft(const UINT& n) {
		return (getGamepadBtns(n) & GamepadButtons::DPAD_LEFT) != 0;
	}

	// returns the d-pad right button state for the specified gamepad
	bool getGamepadDPadRight(const UINT& n) {
		return (getGamepadBtns(n) & GamepadButtons::DPAD_RIGHT) != 0;
	}

	// returns the start button state for the specified gamepad
	bool getGamepadStart(const UINT& n) {
		return (getGamepadBtns(n) & GamepadButtons::START_BUTTON) != 0;
	}

	// returns the back button state for the specified gamepad
	bool getGamepadBack(const UINT& n) {
		return (getGamepadBtns(n) & GamepadButtons::BACK_BUTTON) != 0;
	}

	// returns the left thumb button state for the specified gamepad
	bool getGamepadLeftThumb(const UINT& n) {
		return (getGamepadBtns(n) & GamepadButtons::LEFT_THUMB) != 0;
	}

	// returns the right thumb button state for the specified gamepad
	bool getGamepadRightThumb(const UINT& n) {
		return (getGamepadBtns(n) & GamepadButtons::RIGHT_THUMB) != 0;
	}

	// returns the left shoulder button state for the specified gamepad
	bool getGamepadLeftShoulder(const UINT& n) {
		return (getGamepadBtns(n) & GamepadButtons::LEFT_SHOULDER) != 0;
	}

	// returns the right shoulder button state for the specified gamepad
	bool getGamepadRightShoulder(const UINT& n) {
		return (getGamepadBtns(n) & GamepadButtons::RIGHT_SHOULDER) != 0;
	}

	// returns the "A" button state for the specified gamepad
	bool getGamepadA(const UINT& n) {
		return (getGamepadBtns(n) & GamepadButtons::A) != 0;
	}

	// returns the "B" button state for the specified gamepad
	bool getGamepadB(const UINT& n) {
		return (getGamepadBtns(n) & GamepadButtons::B) != 0;
	}

	// returns the "X" button state for the specified gamepad
	bool getGamepadX(const UINT& n) {
		return (getGamepadBtns(n) & GamepadButtons::X) != 0;
	}

	// returns the "Y" button state for the specified gamepad
	bool getGamepadY(const UINT& n) {
		return (getGamepadBtns(n) & GamepadButtons::Y) != 0;
	}

	// returns the left trigger state for the specified gamepad
	BYTE getGamepadLeftTrigger(const UINT& n) {
		return getGamepad(n).state.Gamepad.bLeftTrigger;
	}

	// returns the right trigger state for the specified gamepad
	BYTE getGamepadRightTrigger(const UINT& n) {
		return getGamepad(n).state.Gamepad.bRightTrigger;
	}

	// returns the left thumbstick's x-value for the specified gamepad
	SHORT getGamepadThumbLX(const UINT& n) {
		return getGamepad(n).state.Gamepad.sThumbLX;
	}

	// returns the left thumbstick' y-value for the specified gamepad
	SHORT getGamepadThumbLY(const UINT& n) {
		return getGamepad(n).state.Gamepad.sThumbLY;
	}

	// returns the right thumbstick's x-value for the specified gamepad
	SHORT getGamepadThumbRX(const UINT& n) {
		return getGamepad(n).state.Gamepad.sThumbRX;
	}

	// returns the right thumbstick's y-value for the specified gamepad
	SHORT getGamepadThumbRY(const UINT& n) {
		return getGamepad(n).state.Gamepad.sThumbRY;
	}

};

#endif // !_ORBIT_INPUT_GAMEPADHANDLER_H