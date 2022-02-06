// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Translated Shape Struct Specification
// ===========================================================================

#ifndef _ORBIT_GRAPHICS_TRANSLATEDSHAPE_H
#define _ORBIT_GRAPHICS_TRANSLATEDSHAPE_H

// import minimal windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "../dximport.h"
#include "../vertex.h"
#include <array>


// main definition

// translated shape data struct that specifies primitive drawing information
// such as the shape's vertices and the type of primitive the vertices should
// be rendered as.
template <size_t nVertices>
struct TranslatedShape
{
	// contains all vertices making up the shape
	std::array<Vertex, nVertices> vertices;

	// specifies the primitive type (i.e: line strips, triangle strips)
	D3DPRIMITIVETYPE type;

	// specifies the number of primitives in the shape
	UINT nPrimitives;


	// convenience constructor
	TranslatedShape(
		std::array<Vertex, nVertices>	_vertices,
		const D3DPRIMITIVETYPE&			_type,
		const UINT&						_nPrimitives
	) :
		vertices	(_vertices),
		type		(_type),
		nPrimitives	(_nPrimitives)
	{}
};

#endif // !_ORBIT_GRAPHICS_TRANSLATEDSHAPE_H