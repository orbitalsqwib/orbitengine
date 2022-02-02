// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Rotate Command Specification
// ===========================================================================

#ifndef _ORBIT_PREFABS_ROTATECOMMAND_H
#define _ORBIT_PREFABS_ROTATECOMMAND_H

// informs transform systems to update the rotation data for all entity
// components that they are responsible for.
struct RotateCommand
{
	// members
	Entity entity;	// the target entity to move
	float angle;	// the update in the rotation of the entity (cw, radians)

	// specifies if updates made are absolute or relative to current values.
	bool relative;

	// default constructor
	RotateCommand():

		// members
		entity		(ECS_INVALID_ENTITY),
		angle		(0),
		relative	(false)
	{}

	// convenience constructor
	RotateCommand(
		const Entity& _entity,
		const float&  _angle	= 0,
		const bool&	  _relative	= false
	):
		// members
		entity		(_entity),
		angle		(_angle),
		relative	(_relative)
	{}

};

#endif // !_ORBIT_PREFABS_ROTATECOMMAND_H