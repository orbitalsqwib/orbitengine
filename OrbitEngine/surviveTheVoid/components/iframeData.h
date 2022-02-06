// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : IFrame Data Struct Specification
// ===========================================================================

#ifndef _STV_COMPONENTS_IFRAMEDATA_H
#define _STV_COMPONENTS_IFRAMEDATA_H

// main definition

// defines the data for an entity's iframe
struct IFrameData
{
	// members
	float timeLeft;		// remaining time until the iframe expires

	// convenience constructor
	IFrameData(
		const float& _iframeTime = 0.5f
	):
		// members
		timeLeft	(_iframeTime)
	{}
};

#endif // !_STV_COMPONENTS_IFRAMEDATA_H