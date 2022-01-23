// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Graphics Notifications Enum Class Specification
// ===========================================================================

#ifndef _ORBIT_COMMON_GRAPHICSNOTIFICATIONS_H
#define _ORBIT_COMMON_GRAPHICSNOTIFICATIONS_H

// main definition

// defines a set of commands that graphics objects should handle
enum class GraphicsObjectCommands
{
	// notifies the receiver that they should release any graphics resources
	// they own - this is usually called when the graphics device is about
	// to be reset by the graphics handler
	RELEASE_ALL_GRAPHICS,

	// notifies the receiver that they should reinitialize or reacquire any
	// graphics resources they previously released - this is usually called 
	// when the graphics device has been reset by the graphics handler
	RESET_ALL_GRAPHICS
};

#endif // !_ORBIT_COMMON_GRAPHICSNOTIFICATIONS_H