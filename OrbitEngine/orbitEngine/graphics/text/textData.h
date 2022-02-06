// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Text Data Struct Specification
// ===========================================================================

#ifndef _ORBIT_GRAPHICS_TEXTDATA_H
#define _ORBIT_GRAPHICS_TEXTDATA_H

// import minimal windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "../dximport.h"
#include "../textStyle/textStyleData.h"
#include "../../common/zvalues.h"
#include <string>


// main definition

// defines text data such as font data, highlighting data and the font 
// resource pointer. as a piece of pure state, all logic using these data
// should be carried out by text operators.
struct TextData
{
	// members
	std::string		text;	// text content to display
	float			x;		// x-position for text's top-left corner
	float			y;		// y-position for text's top-left corner
	float			relX;	// x-offset from logical to actual position 
	float			relY;	// y-offset from logical to actual position
	float			z;		// z-position for depth of text (0.0 - 1.0)
	TextStyleData*	pStyle;	// pointer to text style resource

	// convenience constructor
	TextData(
		const std::string&	_text	= "",
		const float&		_x		= 0,
		const float&		_y		= 0,
		const float&		_z		= ZValues::FOREGROUND,
		TextStyleData*		_pStyle = nullptr
	):
		text	(_text),
		x		(_x),
		y		(_y),
		relX	(0),
		relY	(0),
		z		(_z),
		pStyle	(_pStyle)
	{}
};


#endif // !_ORBIT_GRAPHICS_TEXTDATA_H