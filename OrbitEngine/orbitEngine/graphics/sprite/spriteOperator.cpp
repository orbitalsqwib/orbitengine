// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Sprite Operator Class Implementation
// ===========================================================================

// import specification
#include "spriteOperator.h"


// ===========================================================================
// constructor
// ===========================================================================
SpriteOperator::SpriteOperator(
	GraphicsContext*	_context
):
	// base constructor
	GraphicsOperator	(_context)
{}


// methods

// ===========================================================================
// queues a sprite to be drawn with the texture and transforms specified
// by a spriteData struct. should only be called between the graphics
// context's beginSpriteDraw()...endSpriteDraw() method calls.
// ===========================================================================
void SpriteOperator::render(
	const SpriteData&	sprite,
	const float&		x,
	const float&		y,
	COLOR_ARGB			color
) {
	// ensure spriteData contains a valid texture resource, else exit early
	if (!sprite.pTexture || !sprite.pTexture->resource) return;

	// calculate center of sprite (assuming top-left corner sprite origin)
	D3DXVECTOR3 center{
		(sprite.width  >> 1) * sprite.scale,
		(sprite.height >> 1) * sprite.scale,
		0.0f
	};

	// define translation transform (translates from world origin {0, 0, 0})
	D3DXVECTOR3 translateVec{
		sprite.relX + x,
		sprite.relY + y,
		sprite.z
	};

	// define scaling transform
	D3DXVECTOR3 scalingVec{
		sprite.scale,
		sprite.scale,
		1.0f
	};

	// handle sprite reflection on y-axis (horizontal mirroring)
	if (sprite.flipY)
	{
		// ====================================================
		// apply the general reflection matrix about the y-axis
		// Ty = [-1  0]
		//      [ 0  1]
		// ====================================================
		scalingVec.x *= -1.0f;

		// update center for reflected sprite
		center.x -= sprite.width * sprite.scale;

		// compensate for offset center by translating sprite rightwards 
		// (which is only applied after all other transforms)
		translateVec.x += sprite.width * sprite.scale;
	}

	// handle sprite reflection on x-axis (vertical mirroring)
	if (sprite.flipX)
	{
		// ====================================================
		// apply the general reflection matrix about the y-axis
		// Ty = [1   0]
		//      [0  -1]
		// ====================================================
		scalingVec.y *= -1.0f;

		// update center for reflected sprite
		center.y -= sprite.height * sprite.scale;

		// compensate for offset center by translating sprite rightwards 
		// (which is only applied after all other transforms)
		translateVec.y += sprite.height * sprite.scale;
	}

	// build rotation quaternion
	D3DXQUATERNION rotationQuad;

	// define rotation matrix
	D3DXMATRIX rotationMatrix;

	// apply z-axis rotation in radians
	D3DXMatrixRotationZ(&rotationMatrix, sprite.angle);

	// transform rotationMatrix to rotationQuad
	D3DXQuaternionRotationMatrix(&rotationQuad, &rotationMatrix);

	// create final transform matrice
	D3DXMATRIX T;

	// consolidate all transforms into T: R^3 -> R^3
	D3DXMatrixTransformation(
		&T,				// transformation matrix out
		NULL,			// keep origin at top left when scaling
		NULL,			// no scaling rotation
		&scalingVec,	// scale amount
		&center,		// rotation center
		&rotationQuad,	// rotation angle
		&translateVec	// x,y,z position
	);

	// apply T to sprite
	context->getD3DSprite()->SetTransform(&T);

	// draw sprite at transformed coordinates
	context->getD3DSprite()->Draw(
		sprite.pTexture->resource,
		&sprite.srcRect,
		NULL,
		NULL,
		color
	);
}