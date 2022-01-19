// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Mouse State Container Class Specification
// ===========================================================================

#ifndef _ORBIT_INPUT_MOUSESTATE_H
#define _ORBIT_INPUT_MOUSESTATE_H

// import windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include <windowsx.h>

// define macros for high-definition mouse devices
#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC	((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE ((USHORT) 0x02)
#endif


// main definition

// mouse state container
class MouseState
{
private:

	// general mice members

	// mouse screen coordinates (short int pair struct with x and y fields)
	POINTS pos;

	// specifies if the mouse is currently captured
	bool isMouseCaptured;

	// mouse button states
	bool LBtn, MBtn, RBtn, X1Btn, X2Btn;


	// high-definition mice members

	// captures raw input values for high-definition mice
	int rawX, rawY;

public:

	// default constructor
	MouseState(const bool& captureMouse = false);


	// setters

	// updates the mouse position state
	void notifyPosChanged(const LPARAM& lParam);

	// reads raw mouse input from lParam into mouseRawX, mouseRawY - this
	// routine provides compatibility for high-definition mouse devices
	void notifyRawChanged(const LPARAM& lParam);

	// updates the state of the left mouse button
	void notifyLBtnChanged(const bool& state) { LBtn = state; }

	// updates the state of the middle mouse button
	void notifyMBtnChanged(const bool& state) { MBtn = state; }

	// updates the state of the right mouse button
	void notifyRBtnChanged(const bool& state) { RBtn = state; }

	// updates the state of the extra mouse buttons
	void notifyXBtnChanged(const WPARAM& wParam)
	{
		X1Btn = (wParam & MK_XBUTTON1) ? true : false;
		X2Btn = (wParam & MK_XBUTTON2) ? true : false;
	}

	// updates the current capture state of the mouse
	void notifyMouseCapture(const bool& state)
	{
		isMouseCaptured = state;
	}


	// getters

	// returns the current x-position of the mouse
	int getX() const { return pos.x; }

	// returns the current y-position of the mouse
	int getY() const { return pos.y; }

	// returns the raw x-axis movement of the mouse. (<0 = left, >0 = right)
	// compatible with high-definition mouse devices.
	int getRawX() const { return rawX; }

	// returns the raw y-axis movement of the mouse. (<0 = down, >0 = up)
	// compatible with high-definition mouse devices.
	int getRawY() const { return rawY; }

	// returns the state of the left mouse button
	bool getLBtn() const { return LBtn; }

	// returns the state of the middle mouse button
	bool getMMBtn() const { return MBtn; }

	// returns the state of the right mouse button
	bool getRBtn() const { return RBtn; }

	// returns the state of extra mouse button 1 (m4)
	bool getX1Btn() const { return X1Btn; }

	// returns the state of extra mouse button 2 (m5)
	bool getX2Btn() const { return X2Btn; }

	// checks if the mouse is currently being captured by the window
	bool getCaptureState() const { return isMouseCaptured; }

};

#endif // !_ORBIT_INPUT_MOUSESTATE_H