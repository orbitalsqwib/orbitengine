// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Float-based Rect Struct
// ===========================================================================

#ifndef _ORBIT_UTILS_FLOATRECT_H
#define _ORBIT_UTILS_FLOATRECT_H

// import windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>


// main definition

struct FloatRect
{
	float left;
	float top;
	float right;
	float bottom;

	// default constructor
	FloatRect(): left(0), top(0), right(0), bottom(0) {}

	// convenience constructor
	FloatRect(
		const float& _left,
		const float& _top,
		const float& _right,
		const float& _bottom
	) :
		left	(_left),
		top		(_top),
		right	(_right),
		bottom	(_bottom)
	{}

	// convenience converter to RECT
	RECT getRECT()
	{
		return RECT{
			long(left),
			long(top),
			long(right),
			long(bottom)
		};
	}
};

#endif // !_ORBIT_UTILS_FLOATRECT_H