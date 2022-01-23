// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Primitive Shape / Factory Class Specification
// ===========================================================================

#ifndef _ORBIT_GRAPHICS_PRIMITIVESHAPE_H
#define _ORBIT_GRAPHICS_PRIMITIVESHAPE_H

// import necessary headers
#include "dximport.h"
#include "vertex.h"
#include <array>


// main definition

// generic primitive shape data struct that contains an array of vertices and 
// also specifies the type of primitive the vertices should be rendered as.
template <size_t nVertices>
struct PrimitiveShape
{
	// contains all vertices making up the shape
	std::array<Vertex, nVertices> vertices;

	// specifies the primitive type (i.e: line strips, triangle strips)
	D3DPRIMITIVETYPE type;

	// specifies the number of primitives in the shape
	UINT nPrimitives;

	
	// convenience constructor
	PrimitiveShape(
		std::array<Vertex, nVertices>	_vertices,
		const D3DPRIMITIVETYPE&			_type,
		const UINT&						_nPrimitives						
	):
		vertices	(_vertices),
		type		(_type),
		nPrimitives	(_nPrimitives)
	{}
};

// convenience class that generates and returns basic primitive shapes in the
// form of a PrimitiveShape struct.
class ShapeFactory
{
public:

	// creates a rectangle with a triangle strip. if yGradient is set to true,
	// the gradient made from startCol...endCol will be displayed vertically,
	// from top to bottom. otherwise, the gradient will be displayed
	// horizontally, from left to right.
	static PrimitiveShape<4> createRect(
		const float&	x,
		const float&	y,
		const float&	z,
		const float&	width,
		const float&	height,
		COLOR_ARGB		startCol,
		COLOR_ARGB		endCol		= NULL,
		bool			yGradient	= FALSE
	);

};

#endif // !_ORBIT_GRAPHICS_PRIMITIVESHAPE_H