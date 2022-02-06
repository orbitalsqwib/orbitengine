// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// WinMain : Main Application Entry Point
// ===========================================================================

#define _CRT_SECURE_NO_WARNINGS

// import windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "orbitEngine/imports/engine.h"
#include "surviveTheVoid/scenes/main.h"

// include headers for memory leak detection
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>


// define application entry point (winmain)
int WINAPI WinMain(
	_In_		HINSTANCE	,
	_In_opt_	HINSTANCE	,
	_In_		LPSTR		,
	_In_		int			
) {
	// check for memory leak on debug builds
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif

	// create game engine instance
	OrbitEngine game (L"Survive The Void");
	game.registerScene<MainScene>("STV_MAIN");
	game.setInitialScene("STV_MAIN");

	// initialize message loop states
	MSG msg;
	int exit = false;

	try {

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
	}
	catch (const Error& err)
	{
		// show error message
		MessageBoxA(NULL, err.getMessage(), "Error", MB_OK);

	}
	catch (...)
	{
		// show error message
		MessageBoxA(NULL, "Unknown error occured in game", "Error", MB_OK);
	}
	
	
	// return final message parameters on quit
	return static_cast<int>(msg.wParam);
}