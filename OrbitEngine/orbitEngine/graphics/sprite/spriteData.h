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
#include "../dximport.h"
#include "../texture/textureData.h"


// main definition

// defines the set of data necessary to position, transform and display a
// texture resource within a window. as a piece of pure state, all logic
// using these states should be carried out by sprite operators.
struct SpriteData
{
	// members
	float			relX;		// relative x for sprite's top-left corner
	float			relY;		// relative x for sprite's top-left corner
	float			z;			// z-coord for depth of sprite (0.0 to 1.0)
	int				width;		// width of sprite in pixels
	int				height;		// height of sprite in pixels
	float			angle;		// rotation angle in radians
	float			scale;		// scales both width and height
	RECT			srcRect;	// portion of the spritesheet to display
	TextureData*	pTexture;	// pointer to texture data source
	bool			flipX;		// mirror sprite on the x-axis
	bool			flipY;		// mirror sprite on the y-axis

	// convenience constructor
	SpriteData(
		const float&	_relX		= 0,
		const float&	_relY		= 0,
		const float&	_z			= 0.5f,
		const int&		_width		= 0,
		const int&		_height		= 0,
		const float&	_angle		= 0,
		const float&	_scale		= 0,
		const RECT&		_srcRect	= {0, 0, 0, 0},
		TextureData*	_pTexture	= NULL,
		const bool&		_flipX		= 0,
		const bool&		_flipY		= 0
	):
		relX		(_relX),
		relY		(_relY),
		z			(_z),
		width		(_width),
		height		(_height),
		angle		(_angle),
		scale		(_scale),
		srcRect		(_srcRect),
		pTexture	(_pTexture),
		flipX		(_flipX),
		flipY		(_flipY)
	{}
};

#endif // !_ORBIT_GRAPHICS_SPRITEDATA_H