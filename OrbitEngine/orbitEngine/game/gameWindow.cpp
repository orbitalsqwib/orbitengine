// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Game Window Implementation
// ===========================================================================

// import specification
#include "gameWindow.h"

// ===========================================================================
// constructor
// ===========================================================================
GameWindow::GameWindow():

	// construct base object
	Window	(L"GAME_WINDOW")
{
	// add extensions
	addExtension(new DisplayExtension());
	addExtension(new InputExtension(nullptr));
}

// ===========================================================================
// delegate wndproc
// ===========================================================================
LRESULT GameWindow::wndProc(
	UINT	msg,
	WPARAM	wParam,
	LPARAM	lParam
) {
	return DefWindowProc(getHwnd(), msg, wParam, lParam);
}