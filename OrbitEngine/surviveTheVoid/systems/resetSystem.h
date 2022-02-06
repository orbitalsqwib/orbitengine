// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Entity Reset System Generic Specification
// ===========================================================================

#ifndef _STV_SYSTEMS_RESETSYSTEM_H
#define _STV_SYSTEMS_RESETSYSTEM_H

// import necessary headers
#include "../../orbitEngine/imports/ecs.h"


// main definition

// handles entity resets for the specified unique entity type component
template <class EntityTypeComponent>
class ResetSystem : public System
{
public:

	// sets the signature for the system
	void setSignature(
		ECSInstance& ecs
	) {
		// register components (if not already registered)
		ecs.registerComponent<EntityTypeComponent>();

		// set system signature
		Signature s;
		s.set(ecs.getTypeEnum<EntityTypeComponent>(), true);
		ecs.setSignature<ResetSystem<EntityTypeComponent>>(s);
	}

	// deletes all relevant entities
	void resetEntities()
	{
		// initialize iterator
		ENTITY_SET::iterator it = entities.begin();

		// while enemy entities still exist
		while (it != entities.end())
		{
			// destroy enemy entity at iterator (first entity)
			ecs->destroyEntity(*it);

			// set iterator to the first entity in the container
			it = entities.begin();
		}
	}

};

#endif // !_STV_SYSTEMS_RESETSYSTEM_H