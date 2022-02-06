// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Thrust Data Struct Specification
// ===========================================================================

#ifndef _STV_COMPONENTS_THRUSTDATA_H
#define _STV_COMPONENTS_THRUSTDATA_H


// main definition

// defines thrust data for an entity
struct ThrustData
{
	// members
	float baseThrust;	// specifies the base forward thrust of the entity
	float bonusThrust;	// specifies additional thrust added to the entity
	float thrustScale;	// scales thrust and bonus thrust for final thrust
	bool active;		// specifies if the thrust force is active

	// convenience constructor
	ThrustData(
		const float& _base	= 50.0f,
		const float& _bonus	= 0.0f,
		const float& _scale = 1.0f,
		const bool& _active	= true
	):
		// members
		baseThrust	(_base),
		bonusThrust	(_bonus),
		thrustScale	(_scale),
		active		(_active)
	{}
};


#endif // !_STV_COMPONENTS_THRUSTDATA_H