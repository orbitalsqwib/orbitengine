// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Graphics Operator Class Specification
// ===========================================================================

#ifndef _ORBIT_GRAPHICS_GRAPHICSOPERATOR_H
#define _ORBIT_GRAPHICS_GRAPHICSOPERATOR_H

// import necessary headers
#include "graphicsContext.h"


// main definition

// specifies a generic graphics operator that provides a pointer reference to
// the graphics context for any graphics operations to be carried out.
class GraphicsOperator
{
protected:

	// members

	// specifies the graphics context for all graphics operations
	GraphicsContext* context;

public:

	// constructor
	GraphicsOperator(GraphicsContext* _context) : context(_context) {}
};


#endif // !_ORBIT_GRAPHICS_GRAPHICSOPERATOR_H