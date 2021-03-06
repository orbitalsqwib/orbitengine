// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Boost System Specification
// ===========================================================================

#ifndef _STV_SYSTEMS_BOOSTSYSTEM_H
#define _STV_SYSTEMS_BOOSTSYSTEM_H

// import necessary headers
#include "../components/fuelData.h"
#include "../components/boostData.h"
#include "../components/thrustData.h"
#include "../../orbitEngine/imports/ecs.h"
#include "../../orbitEngine/imports/components.h"


// main definition

// handles the boost mechanic
class BoostSystem : public System
{
public:

	// sets the signature for the system
	void setSignature(
		ECSInstance& ecs
	) {
		// register components (if not already registered)
		ecs.registerComponent<BoostData>();
		ecs.registerComponent<FuelData>();
		ecs.registerComponent<ThrustData>();

		// set system signature
		Signature s;
		s.set(ecs.getTypeEnum<BoostData>(), true);
		s.set(ecs.getTypeEnum<FuelData>(), true);
		s.set(ecs.getTypeEnum<ThrustData>(), true);
		ecs.setSignature<BoostSystem>(s);
	}

	// applies boost to thrust
	void applyBoost(const float& _deltaTime)
	{
		// initialize iterator
		ENTITY_SET::iterator it;

		// loop through all relevant entities
		for (it = entities.begin(); it != entities.end(); it++)
		{
			// get components for entity
			BoostData* pBoost = ecs->getComponent<BoostData>(*it);
			ThrustData* pThrust = ecs->getComponent<ThrustData>(*it);
			FuelData* pFuel = ecs->getComponent<FuelData>(*it);

			// ensure all components exist, else skip to next iteration
			if (!pBoost || !pThrust) continue;

			// recover fuel for frame up till maxFuel
			pFuel->fuel = min(
				pFuel->fuel + pFuel->recovery * _deltaTime,
				pFuel->maxFuel
			);

			// if boost is not active or out of fuel, skip to next iteration
			if (!pBoost->active || pFuel->fuel <= 0) continue;

			// else, apply boost to thrust
			pThrust->bonusThrust 
				+= pBoost->speedUp 
					? pBoost->fwdBoost 
					: -pBoost->revBoost;

			// consume fuel for frame
			pFuel->fuel = max(pFuel->fuel - _deltaTime, 0);
		}
	}

};

#endif // !_STV_SYSTEMS_BOOSTSYSTEM_H