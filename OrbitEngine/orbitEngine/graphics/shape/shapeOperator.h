// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Shape Operator Class Specification
// ===========================================================================

#ifndef _ORBIT_GRAPHICS_SHAPEOPERATOR_H
#define _ORBIT_GRAPHICS_SHAPEOPERATOR_H

// import minimal windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "shapeData.h"
#include "shapeTranslator.h"
#include "../dximport.h"
#include "../graphicsContext.h"
#include "../graphicsOperator.h"


// main definition

// specifies an object that operates on pure shape data objects, and is
// responsible for handling shape data logic
class ShapeOperator : public GraphicsOperator
{
public:

	// constructor
	ShapeOperator(GraphicsContext* _context);


	// methods

	// translates and queues the shape for rendering. should only be called
	// between the graphics context's beginSpriteDraw()...endSpriteDraw()
	// method calls.
	void render(
		const ShapeData&	shape,
		const float&		x			= 0,
		const float&		y			= 0
	);
};

#endif // !_ORBIT_GRAPHICS_SHAPEOPERATOR_H