// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Shape Operator Class Implementation
// ===========================================================================

// import specification
#include "shapeOperator.h"


// ===========================================================================
// constructor
// ===========================================================================
ShapeOperator::ShapeOperator(
	GraphicsContext* _context
) :
	// base constructor
	GraphicsOperator(_context)
{}


// methods

// ===========================================================================
// translates and queues the shape for rendering. should only be called
// between the graphics context's beginSpriteDraw()...endSpriteDraw()
// method calls.
// ===========================================================================
void ShapeOperator::render(
	const ShapeData&	shape,
	const float&		x,
	const float&		y
) {
	// translate and render shape
	switch (shape.type)
	{
	case BasicShape::RECTANGLE:
	{
		// translate shape to primitives
		TranslatedShape<4> t 
			= ShapeTranslator::translateRectangle(shape, x, y);

		// draw primitives
		context->drawVertices(
			t.vertices.data(),
			4,
			t.type,
			t.nPrimitives
		);
	}
	default:
	{
		// if not caught throw warning
		throw Error("Warning: Unknown Shape!", ErrorType::WARNING);
	}
	}
}