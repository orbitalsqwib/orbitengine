// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Boost Animation System Specification
// ===========================================================================

#ifndef _STV_SYSTEMS_BOOSTANIMSYSTEM_H
#define _STV_SYSTEMS_BOOSTANIMSYSTEM_H

// import necessary headers
#include "../components/boostData.h"
#include "../components/playerData.h"
#include "../../orbitEngine/imports/ecs.h"
#include "../../orbitEngine/imports/components.h"
#include "../../orbitEngine/imports/graphics.h"


// main definition

// handles the boost mechanic
class BoostAnimSystem : public System
{
private:

	// local sprite animation operator
	UniquePtr<AnimSpriteOperator> pAnimOp;

public:

	// constructor
	BoostAnimSystem() : pAnimOp(nullptr) {}

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
		ecs.registerComponent<BoostData>();
		ecs.registerComponent<SpriteData>();
		ecs.registerComponent<PlayerData>();

		// set system signature
		Signature s;
		s.set(ecs.getTypeEnum<BoostData>(), true);
		s.set(ecs.getTypeEnum<SpriteData>(), true);
		s.set(ecs.getTypeEnum<PlayerData>(), true);
		ecs.setSignature<BoostAnimSystem>(s);
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
			BoostData* pBoost = ecs->getComponent<BoostData>(*it);
			SpriteData* pSprite = ecs->getComponent<SpriteData>(*it);

			// ensure all components / operators exist, else skip iteration
			if (!pBoost || !pSprite || !pAnimOp) continue;

			// get current boost fuel percentage
			float fuelP = pBoost->fuel / pBoost->maxFuel;

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

#endif // !_STV_SYSTEMS_BOOSTANIMSYSTEM_H