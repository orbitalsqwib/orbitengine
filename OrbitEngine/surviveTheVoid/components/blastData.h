// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Blast Data Struct Specification
// ===========================================================================

#ifndef _STV_COMPONENTS_BLASTDATA_H
#define _STV_COMPONENTS_BLASTDATA_H

// main definition

// defines the data for a bomb blast
struct BlastData
{
	// members
	float blastTime;	// total blast time
	float timeLeft;		// remaining time until the blast expires
	float blastRadius;	// radius of the blast
	float spriteScale;	// base sprite scaling

	// convenience constructor
	BlastData(
		const float& _blastTime		= 0.5f,
		const float& _blastRadius	= 128,
		const float& _spriteScale	= 1.0f
	) :
		// members
		blastTime	(_blastTime),
		timeLeft	(_blastTime),
		blastRadius	(_blastRadius),
		spriteScale	(_spriteScale)
	{}
};

#endif // !_STV_COMPONENTS_BLASTDATA_H