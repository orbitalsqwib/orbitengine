// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngineECS : Component Type Enum Specification
// ===========================================================================
// ACKNOWLEDGEMENT: This Entity Component System was built with reference to a 
// plethora of sources, but most of the inspiration came from this reference:
// https://austinmorlan.com/posts/entity_component_system.
// ===========================================================================

#ifndef _ORBIT_ECS_COMPONENTTYPEENUM_H
#define _ORBIT_ECS_COMPONENTTYPEENUM_H

// import windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// include necessary headers
#include <limits>

// main definitions

// represents a unique identifier for every component type within a single ECS
// instance. this can be thought of as an enumeration for each component type.
// this is necessary to implement a signature for each entity, which describes
// the components it contains as a bitfield, where the nth bit corresponds to
// the nth component type.
typedef UCHAR ComponentTypeEnum;

// define the maximum number of components for this ECS.
const UCHAR ECS_MAX_COMPONENTS = UCHAR_MAX;

#endif // !_ORBIT_ECS_COMPONENTTYPEENUM_H