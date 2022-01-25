// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngineECS : Entity Manager Class Specification
// ===========================================================================
// ACKNOWLEDGEMENT: This Entity Component System was built with reference to a 
// plethora of sources, but most of the inspiration came from this reference:
// https://austinmorlan.com/posts/entity_component_system.
// ===========================================================================

#ifndef _ORBIT_ECS_ENTITYMANAGER_H
#define _ORBIT_ECS_ENTITYMANAGER_H

// import necessary headers
#include "types.h"
#include "../error.h"
#include <queue>
#include <array>


// main definition

// manager class responsible for generating and recycling entities, as well as
// recording each entity's component signature for the entity-component-system
class EntityManager
{
private:

	// members

	// specifies the next available entity id, if no reusable entities are
	// currently available. this value is only valid up to MAX_ENTITIES - 1!
	// (nextId: 0 <= nextId < MAX_ENTITIES, nextId E I)
	WORD nextId;

	// queue of reusable entity ids
	std::queue<Entity> recycled;

	// array of entityid : signature pairs - this creates a signature bitfield 
	// for each possible entity in the ECS, where the i-th signature in the
	// array is for the i-th entity. assuming each bitfield has 256 bits for
	// 256 components (32 byte signature), and there are 4096 possible
	// entities in the system, this means that this array will (theoretically)
	// take up 131,072 bytes of space! (slightly over 131 kilobytes). this
	// sacrifices memory for speed, since this has O(1) retrieval and lives in
	// contiguous memory (faster than cache-missing on an unordered_map).
	std::array<Signature, ECS_MAX_ENTITIES> signatures;

public:

	// constructor
	EntityManager();


	// methods - all methods, setters and getters are O(1)!

	// creates and returns a new entity.
	Entity createEntity();

	// destroys the specified entity, and prepares it for reuse
	void destroyEntity(Entity entity);

	
	// setters

	// sets the signature for the specified entity
	void setSignature(const Entity& entity, const Signature& signature);


	// getters

	// returns the signature for the specified entity
	Signature getSignature(const Entity& entity);

};

#endif // !_ORBIT_ECS_ENTITYMANAGER_H