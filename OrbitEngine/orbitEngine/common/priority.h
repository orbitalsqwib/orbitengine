// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Priority Enum Class Specification
// ===========================================================================

#ifndef _ORBIT_COMMON_PRIORITY_H
#define _ORBIT_COMMON_PRIORITY_H

// import windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>


// main definition

// specifies a basic set of discrete priority values.
enum class Priority : UCHAR
{
	// should be overridden by any priority, including itself
	NONE	= 0,

	// should be overridden only by higher priorities, excluding itself
	LOW		= 1,
	MEDIUM	= 2,
	HIGH	= 3,

	// should be overridden only by itself
	MAX		= 4
};

#endif // !_ORBIT_COMMON_PRIORITY_H