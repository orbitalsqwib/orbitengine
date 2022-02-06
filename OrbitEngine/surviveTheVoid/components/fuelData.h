// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Fuel Data Struct Specification
// ===========================================================================

#ifndef _STV_COMPONENTS_FUELDATA_H
#define _STV_COMPONENTS_FUELDATA_H

// main definition

// defines the fuel data for an entity
struct FuelData
{
	// members
	float fuel;			// specifies the current amount of boost fuel
	float maxFuel;		// specifies the maximum amount of boost fuel
	float recovery;		// specifies how much fuel is recovered per second

	// convenience constructor
	FuelData(
		const float& _maxFuel	= 2.5f,
		const float& _recovery	= 0.35f
	):
		// members
		fuel		(_maxFuel),
		maxFuel		(_maxFuel),
		recovery	(_recovery)
	{}
};

#endif // !_STV_COMPONENTS_FUELDATA_H