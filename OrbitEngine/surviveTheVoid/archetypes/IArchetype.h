// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Archetype Interface Specification
// ===========================================================================

#ifndef _STV_ARCHETYPES_IARCHETYPE_H
#define _STV_ARCHETYPES_IARCHETYPE_H


// main definition

// defines an interface for archetypes
class IArchetype
{
public:

	// methods

	// should spawn an entity at the specified center coordinates and return
	// the newly created entity for external use
	virtual Entity spawn(
		const float& x,
		const float& y
	) = 0;

	// should return the entity's width at spawn time
	virtual float getWidth() = 0;

	// should return the entity's height at spawn time
	virtual float getHeight() = 0;

};

#endif // !_STV_ARCHETYPES_IARCHETYPE_H