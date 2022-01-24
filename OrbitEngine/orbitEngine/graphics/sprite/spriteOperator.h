// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Sprite Operator Class Specification
// ===========================================================================

#ifndef _ORBIT_GRAPHICS_SPRITEOPERATOR_H
#define _ORBIT_GRAPHICS_SPRITEOPERATOR_H

// import minimal windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "spriteData.h"
#include "../dximport.h"
#include "../graphicsContext.h"
#include "../graphicsOperator.h"


// main definition

// specifies an object that operates on pure sprite data objects, and is
// responsible for handling sprite logic
class SpriteOperator : public GraphicsOperator
{
public:

	// constructor
	SpriteOperator(GraphicsContext* _context);


	// methods

	// queues a sprite to be drawn with the texture and transforms specified
	// by a spriteData struct. should only be called between the graphics
	// context's beginSpriteDraw()...endSpriteDraw() method calls.
	void render(
		const SpriteData&	sprite,
		const float&		x			= 0,
		const float&		y			= 0,
		COLOR_ARGB			color		= Colors::WHITE
	);

};

#endif // !_ORBIT_GRAPHICS_SPRITEOPERATOR_H