// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngineECS : Entity Type / Utils Specification
// ===========================================================================
// ACKNOWLEDGEMENT: This Entity Component System was built with reference to a 
// plethora of sources, but most of the inspiration came from this reference:
// https://austinmorlan.com/posts/entity_component_system.
// ===========================================================================

#ifndef _ORBIT_ECS_ENTITY_H
#define _ORBIT_ECS_ENTITY_H

// import windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "../../error.h"
#include <assert.h>


// main definitions

// represents an entity, and is also its own unique identifier. the LOWORD of
// the entity represents its id, while the HIWORD represents its generation
// count. this gives us 2^16 possible unique entities living at any point of
// time, as well as 2^16 possible generations for each entity before rollover
// occurs.
typedef DWORD Entity;
typedef WORD EntityId;
typedef WORD EntityGen;

// define a maximum entity count, which limits the number of entities that can
// exist at any one point of time. when this limit is hit, the system should
// either compensate for it or throw an error. theoretically, the max limit
// for this value is 65,535 as the second half of the entity is used for the
// generation value.
const EntityId ECS_MAX_ENTITIES = 4096;

// the entityId value (0xffff) is reserved as a marker for invalid entity ids!
const EntityId ECS_INVALID_ENTITY = MAXWORD;

// utility class that holds a couple of convenience functions pertaining to
// entity id management
struct EntityUtils
{
	// increments the generation of an entity id by one - this is done when
	// an entity dies, so the id can be rolled over without causing bugs (e.g:
	// a turret with the id 100 dies, but then another entity is created with
	// the same id. thus, to a system checking an entity, the turret seems to
	// have zombified and remains alive (but may even be a HUD element)!)
	static void incrementGeneration(Entity& e) {
		e = LOWORD(e) | ((HIWORD(e) + 1) << 16);
	}

	// increments the id of an entity by one.
	static void incrementId(Entity& e) {
		e = (LOWORD(e) + 1) | (HIWORD(e) << 16);
	}

	// checks if the entity id is valid for the current max entity count. this
	// cannot rule out signed values as the sign bit occupies the MSB, which
	// would lie in the high-order word of the entity (generation count).
	// verifies the rule (Id(e) < MAX_ENTITIES && Id(e) != 0xffff).
	static bool isValid(const Entity& e) 
	{ 
		// get entity id
		EntityId id = getId(e);

		// check rules and return result
		return id < ECS_MAX_ENTITIES && id != ECS_INVALID_ENTITY;
	}

	// convenience wrapper around isValid() to automatically throw a exception
	// if the entity id is invalid. after this statement is invoked, e is
	// guaranteed to be valid according to the isValid() rules.
	static void guardIsValid(
		const Entity&	e,
		const bool&		warnOnly = true
	) {
		// get prefix
		std::string prefix = warnOnly ? "Warning" : "Error";

		// throw exception
		if (!isValid(e)) throw Error(
			prefix + " Entity ID: " + std::to_string(e) + " is not valid!",
			warnOnly ? ErrorType::WARNING : ErrorType::FATAL_ERROR
		);
	}

	// assertion variant of guardIsValid(). this is not run on release, so be
	// cautious of how this method is used!
	static void assertIsValid(
		const Entity&	e
	) {
		// assert expression is valid
		assert(isValid(e) && "Entity ID is not valid!");
	}

	// returns the generation count of an entity
	static EntityGen getGeneration(const Entity& e) { return HIWORD(e); }

	// returns the id of an entity
	static EntityId getId(const Entity& e) { return LOWORD(e); }
};

#endif // !_ORBIT_ECS_ENTITY_H