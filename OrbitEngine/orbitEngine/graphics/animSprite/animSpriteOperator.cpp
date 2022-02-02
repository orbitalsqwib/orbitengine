// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Animated Sprite Operator Class Implementation
// ===========================================================================

// import specification
#include "animSpriteOperator.h"


// ===========================================================================
// constructor
// ===========================================================================
AnimSpriteOperator::AnimSpriteOperator(
	GraphicsContext*	_context
):
	// base constructor
	GraphicsOperator	(_context)
{}


// methods

// ===========================================================================
// updates the sprite data's spritesheet source rect selection according
// to the current frame of the sprite animation
// ===========================================================================
void AnimSpriteOperator::updateSpriteForAnimation(
	const AnimSpriteData&	animData,
	SpriteData&				sprite
) {
	// update spriteData.sheetRect to draw currentFrame
	sprite.srcRect.left
		= (animData.currentFrame % animData.nSrcCols) * sprite.width;
	sprite.srcRect.top
		= (animData.currentFrame / animData.nSrcCols) * sprite.height;

	// right edge and bottom edge +1
	sprite.srcRect.right
		= sprite.srcRect.left + sprite.width;
	sprite.srcRect.bottom
		= sprite.srcRect.top + sprite.height;
}

// ===========================================================================
// updates animation data timer and handles frame updates accordingly
// ===========================================================================
void AnimSpriteOperator::updateAnimation(
	AnimSpriteData&		animData,
	SpriteData&			sprite,
	const float&		updateTime
) {
	// ensure sprite has a valid animation
	if (animData.endFrame - animData.startFrame <= 0) return;

	// update total elapsed time
	animData.frameTimer += updateTime;

	// if animation timer is still lower than frame delay, continue waiting
	if (animData.frameTimer <= animData.frameDelay) return;

	// else, update animation

	// update timer and frame counter
	animData.frameTimer -= animData.frameDelay;
	animData.currentFrame++;

	// update sprite frame
	updateSpriteForAnimation(animData, sprite);

	// handle animation complete
	if (
		animData.currentFrame < animData.startFrame || 
		animData.currentFrame > animData.endFrame
	) {
		// if animation is looping
		if (animData.loop == true)
		{
			// set current frame to start frame on completion
			animData.currentFrame = animData.startFrame;
		}

		// else if non-looping, stop animation
		else {
			animData.currentFrame = animData.endFrame;
			animData.stopped = true;
		}
	}
}