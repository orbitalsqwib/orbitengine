// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Animated Sprite Data Struct Specification
// ===========================================================================

#ifndef _ORBIT_GRAPHICS_ANIMSPRITEDATA_H
#define _ORBIT_GRAPHICS_ANIMSPRITEDATA_H

// import minimal windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "../dximport.h"


// main definition

// defines additional data required to add animation to a basic sprite.
struct AnimSpriteData
{
	// members
	int startFrame;		// first frame of image animation ("Z"-shape order)
	int endFrame;		// last frame of image animation ("Z"-shape order)
	int currentFrame;	// current frame of image animation ("Z"-shape order)
	float frameDelay;	// number of seconds between each animation frame
	float frameTimer;	// time elapsed since last animation frame change
	bool loop;			// specifies if animation should loop
	bool stopped;		// specifies if animation is complete
	int nSrcCols;		// number of columns in the spritesheet

	// convenience constructor
	AnimSpriteData(
		const int&		_startFrame		= 0,
		const int&		_endFrame		= 0,
		const int&		_currentFrame	= 0,
		const float&	_frameDelay		= 0.5f,
		const bool&		_loop			= true,
		const int&		_nSrcCols		= 1
	) :
		startFrame		(_startFrame),
		endFrame		(_endFrame),
		currentFrame	(_currentFrame),
		frameDelay		(_frameDelay),
		frameTimer		(0.0f),
		loop			(_loop),
		stopped			(false),
		nSrcCols		(_nSrcCols)
	{
		// nSrcCols should be set to 1 at minimum
		if (nSrcCols <= 0) nSrcCols = 1;
	}
};

#endif // !_ORBIT_GRAPHICS_ANIMSPRITEDATA_H