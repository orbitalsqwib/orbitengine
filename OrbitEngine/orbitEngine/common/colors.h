// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Common Colors
// ===========================================================================

#ifndef _ORBIT_COMMON_COLORS_H
#define _ORBIT_COMMON_COLORS_H

// import minimal windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// define alias for argb color data for clarity
#define COLOR_ARGB DWORD

// define convenience method to construct color data using a, r, g, b values
#define SETCOLOR_ARGB(a, r, g, b) \
	(DWORD)				\
	((a&0xff) << 24 ) |	\
	((r&0xff) << 16 ) |	\
	((g&0xff) <<  8 ) |	\
	(b&0xff)


// main definition

// common color value enums
enum Colors : COLOR_ARGB
{
	// ARGB channel values range from 0 - 255 inclusive.
	// A = Alpha channel (0 = transparent, 255 = opaque)
	// RGB = Red, Green, Blue channels respectively

	// colorwheel ==================================

	PURPLE		= SETCOLOR_ARGB(255, 128,   0, 128),
	MAROON		= SETCOLOR_ARGB(255, 128,   0,   0),
	RED			= SETCOLOR_ARGB(255, 255,   0,   0),
	MAGENTA		= SETCOLOR_ARGB(255, 255,   0, 255),
	OLIVE		= SETCOLOR_ARGB(255, 128, 128,   0),
	BROWN		= SETCOLOR_ARGB(255, 139,  69,  19),
	ORANGE		= SETCOLOR_ARGB(255, 255, 165,   0),
	YELLOW		= SETCOLOR_ARGB(255, 255, 255,   0),
	GREEN		= SETCOLOR_ARGB(255,   0, 128,   0),
	LIME		= SETCOLOR_ARGB(255,   0, 255,   0),
	TEAL		= SETCOLOR_ARGB(255,   0, 128, 128),
	CYAN		= SETCOLOR_ARGB(255,   0, 255, 255),
	NAVY		= SETCOLOR_ARGB(255,   0,   0, 128),
	BLUE		= SETCOLOR_ARGB(255,   0,   0, 255),

	// greyscale ===================================

	WHITE		= SETCOLOR_ARGB(255, 255, 255, 255),
	LTGRAY		= SETCOLOR_ARGB(255, 192, 192, 192),
	GRAY		= SETCOLOR_ARGB(255, 128, 128, 128),
	BLACK		= SETCOLOR_ARGB(255,   0,   0,   0),

	// opacity compopnents =========================

	ALPHA0		= SETCOLOR_ARGB(  0, 255, 255, 255),
	ALPHA25		= SETCOLOR_ARGB( 64, 255, 255, 255),
	ALPHA50		= SETCOLOR_ARGB(128, 255, 255, 255),
	ALPHA75		= SETCOLOR_ARGB(192, 255, 255, 255),
	ALPHAMASK	= SETCOLOR_ARGB(255,   0,   0,   0),

	// use to specify drawing with colorfilter =====

	FILTER		= SETCOLOR_ARGB(  0,   0,   0,   0),

	// transparency key color ======================

	TRANS_KEY	= SETCOLOR_ARGB(  0, 255,   0, 255),
};

#endif // !_ORBIT_COMMON_COLORS_H