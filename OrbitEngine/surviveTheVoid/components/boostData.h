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
	float fwdBoost;		// specifies the bonus forward thrust from boost
	float revBoost;		// specifies the bonus reverse thrust from boost
	bool speedUp;		// if true, boost is used to speed up, else slow down
	bool active;		// if true, fuel is consumed to boost the entity

	// convenience constructor
	BoostData(
		const float& _fwdBoost	= 50.0f,
		const float& _revBoost	= 15.0f
	):
		// members
		fwdBoost	(_fwdBoost),
		revBoost	(_revBoost),
		speedUp		(true),
		active		(false)
	{}
};

#endif // !_STV_COMPONENTS_BOOSTDATA_H