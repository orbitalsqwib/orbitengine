// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngineECS : Signature Type Specification
// ===========================================================================
// ACKNOWLEDGEMENT: This Entity Component System was built with reference to a 
// plethora of sources, but most of the inspiration came from this reference:
// https://austinmorlan.com/posts/entity_component_system.
// ===========================================================================

#ifndef _ORBIT_ECS_SIGNATURE_H
#define _ORBIT_ECS_SIGNATURE_H

// import windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "componentTypeEnum.h"
#include <bitset>


// main definitions

// defines a fast way to identify the components a certain entity has by
// representing each component type as a single bit within the bitset, e.g:
// the nth bit represents the nth component type in the ECS.
typedef std::bitset<ECS_MAX_COMPONENTS> Signature;

#endif // !_ORBIT_ECS_SIGNATURE_H