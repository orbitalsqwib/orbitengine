// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Window Style Enum Class Specification
// ===========================================================================

#ifndef _ORBIT_COMMON_WINDOWSTYLE_H
#define _ORBIT_COMMON_WINDOWSTYLE_H

// import windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>


// main definition

// specifies a mapping of all possible window styles for the window display
// extension to their respective window style values
enum class WindowStyle : DWORD
{
	BORDERED
	= WS_OVERLAPPED
	| WS_SIZEBOX
	| WS_CAPTION
	| WS_SYSMENU
	| WS_MINIMIZEBOX
	| WS_MAXIMIZEBOX,

	BORDERLESS
	= WS_POPUP
	| WS_SIZEBOX
	| WS_CAPTION
	| WS_SYSMENU
	| WS_MINIMIZEBOX
	| WS_MAXIMIZEBOX,

	BD_FALLBACK
	= WS_POPUP
	| WS_SIZEBOX
	| WS_SYSMENU
	| WS_MINIMIZEBOX
	| WS_MAXIMIZEBOX,

	UNSET
	= NULL
};

#endif // !_ORBIT_COMMON_WINDOWSTYLE_H