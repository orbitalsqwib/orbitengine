// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Window Commands Enum Class Specification
// ===========================================================================

#ifndef _ORBIT_COMMON_WINDOWCOMMANDS_H
#define _ORBIT_COMMON_WINDOWCOMMANDS_H

// main definition

// specifies a list of commands that can be sent to a window instance to
// modify the state and/or behaviour of its display extension
enum class WindowDisplayCommands {

	// DISPLAY EXTENSION

	// sets window style to bordered
	SETSTYLE_BORDERED,

	// sets window style to borderless
	SETSTYLE_BORDERLESS,

	// sets window style to unset
	SETSTYLE_UNSET,

	// turns window resizing off
	SETRESIZE_OFF,

	// turns window resizing on
	SETRESIZE_ON,

	// turns window dragging off
	SETDRAGGING_OFF,

	// turns window dragging on
	SETDRAGGING_ON,

	// turns window shadows off
	SETSHADOWS_OFF,

	// turns window shadows on
	SETSHADOWS_ON,

	// convenience command - set window to borderless fullscreen
	BORDERLESSFULLSCREEN,

	// convenience command - set window to bordered windowed
	BORDEREDWINDOWED,

	// convenience command - toggle window between borderless fullscreen and
	// bordered window display modes
	TOGGLEBORDERLESSFULLSCREEN

};

#endif // !_ORBIT_COMMON_WINDOWCOMMANDS_H