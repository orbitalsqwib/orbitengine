// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Global Configuration Specification
// ===========================================================================

#ifndef _ORBIT_CONFIG_H
#define _ORBIT_CONFIG_H

// import windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>


// specify namespaced configurations

// general settings
namespace SETTINGS_NS {

	// configurable constants

	// initial window top-left x-position
	const LONG	WND_INIT_X			= 64;

	// initial window top-left y-position
	const LONG	WND_INIT_Y			= 64;

	// initial window width
	const LONG	WND_INIT_WIDTH		= 1280;

	// initial window height
	const LONG	WND_INIT_HEIGHT		= 720;


	// behavioural settings

	// specifies whether to terminate the main message loop once all window
	// instances have been destroyed
	const BOOL QUIT_ON_ZERO_WINDOWS	= TRUE;
}

#endif // !_ORBIT_CONFIG_H