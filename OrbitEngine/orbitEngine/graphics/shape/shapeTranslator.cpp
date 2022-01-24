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
	const ShapeData&	shape,
	float				x,
	float				y
) {
	// assert that shape endGradient should not be null
	assert(shape.endGradient);

	// generate and return PrimitiveShape
	return std::move(TranslatedShape<4>(
		std::array<Vertex, 4>{
			Vertex(
				x + shape.relX,
				y + shape.relY,
				shape.z, 
				shape.color,
				0.0f, 0.0f
			),
			Vertex(
				x + shape.relX + shape.width,
				y + shape.relY,
				shape.z, 
				shape.xGradient ? shape.color : shape.endGradient,
				1.0f, 0.0f
			),
			Vertex(
				x + shape.relX,
				y + shape.relY + shape.height,
				shape.z,
				shape.xGradient ? shape.endGradient : shape.color,
				0.0f, 1.0f
			),
			Vertex(
				x + shape.relX + shape.width,
				y + shape.relY + shape.height,
				shape.z,
				shape.endGradient,
				1.0f, 1.0f
			)
		},
		D3DPT_TRIANGLESTRIP,
		2
	));
}