// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Tracking Data Struct Specification
// ===========================================================================

#ifndef _STV_COMPONENTS_TRACKINGDATA_H
#define _STV_COMPONENTS_TRACKINGDATA_H

// import necessary headers
#include "../../orbitEngine/imports/ecs.h"


// main definition

// defines a entity to be tracked by the current entity. the current entity 
// will attempt to face the tracked entity.
struct TrackingData
{
	// members
	Entity tracked;	// specifies the tracked entity

	// convenience constructor
	TrackingData(
		const Entity& _tracked = ECS_INVALID_ENTITY
	):
		// members
		tracked	(_tracked)
	{}
};


#endif // !_STV_COMPONENTS_TRACKINGDATA_H