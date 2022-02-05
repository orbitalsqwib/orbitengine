// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Mass Data Struct Specification
// ===========================================================================

#ifndef _STV_COMPONENTS_MASSDATA_H
#define _STV_COMPONENTS_MASSDATA_H

// main definition

// defines the mass for an entity
struct MassData
{
	// members
	float mass;	// specifies the mass of the entity

	// convenience constructor
	MassData(
		const float& _mass = 1.0f
	):
		// members
		mass	(_mass)
	{}
};

#endif // !_STV_COMPONENTS_MASSDATA_H