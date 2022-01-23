// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Primitive Shape / Factory Class Implementation
// ===========================================================================

// import specification
#include "primitiveShape.h"


// factory methods

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
PrimitiveShape<4> ShapeFactory::createRect(
	const float&	x,
	const float&	y,
	const float&	z,
	const float&	w,
	const float&	h,
	COLOR_ARGB		startCol,
	COLOR_ARGB		endCol,
	bool			xGrad
) {
	// handle single color rect
	if (!endCol) endCol = startCol;

	// generate and return PrimitiveShape
	return PrimitiveShape<4>(
		std::array<Vertex, 4>{
			Vertex(x,     y,     z, xGrad ? startCol : startCol, 0.0f, 0.0f),
			Vertex(x + w, y,     z, xGrad ? startCol : endCol,   1.0f, 0.0f),
			Vertex(x,     y + h, z, xGrad ? endCol   : startCol, 0.0f, 1.0f),
			Vertex(x + w, y + h, z, xGrad ? endCol   : endCol,   1.0f, 1.0f),
		},
		D3DPT_TRIANGLESTRIP,
		2
	);
}