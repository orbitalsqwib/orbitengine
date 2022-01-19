// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Game Window Specification
// ===========================================================================

#ifndef _ORBIT_GAME_GAMEWINDOW_H
#define _ORBIT_GAME_GAMEWINDOW_H

// import necessary headers
#include "../window/window.h"
#include "../window/extensions/displayExtension.h"
#include "../window/extensions/inputExtension.h"


// main definition

class GameWindow : public Window<GameWindow>
{
public:

	// constructor
	GameWindow();

	// delegate wndproc
	virtual LRESULT wndProc(
		UINT	msg,
		WPARAM	wParam,
		LPARAM	lParam
	);
};

#endif // !_ORBIT_WINDOW_GAMEWINDOW_H