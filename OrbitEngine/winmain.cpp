// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// WinMain : Main Application Entry Point
// ===========================================================================

// import windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "orbitEngine/engine/orbitEngine.h"


int WINAPI WinMain(
	_In_		HINSTANCE	,
	_In_opt_	HINSTANCE	,
	_In_		LPSTR		,
	_In_		int			
) {
	// create game engine instance
	OrbitEngine game(L"Survive The Void");

	// initialize message loop states
	MSG msg;
	int exit = false;

	// run message loop
	while (!exit) {

		// check for new messages
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// check for and handle application quit messages
			if (msg.message == WM_QUIT) exit = true;

			// translate and dispatch message to relevant window
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}

		// run game
		game.update();

	}
	
	// return final message parameters on quit
	return static_cast<int>(msg.wParam);
}