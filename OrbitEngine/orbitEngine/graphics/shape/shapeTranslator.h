// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Shape Translator Struct Specification
// ===========================================================================

#ifndef _ORBIT_GRAPHICS_SHAPETRANSLATOR_H
#define _ORBIT_GRAPHICS_SHAPETRANSLATOR_H

// import minimal windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "shapeData.h"
#include "translatedShape.h"
#include "../dximport.h"
#include <assert.h>
#include <utility>


// main definition

// convenience struct that translates high-level shape data into drawable
// vertices and primitive types
class ShapeTranslator
{
public:

	// translates a shape of type rectangle to a triangle strip of vertices
	// that render a rectangle with the specified position, color and size
	static TranslatedShape<4>&& translateRectangle(
		const ShapeData&	shape,
		float				x		= 0,
		float				y		= 0
	);
};


#endif // !_ORBIT_GRAPHICS_SHAPETRANSLATOR_H