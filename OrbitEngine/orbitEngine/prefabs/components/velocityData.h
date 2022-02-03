// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngineECS : Velocity Data Component Specification
// ===========================================================================

#ifndef _ORBIT_PREFABS_VELOCITYDATA_H
#define _ORBIT_PREFABS_VELOCITYDATA_H

struct VelocityData
{
	// members
	float dx;		// change in the entity's x position per second
	float dy;		// change in the entity's y position per second

	// convenience constructor
	VelocityData(
		const float& _dx = 0,
		const float& _dy = 0
	):
		// members
		dx	(_dx),
		dy	(_dy)
	{}
};

#endif // !_ORBIT_PREFABS_VELOCITYDATA_H