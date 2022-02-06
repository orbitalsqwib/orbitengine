// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Animated Sprite Operator Class Specification
// ===========================================================================

#ifndef _ORBIT_GRAPHICS_ANIMSPRITEOPERATOR_H
#define _ORBIT_GRAPHICS_ANIMSPRITEOPERATOR_H

// import minimal windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "animSpriteData.h"
#include "../sprite/spriteData.h"
#include "../dximport.h"
#include "../graphicsContext.h"
#include "../graphicsOperator.h"


// main definition

// specifies an object that operates on pure sprite animation data objects, 
// and is responsible for handling sprite animation logic
class AnimSpriteOperator : public GraphicsOperator
{
public:

	// constructor
	AnimSpriteOperator(GraphicsContext* _context);


	// methods

	// updates the sprite data's spritesheet source rect selection according
	// to the current frame of the sprite animation
	void updateSpriteForAnimation(
		const AnimSpriteData&	animData,
		SpriteData&				sprite
	);

	// updates animation data timer and handles frame updates accordingly
	void updateAnimation(
		AnimSpriteData&		animData,
		SpriteData&			sprite,
		const float&		updateTime
	);

};

#endif // !_ORBIT_GRAPHICS_ANIMSPRITEOPERATOR_H