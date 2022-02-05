// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Boost Data Struct Specification
// ===========================================================================

#ifndef _STV_COMPONENTS_BOOSTDATA_H
#define _STV_COMPONENTS_BOOSTDATA_H

// main definition

// defines the boost data for an entity - 1 unit of fuel = 1s of boost
struct BoostData
{
	// members
	float fuel;			// specifies the current amount of boost fuel
	float maxFuel;		// specifies the maximum amount of boost fuel
	float recovery;		// specifies how much fuel is recovered per second
	float fwdBoost;		// specifies the bonus forward thrust from boost
	float revBoost;		// specifies the bonus reverse thrust from boost
	bool speedUp;		// if true, boost is used to speed up, else slow down
	bool active;		// if true, fuel is consumed to boost the entity

	// convenience constructor
	BoostData(
		const float& _maxFuel	= 2.5f,
		const float& _recovery	= 0.35f,
		const float& _fwdBoost	= 50.0f,
		const float& _revBoost	= 15.0f
	):
		// members
		fuel		(_maxFuel),
		maxFuel		(_maxFuel),
		recovery	(_recovery),
		fwdBoost	(_fwdBoost),
		revBoost	(_revBoost),
		speedUp		(true),
		active		(false)
	{}
};

#endif // !_STV_COMPONENTS_BOOSTDATA_H