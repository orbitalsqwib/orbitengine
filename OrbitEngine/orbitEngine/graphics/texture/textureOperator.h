// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Texture Operator Class Specification
// ===========================================================================

#ifndef _ORBIT_GRAPHICS_TEXTUREOPERATOR_H
#define _ORBIT_GRAPHICS_TEXTUREOPERATOR_H

// import minimal windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "textureData.h"
#include "../dximport.h"
#include "../graphicsContext.h"
#include "../graphicsOperator.h"


// main definition

// specifies an object that operates on pure texture data objects, and is
// responsible for handling texture logic.
class TextureOperator : public GraphicsOperator
{
public:

	// constructor
	TextureOperator(GraphicsContext* _context);

	
	// methods

	// creates a texture resource from the file specified by the texture and
	// binds it to the texture's resource pointer.
	void loadResource(TextureData& texture);

	// releases the texture resource at the texture's resource pointer
	void releaseResource(TextureData& texture);

};

#endif // !_ORBIT_GRAPHICS_TEXTUREOPERATOR_H