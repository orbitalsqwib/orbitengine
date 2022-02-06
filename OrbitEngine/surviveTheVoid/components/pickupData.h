// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Pickup Data Struct Specification
// ===========================================================================

#ifndef _STV_COMPONENTS_PICKUPDATA_H
#define _STV_COMPONENTS_PICKUPDATA_H

// pickup types
enum class PickupTypes
{
	BOMB
};


// main definition

// defines the data for a pickup entity
struct PickupData
{
	// members
	PickupTypes type;	// dictates the type of pickup

	// convenience constructor
	PickupData(
		const PickupTypes& _type = PickupTypes::BOMB
	):
		// members
		type	(_type)
	{}
};

#endif // !_STV_COMPONENTS_PICKUPDATA_H