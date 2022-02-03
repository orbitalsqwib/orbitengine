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
	Entity subject;		// the subject of the collision
	Entity target;		// the target of the collision
	std::string tag;	// the target collider tag for the collision
	Vec2 cV;			// the collision vector of the collision

	// convenience constructor
	EntityCollided(
		const Entity&	_subject	= ECS_INVALID_ENTITY,
		const Entity&	_target		= ECS_INVALID_ENTITY,
		const char		_tag[32]	= "",
		const Vec2&		_cV			= Vec2()
	) :
		// members
		subject	(_subject),
		target	(_target),
		tag		(_tag),
		cV		(_cV)
	{}
};

#endif // !_ORBIT_PREFABS_ENTITYCOLLIDED_H