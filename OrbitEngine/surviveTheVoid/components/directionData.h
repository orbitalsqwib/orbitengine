// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Direction Data Struct Specification
// ===========================================================================

#ifndef _STV_COMPONENTS_DIRECTIONDATA_H
#define _STV_COMPONENTS_DIRECTIONDATA_H

// import necessary headers
#include "../../orbitEngine/imports/commons.h"

// main definition

// defines the direction an entity is moving in
struct DirectionData
{
	// members

	// specifies the rotation of the entity in radians from the direction
	// vector (0, 1).
	float rotation;	

	// default constructor
	DirectionData(float _rotation = 0.0f): rotation(_rotation) {}

};


#endif // !_STV_COMPONENTS_DIRECTIONDATA_H