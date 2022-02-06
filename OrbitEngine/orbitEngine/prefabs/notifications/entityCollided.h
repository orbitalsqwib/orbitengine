// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Entity Collided Notification Specification
// ===========================================================================

#ifndef _ORBIT_PREFABS_ENTITYCOLLIDED_H
#define _ORBIT_PREFABS_ENTITYCOLLIDED_H

// import necessary headers
#include "../../ecs/types.h"
#include "../../collisions/dxvec2.h"
#include <string>

// main definition

struct EntityCollided
{
	// members
	Entity subject;				// the subject of the collision
	Entity target;				// the target of the collision
	std::string subjectTag;		// the subject collider tag for the collision
	std::string targetTag;		// the target collider tag for the collision
	Vec2 cV;					// the collision vector of the collision

	// convenience constructor
	EntityCollided(
		const Entity&	_subject		= ECS_INVALID_ENTITY,
		const Entity&	_target			= ECS_INVALID_ENTITY,
		const char		_subjectTag[32]	= "",
		const char		_targetTag[32]	= "",
		Vec2			_cV				= Vec2()
	) :
		// members
		subject		(_subject),
		target		(_target),
		subjectTag	(_subjectTag),
		targetTag	(_targetTag),
		cV			(_cV)
	{}
};

#endif // !_ORBIT_PREFABS_ENTITYCOLLIDED_H