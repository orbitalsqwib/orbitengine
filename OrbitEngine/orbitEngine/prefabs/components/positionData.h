// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngineECS : Position Data Component Specification
// ===========================================================================

#ifndef _ORBIT_ECS_POSITIONDATA_H
#define _ORBIT_ECS_POSITIONDATA_H

struct PositionData
{
	// members
	float x;		// x-coordinate of the top-left corner of the entity
	float y;		// y-coordinate of the top-left corner of the entity
	float width;	// records the width of the entity, to get center pos
	float height;	// records the height of the entity, to get center pos

	// convenience constructor - note that if the width and height are left as
	// 0, the "center" of the entity will be the top-left corner of the entity
	PositionData(
		const float& _x			= 0,
		const float& _y			= 0,
		const float& _width		= 0,
		const float& _height	= 0
	):
		// members
		x		(_x),
		y		(_y),
		width	(_width),
		height	(_height)
	{}
};

#endif // !_ORBIT_ECS_POSITIONCOMPONENT_H