// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Text Operator Class Specification
// ===========================================================================

#ifndef _ORBIT_GRAPHICS_TEXTOPERATOR_H
#define _ORBIT_GRAPHICS_TEXTOPERATOR_H

// import minimal windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "textData.h"
#include "../shape/shapeOperator.h"
#include "../textStyle/textStyleOperator.h"
#include "../dximport.h"
#include "../graphicsContext.h"
#include "../graphicsOperator.h"


// main definition

// specifies an object that operates on pure sprite data objects, and is
// responsible for handling sprite logic
class TextOperator : public GraphicsOperator
{
private:

	// internal shape operator
	ShapeOperator shapeOp;

	// internal text style operator
	TextStyleOperator textStyleOp;

public:

	// constructor
	TextOperator(GraphicsContext* _context);


	// methods

	// queues text data to be rendered relative to the specified coordinates.
	// should only be called between the graphics context's 
	// beginSpriteDraw()...endSpriteDraw() method calls.
	void render(
		TextData&		text,
		const UINT&		format	= DT_LEFT
	);

};

#endif // !_ORBIT_GRAPHICS_TEXTOPERATOR_H