// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Game Window Specification
// ===========================================================================

#ifndef _ORBIT_WINDOWCLASS_GAMEWINDOW_H
#define _ORBIT_WINDOWCLASS_GAMEWINDOW_H

// import necessary headers
#include "../window.h"
#include "../extensions/displayExtension.h"
#include "../extensions/inputExtension.h"


// main definition

// specifies the main game window class - this is what the game will be
// rendered upon and user inputs recieved through
class GameWindow : public Window<GameWindow>
{
public:

	// constructor
	GameWindow(
		KeyboardState*	keyboardState	= nullptr, 
		MouseState*		mouseState		= nullptr,
		MessageBroker*	externalBroker	= nullptr			
	);

	// delegate wndproc
	virtual LRESULT wndProc(
		UINT	msg,
		WPARAM	wParam,
		LPARAM	lParam
	);
};

#endif // !_ORBIT_WINDOWCLASS_GAMEWINDOW_H