// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngineECS : Entity Manager Class Implementation
// ===========================================================================
// ACKNOWLEDGEMENT: This Entity Component System was built with reference to a 
// plethora of sources, but most of the inspiration came from this reference:
// https://austinmorlan.com/posts/entity_component_system.
// ===========================================================================

// import specification
#include "entityManager.h"


// ===========================================================================
// constructor
// ===========================================================================
EntityManager::EntityManager():
	
	// members
	nextId		(0),
	recycled	(),
	signatures	()
{}


// methods

// ===========================================================================
// creates and returns a new entity.
// ===========================================================================
Entity EntityManager::createEntity()
{
	// create temporary entity container
	Entity entity = 0;

	// attempt to recycle entities before using a new identifier
	if (!recycled.empty())
	{
		// get entity from front of recyclable queue
		entity = recycled.front();
		
		// prevent the reuse of this id until the entity is destroyed
		recycled.pop();

		// return entity
		return entity;
	}

	// else, attempt to create a new entity
	if (nextId < ECS_MAX_ENTITIES)
	{
		// construct entity from id and initialize generation count to 0. this
		// is possible, because nextId will only be used on the very first
		// generation of an entity. further reuses will only occur when the
		// entity is recycled.

		// since the id is the LOWORD of a DWORD, we can just set entity to
		// nextId and have it update accordingly without any bitwise work.
		entity = nextId;

		// increment next entity
		nextId++;

		// return entity
		return entity;
	}

	// if no recyclables available and all ids have been used, we have hit the
	// max entity count! to be safe, instead of destroying the oldest entity
	// or resizing the signatures array, we'll throw an error here instead
	throw Error("Error: Maximum entity capacity reached!");
}

// ===========================================================================
// destroys the specified entity, and prepares it for reuse
// ===========================================================================
void EntityManager::destroyEntity(
	Entity	entity
) {
	// ensure that entity is valid, else throw a warning
	EntityUtils::guardIsValid(entity);

	// if valid, reset the signature tied to that entity (flips all bits to 0)
	signatures[EntityUtils::getId(entity)].reset();

	// increase entity generation count by one so the next object recieving
	// this id is unique from the object that got recently destroyed
	EntityUtils::incrementGeneration(entity);

	// send entity to recycle queue
	recycled.push(entity);
}


// setters

// ===========================================================================
// sets the signature for the specified entity
// ===========================================================================
void EntityManager::setSignature(
	const Entity&		entity,
	const Signature&	signature
) {
	// ensure that entity is valid, else throw a warning
	EntityUtils::guardIsValid(entity);

	// if valid, update signature for entity
	signatures[EntityUtils::getId(entity)] = signature;
}


// getters

// ===========================================================================
// returns the signature for the specified entity
// ===========================================================================
Signature EntityManager::getSignature(
	const Entity&	entity
) {
	// ensure that entity is valid, else throw a warning
	EntityUtils::guardIsValid(entity);

	// if valid, return copy of signature for entity
	return signatures[EntityUtils::getId(entity)];
}
