// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Move Command Specification
// ===========================================================================

#ifndef _ORBIT_PREFABS_MOVECOMMAND_H
#define _ORBIT_PREFABS_MOVECOMMAND_H

// import necessary headers
#include "../../ecs/types.h"


// informs transform systems to update the position data for all entity
// components that they are responsible for.
struct MoveCommand
{
	// members
	Entity entity;	// the target entity to move
	float x;		// the update in the x-position of the entity
	float y;		// the update in the y-position of the entity

	// specifies if updates made are absolute or relative to current values.
	bool relative;

	// default constructor
	MoveCommand():

		// members
		entity		(ECS_INVALID_ENTITY),
		x			(0),
		y			(0),
		relative	(false)
	{}

	// convenience constructor
	MoveCommand(
		const Entity& _entity,
		const float&  _x,
		const float&  _y,
		const bool&	  _relative	= false
	):
		// members
		entity		(_entity),
		x			(_x),
		y			(_y),
		relative	(_relative)
	{}
};

// defines a separate command type which must be translated into a proper move
// command by a verification system such as a collision checking system before
// being applied to the actual transform systems.
struct MoveRequest : public MoveCommand {};

#endif // !_ORBIT_PREFABS_MOVECOMMAND_H