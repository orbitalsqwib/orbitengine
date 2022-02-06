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
#include "../types.h"
#include <set>

// forward declaration
class ECSInstance;


// main definition

// defines a base system object that contains a container for entities that
// match the system's signature and can be managed by a system manager. logic
// should be specified per system, and does not prescribe a fixed run() method
// that will be called every update. it is up to the implementer to call the
// necessary system methods as needed for the logic to work.
class System 
{
protected: 

	// allow system manager to manage system entities
	friend class SystemManager;


	// typedefs

	// defines a set of entities that can be iterated through
	typedef std::set<Entity> ENTITY_SET;


	// members

	// protected entities container that can be accessed by system logic
	ENTITY_SET entities;

	// stores a pointer to the ecs instance containing this system
	ECSInstance* ecs;

	
	// protected constructor
	System(): entities(), ecs(nullptr) {}

public: 

	// virtual destructor
	virtual ~System() {}
};

#endif // !_ORBIT_ECS_SYSTEM_H