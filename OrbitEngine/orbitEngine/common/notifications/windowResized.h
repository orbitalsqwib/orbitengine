// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Window Resized Notification Struct Specification
// ===========================================================================

#ifndef _ORBIT_COMMON_WINDOWRESIZED_H
#define _ORBIT_COMMON_WINDOWRESIZED_H

// main definition

// notifies subscribers when a window has been resized, and includes the new
// width and height of the window.
struct WindowResized
{
	// defines the window handle for the window that resized
	HWND hwnd;

	// defines the new width and height of the window
	UINT newWidth, newHeight;

	// convenience constructor
	WindowResized(
		HWND	windowHandle	= NULL,
		UINT	updatedWidth	= 0,
		UINT	updatedHeight	= 0
	):
		hwnd		(windowHandle),
		newWidth	(updatedWidth),
		newHeight	(updatedHeight)
	{}
};

#endif // !_ORBIT_COMMON_WINDOWRESIZED_H