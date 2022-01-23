// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Graphics Vertex Struct Specification
// ===========================================================================

#ifndef _ORBIT_GRAPHICS_VERTEX_H
#define _ORBIT_GRAPHICS_VERTEX_H

// import minimal windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "dximport.h"
#include "../common/colors.h"

// define FVF format for Vertex
#define D3DFVF_Vertex (D3DFVF_XYZ | D3DFVF_DIFFUSE)


// main definition

// defines a basic vertex struct with position, color and texture coordinate
// components. also provides a constructor for ease of use.
struct Vertex
{
	// position component
	FLOAT	x, y, z;

	// color component
	COLOR_ARGB	color;

	// texture coordinate component
	FLOAT	tu, tv;

	// constructor
	Vertex(
		float		_x,
		float		_y,
		float		_z,
		COLOR_ARGB	_color,
		float		_tu,
		float		_tv
	) :
		x		(_x),
		y		(_y),
		z		(_z),
		color	(_color),
		tu		(_tu),
		tv		(_tv)
	{}
};

#endif // !_ORBIT_GRAPHICS_VERTEX_H