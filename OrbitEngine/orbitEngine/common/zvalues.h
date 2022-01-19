// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Common Z Values
// ===========================================================================

#ifndef _ORBIT_COMMON_ZVALUES_H
#define _ORBIT_COMMON_ZVALUES_H

// main definition

// provides common z-values and references
namespace ZValues
{
	// (0.0 <= z < 0.1) layer reserved for debug and important information
	const float RESERVED	= 0.0f;

	// (0.1 <= z < 0.2) layer reserved for overlays that should go "over" UIs
	const float OVERLAYS	= 0.1f;

	// (0.2 <= z < 0.5) layer reserved for normal user interface elements
	const float UI			= 0.2f;

	// (0.3 <= z < 0.5) foreground layer - entities go here
	const float FOREGROUND	= 0.3f;

	// (0.8 <= z < 1.0) background layer - scene backgrounds go here
	const float BACKGROUND	= 0.8f;

	// maximum z-value. entities over this limit may be clipped from view
	const float MAX			= 1.0f;
};

#endif // !_ORBIT_COMMON_ZVALUES_H