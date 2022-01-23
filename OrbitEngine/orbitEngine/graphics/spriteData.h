// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Sprite Data Struct Specification
// ===========================================================================

#ifndef _ORBIT_GRAPHICS_SPRITEDATA_H
#define _ORBIT_GRAPHICS_SPRITEDATA_H

// import minimal windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "dximport.h"


// main definition

// defines a set of data that can be sent to the graphics handler to position, 
// transform and display a sprite texture within a window.
struct SpriteData
{
	// members
	int			width;		// width of sprite in pixels
	int			height;		// height of sprite in pixels
	float		x;			// x-coord for top left corner of sprite
	float		y;			// y-coord for top left corner of sprite
	float		z;			// z-coord for depth of sprite (0 to 100)
	float		angle;		// rotation angle in radians
	float		scale;		// scales both width and height
	RECT		srcRect;	// selects a portion of the spritesheet to display
	LP_TEXTURE	pTexture;	// pointer to texture data
	bool		flipX;		// mirror sprite on the x-axis
	bool		flipY;		// mirror sprite on the y-axis

	// convenience constructor
	SpriteData(
		const int&		_width		= 0,
		const int&		_height		= 0,
		const float&	_x			= 0,
		const float&	_y			= 0,
		const float&	_z			= 0,
		const float&	_angle		= 0,
		const float&	_scale		= 0,
		const RECT&		_srcRect	= {0, 0, 0, 0},
		LP_TEXTURE		_pTexture	= NULL,
		const bool&		_flipX		= 0,
		const bool&		_flipY		= 0
	):
		width		(_width),
		height		(_height),
		x			(_x),
		y			(_y),
		z			(_z),
		angle		(_angle),
		scale		(_scale),
		srcRect		(_srcRect),
		pTexture	(_pTexture),
		flipX		(_flipX),
		flipY		(_flipY)
	{}
};

#endif // !_ORBIT_GRAPHICS_SPRITEDATA_H