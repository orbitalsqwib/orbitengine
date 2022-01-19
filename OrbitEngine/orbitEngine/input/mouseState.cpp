// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Mouse State Container Class Implementation
// ===========================================================================

// import necessary specification
#include "mouseState.h"

// ===========================================================================
// default constructor
// ===========================================================================
MouseState::MouseState(
	const bool&	captureMouse
) :
	// general mice members
	pos				({0, 0}),
	isMouseCaptured	(captureMouse),
	LBtn			(false),
	MBtn			(false),
	RBtn			(false),
	X1Btn			(false),
	X2Btn			(false),

	// high-definition mice members
	rawX			(0),
	rawY			(0)
{}


// setters

// ===========================================================================
// updates the mouse position state
// ===========================================================================
void MouseState::notifyPosChanged(
	const LPARAM&	lParam
) {
	pos.x = GET_X_LPARAM(lParam);
	pos.y = GET_Y_LPARAM(lParam);
}

// ===========================================================================
// reads raw mouse input from lParam into mouseRawX, mouseRawY - this
// routine provides compatibility for high-definition mouse devices
// ===========================================================================
void MouseState::notifyRawChanged(
	const LPARAM&	lParam
) {
	// initialise RAWINPUT struct and required data for processing
	RAWINPUT rawInput;
	UINT rawInputSize = sizeof(rawInput);
	ZeroMemory(&rawInput, rawInputSize);

	// retrieve raw input data to the RAWINPUT struct
	GetRawInputData(
		(HRAWINPUT)lParam,	// the handle to the RAWINPUT struct from lParam
		RID_INPUT,			// specifies raw input as the data to be retrieved
		&rawInput,			// pointer to the RAWINPUT struct
		&rawInputSize,
		sizeof(RAWINPUTHEADER)
	);

	// update raw mouse data states
	if (rawInput.header.dwSize == RIM_TYPEMOUSE) {
		rawX = rawInput.data.mouse.lLastX;
		rawY = rawInput.data.mouse.lLastY;
	}
}