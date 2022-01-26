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

	// defines a pair of signatures. the first signature is the standard
	// system signature, which an entity must possess as a subset of its total
	// components. the second signature is the exclusive system signature,
	// which specifies the components that an entity cannot have, and acts as
	// a sort of filter for systems
	typedef std::pair<Signature, Signature> SIGNATURE_PAIR;

	// defines a map of type strings : unique pointers of generic systems
	typedef std::unordered_map<TYPE_STRING, UniquePtr<System>> SYSTEM_MAP;


	// members

	// maps system type strings to system signatures
	std::unordered_map<TYPE_STRING, SIGNATURE_PAIR> signatures;

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

	// sets the standard  signature for a registered system. this controls the
	// components that an entity must possess in order to be added to the
	// system.
	template <class SystemType>
	void setSignature(const Signature& signature);

	// sets the exclusive signature for a registered system. this controls the
	// components that an entity must not have in order to be added to the
	// system
	template <class SystemType>
	void setExclusiveSignature(const Signature& signature);

};

#endif // !_ORBIT_ECS_SYSTEMMANAGER_H