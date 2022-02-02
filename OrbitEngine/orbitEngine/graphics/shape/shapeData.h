// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Shape Data Struct Specification
// ===========================================================================

#ifndef _ORBIT_GRAPHICS_SHAPEDATA_H
#define _ORBIT_GRAPHICS_SHAPEDATA_H

// import minimal windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "../dximport.h"
#include "../vertex.h"
#include "../../common/colors.h"
#include <array>

// related constructs

// specifies the supported basic shapes that shape data can be translated to.
enum class BasicShape
{
	RECTANGLE
};


// main definition

// high level shape data struct that must be translated to extract primitive
// data such as vertices and primitive types before it can be rendered
struct ShapeData
{
	// members
	BasicShape	type;			// specifies the basic shape type
	float		x;				// x-coordinate for shape's top-left corner
	float		y;				// y-coordinate for shape's top-left corner
	float		relX;			// x-offset from logical to actual position 
	float		relY;			// y-offset from logical to actual position
	float		z;				// z-position for depth of text (0.0 - 1.0)
	float		width;			// width of shape
	float		height;			// height of shape
	COLOR_ARGB	color;			// color for shape
	COLOR_ARGB	endGradient;	// if defined, creates gradient (color -> end)
	bool		xGradient;		// if true, gradient dir = x-axis, else y-axis
	
	// convenience constructor
	ShapeData(
		const BasicShape&	_type			= BasicShape::RECTANGLE,
		const float&		_x				= 0,
		const float&		_y				= 0,
		const float&		_z				= 0.5f,
		const float&		_width			= 0,
		const float&		_height			= 0,
		const COLOR_ARGB&	_color			= Colors::BLACK,
		const COLOR_ARGB&	_endGradient	= NULL,
		const bool&			_xGradient		= true
	):
		type			(_type),
		x				(_x),
		y				(_y),
		relX			(0),
		relY			(0),
		z				(_z),
		width			(_width),
		height			(_height),
		color			(_color),
		endGradient		(_endGradient),
		xGradient		(_xGradient)
	{
		// if end gradient is not specified, set it to color for solid color
		if (!endGradient) endGradient = color;
	}
};

#endif // !_ORBIT_GRAPHICS_SHAPEDATA_H