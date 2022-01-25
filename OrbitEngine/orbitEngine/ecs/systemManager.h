// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngineECS : System Manager Class Specification
// ===========================================================================
// ACKNOWLEDGEMENT: This Entity Component System was built with reference to a 
// plethora of sources, but most of the inspiration came from this reference:
// https://austinmorlan.com/posts/entity_component_system.
// ===========================================================================

#ifndef _ORBIT_ECS_SYSTEMMANAGER_H
#define _ORBIT_ECS_SYSTEMMANAGER_H

// import necessary headers
#include "types.h"
#include "system.h"
#include "../utils/pointers.h"
#include <unordered_map>
#include <typeinfo>


// main definition

// manager class responsible for maintaining the entity arrays of the systems
// bound to this class and their system signatures, adding and removing 
// entities from systems according to whether the entity has the desired
// subset of components the system requires.
class SystemManager
{
private:

	// typedefs

	// defines a constant type string as returned by typeid().name()
	typedef const char* TYPE_STRING;

	typedef std::unordered_map<TYPE_STRING, UniquePtr<System>> SYSTEM_MAP;


	// members

	// maps system type strings to system signatures
	std::unordered_map<TYPE_STRING, Signature> signatures;

	// maps system type strings to unique pointers of generic systems.
	SYSTEM_MAP systems;

public:

	// constructor
	SystemManager();


	// methods

	// registers a system with the system manager, creating a new system 
	// object instance within the system manager. also returns a pointer to 
	// the newly-created system so it can be used externally.
	template <class SystemType>
	SystemType* registerSystem();

	// notifies the manager that an entity has been destroyed. this removes
	// the entity from all system entity containers that contain it.
	void notifyEntityDestroyed(const Entity& entity);

	// notifies the manager that the signature for an entity has been updated.
	// updates the system entity containers for all registered systems and
	// removes or adds the entity accordingly.
	void notifyEntitySignatureChanged(
		const Entity&		entity,
		const Signature&	newSignature
	);


	// setters

	// sets the signature for a registered system. this controls the criteria
	// for entities to be added or removed from the system entity container.
	// i.e: an entity's signature has to contain the system signature in order
	// for a system to operate on it
	template <class SystemType>
	void setSignature(const Signature& signature);

};

#endif // !_ORBIT_ECS_SYSTEMMANAGER_H