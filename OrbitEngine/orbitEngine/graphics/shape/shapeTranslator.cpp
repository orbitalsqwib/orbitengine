// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Shape Translator Struct Implementation
// ===========================================================================

// import specification
#include "shapeTranslator.h"


// methods

// ===========================================================================
// creates a rectangle with a triangle strip. if yGradient is set to true,
// the gradient made from startCol...endCol will be displayed vertically,
// from top to bottom. otherwise, the gradient will be displayed
// horizontally, from left to right.
// ===========================================================================
// the vertice order & texture coords for the triangle strip are as follows:
// +----------> x   +---------> tu
// |     w          |
// |   0---1        |   0,0---1,0
// |   |  /|        |    |   / |
// | h | / |        |    |  /  |
// |   |/  |        |    | /   |
// v   2---3        v   0,1---1,1
// y                tv
// ===========================================================================
TranslatedShape<4>&& ShapeTranslator::translateRectangle(
	const ShapeData&	shape
) {
	// handle single color shapes
	COLOR_ARGB endGrad = shape.endGradient ? shape.color : shape.endGradient;

	// generate and return PrimitiveShape
	return std::move(TranslatedShape<4>(
		std::array<Vertex, 4>{
			Vertex(
				shape.x + shape.relX,
				shape.y + shape.relY,
				shape.z, 
				shape.color,
				0.0f, 0.0f
			),
			Vertex(
				shape.x + shape.relX + shape.width,
				shape.y + shape.relY,
				shape.z, 
				shape.xGradient ? shape.color : endGrad,
				1.0f, 0.0f
			),
			Vertex(
				shape.x + shape.relX,
				shape.y + shape.relY + shape.height,
				shape.z,
				shape.xGradient ? endGrad : shape.color,
				0.0f, 1.0f
			),
			Vertex(
				shape.x + shape.relX + shape.width,
				shape.y + shape.relY + shape.height,
				shape.z,
				endGrad,
				1.0f, 1.0f
			)
		},
		D3DPT_TRIANGLESTRIP,
		2
	));
}