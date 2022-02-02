// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngineECS : System Manager Class Implementation
// ===========================================================================
// ACKNOWLEDGEMENT: This Entity Component System was built with reference to a 
// plethora of sources, but most of the inspiration came from this reference:
// https://austinmorlan.com/posts/entity_component_system.
// ===========================================================================

// import specification
#include "systemManager.h"


// ===========================================================================
// constructor
// ===========================================================================
SystemManager::SystemManager(
	ECSInstance*	_ecs
):
	// members
	signatures		(),
	systems			(),
	ecs				(_ecs)
{}


// methods

// ===========================================================================
// notifies the manager that an entity has been destroyed. this removes
// the entity from all system entity containers that contain it.
// ===========================================================================
void SystemManager::notifyEntityDestroyed(
	const Entity&	entity
) {
	// initialize iterator
	SYSTEM_MAP::iterator it = systems.begin();

	// iterate through systems map
	while (it != systems.end())
	{
		// erase entity from every system. no checks required since the entity
		// container is a set, which does nothing if the entity doesn't exist.
		it->second->entities.erase(entity);

		// increment iterator
		it++;
	}
}

// ===========================================================================
// notifies the manager that the signature for an entity has been updated.
// updates the system entity containers for all registered systems and
// removes or adds the entity accordingly.
// ===========================================================================
void SystemManager::notifyEntitySignatureChanged(
	const Entity&		entity,
	const Signature&	newSignature
) {
	// initialize iterator
	SYSTEM_MAP::iterator it = systems.begin();

	// iterate through systems map
	while (it != systems.end())
	{
		// get system signatures from signature map
		Signature standard = signatures[it->first].first;
		Signature exclusive = signatures[it->first].second;

		// check entity signature to see if it meets system criterias
		if (
			// check entity has components that the system wants
			(newSignature & standard) == standard &&
			// check entity does not have any components the system excludes
			(newSignature & exclusive) == 0
		) {
			// add without checking; set does nothing if entity already exists
			it->second->entities.insert(entity);
		}
		// else, if entity does not have the necessary components,
		else
		{
			// remove likewise; set does nothing if entity does not exist
			it->second->entities.erase(entity);
		}

		// increment iterator
		it++;
	}
}
