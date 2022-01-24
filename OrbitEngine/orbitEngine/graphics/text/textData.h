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
#include <string>


// main definition

// defines text data such as font data, highlighting data and the font 
// resource pointer. as a piece of pure state, all logic using these data
// should be carried out by text operators.
struct TextData
{
	// members
	std::string		text;	// text content to display
	float			relX;	// relative x-position for text's top-left corner
	float			relY;	// relative y-position for text's top-left corner
	float			z;		// z-position for depth of text (0.0 - 1.0)
	TextStyleData*	pStyle;	// pointer to text style resource

	// convenience constructor
	TextData(
		const std::string&	_text,
		const float&		_relX,
		const float&		_relY,
		const float&		_z
	):
		text	(_text),
		relX	(_relX),
		relY	(_relY),
		z		(_z),
		pStyle	(nullptr)
	{}
};


#endif // !_ORBIT_GRAPHICS_TEXTDATA_H