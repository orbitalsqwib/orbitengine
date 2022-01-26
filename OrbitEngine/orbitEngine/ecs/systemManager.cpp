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
SystemManager::SystemManager():

	// members
	signatures	(),
	systems		()
{}


// methods

// ===========================================================================
// registers a system with the system manager, creating a new system 
// object instance within the system manager. also returns a pointer to 
// the newly-created system so it can be used externally.
// ===========================================================================
template <class SystemType>
SystemType* SystemManager::registerSystem()
{
	// get type string for system
	TYPE_STRING type = typeid(System).name();

	// ensure system has not been registered before, else throw a warning
	if (systems.count(type) == 0) throw Error(
		"Warning: Component type " 
		+ std::string(type) 
		+ "has already been registered!",
		ErrorType::WARNING
	);

	// create the system and add it to systems map
	systems[type] = UniquePtr<SystemType>(new SystemType());

	// return non-owning system pointer for external use
	return systems[type].get();
}

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


// setters

// ===========================================================================
// sets the standard  signature for a registered system. this controls the
// components that an entity must possess in order to be added to the
// system.
// ===========================================================================
template <class SystemType>
void SystemManager::setSignature(
	const Signature&	signature
) {
	// get type string for system
	TYPE_STRING type = typeid(System).name();

	// ensure system has been registered before, else throw a warning
	// ensure system has not been registered before, else throw a warning
	if (systems.count(type) == 0) throw Error(
		"Warning: Component type "
		+ std::string(type)
		+ "has already been registered!",
		ErrorType::WARNING
	);

	// sets the standard signature for the specified system
	signatures[type].first = signature;
}

// ===========================================================================
// sets the exclusive signature for a registered system. this controls the
// components that an entity must not have in order to be added to the
// system
// ===========================================================================
template <class SystemType>
void SystemManager::setExclusiveSignature(
	const Signature& signature
) {
	// get type string for system
	TYPE_STRING type = typeid(System).name();

	// ensure system has been registered before, else throw a warning
	// ensure system has not been registered before, else throw a warning
	if (systems.count(type) == 0) throw Error(
		"Warning: Component type "
		+ std::string(type)
		+ "has already been registered!",
		ErrorType::WARNING
	);

	// sets the standard signature for the specified system
	signatures[type].second = signature;
}
