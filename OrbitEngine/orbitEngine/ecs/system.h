// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngineECS : System Base Class Specification
// ===========================================================================
// ACKNOWLEDGEMENT: This Entity Component System was built with reference to a 
// plethora of sources, but most of the inspiration came from this reference:
// https://austinmorlan.com/posts/entity_component_system.
// ===========================================================================

#ifndef _ORBIT_ECS_SYSTEM_H
#define _ORBIT_ECS_SYSTEM_H

// import necessary headers
#include "types.h"
#include <set>


// main definition

// defines a base system object that contains a container for entities that
// match the system's signature and can be managed by a system manager. can
// be inherited by other classes with non-virtual inheritance.
class System 
{
protected: 

	// allow system manager to manage system entities
	friend class SystemManager;

	// protected entities container that can be accessed by system logic
	std::set<Entity> entities;

};

#endif // !_ORBIT_ECS_SYSTEM_H