// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Fuel Animation System Specification
// ===========================================================================

#ifndef _STV_SYSTEMS_FUELANIMSYSTEM_H
#define _STV_SYSTEMS_FUELANIMSYSTEM_H

// import necessary headers
#include "../components/fuelData.h"
#include "../components/playerData.h"
#include "../../orbitEngine/imports/ecs.h"
#include "../../orbitEngine/imports/components.h"
#include "../../orbitEngine/imports/graphics.h"


// main definition

// updates player sprite according to the amount of fuel they have
class FuelAnimSystem : public System
{
private:

	// local sprite animation operator
	UniquePtr<AnimSpriteOperator> pAnimOp;

public:

	// constructor
	FuelAnimSystem() : pAnimOp(nullptr) {}

	// initializer
	void initialize(GraphicsContext& _graphics)
	{
		// build animation operator
		pAnimOp = new AnimSpriteOperator(&_graphics);
	}

	// sets the signature for the system
	void setSignature(
		ECSInstance& ecs
	) {
		// register components (if not already registered)
		ecs.registerComponent<FuelData>();
		ecs.registerComponent<SpriteData>();
		ecs.registerComponent<PlayerData>();

		// set system signature
		Signature s;
		s.set(ecs.getTypeEnum<FuelData>(), true);
		s.set(ecs.getTypeEnum<SpriteData>(), true);
		s.set(ecs.getTypeEnum<PlayerData>(), true);
		ecs.setSignature<FuelAnimSystem>(s);
	}

	// synchronizes player sprite for current boost value
	void updatePlayerSprite()
	{
		// initialize iterator
		ENTITY_SET::iterator it;

		// loop through all relevant entities
		for (it = entities.begin(); it != entities.end(); it++)
		{
			// get components for entity
			FuelData* pFuel = ecs->getComponent<FuelData>(*it);
			SpriteData* pSprite = ecs->getComponent<SpriteData>(*it);

			// ensure all components / operators exist, else skip iteration
			if (!pFuel || !pSprite || !pAnimOp) continue;

			// get current boost fuel percentage
			float fuelP = pFuel->fuel / pFuel->maxFuel;

			// map fuel percentage to 0 <= fp <= 4
			int frame = int(floor(fuelP * 4));

			// update sprite to appropriate frame
			pAnimOp->updateSpriteForAnimation(
				AnimSpriteData(0, 0, frame, 0, 0, 5),
				*pSprite
			);
		}
	}

};

#endif // !_STV_SYSTEMS_FUELANIMSYSTEM_H