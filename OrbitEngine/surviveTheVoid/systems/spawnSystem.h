// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Spawn System Specification
// ===========================================================================

#ifndef _STV_SYSTEMS_SPAWNSYSTEM_H
#define _STV_SYSTEMS_SPAWNSYSTEM_H

// import necessary headers
#include "../archetypes/IArchetype.h"
#include "../components/playerData.h"
#include "../archetypes/enemyArchetype.h"
#include "../../orbitEngine/imports/ecs.h"
#include "../../orbitEngine/imports/components.h"
#include "../../orbitEngine/imports/commons.h"
#include <time.h>


// main definition

// handles enemy resets
class SpawnSystem : public System
{
public:

	// methods

	// sets the signature for the system
	void setSignature(
		ECSInstance& ecs
	) {
		// register components (if not already registered)
		ecs.registerComponent<PlayerData>();
		ecs.registerComponent<PositionData>();

		// set system signature
		Signature s;
		s.set(ecs.getTypeEnum<PlayerData>(), true);
		s.set(ecs.getTypeEnum<PositionData>(), true);
		ecs.setSignature<SpawnSystem>(s);
	}

	// spawns an enemy randomly within the window, but not around players
	Entity spawn(
		IArchetype*		pArchetype,
		const RECT&		bounds, 
		const float&	protectedRadius
	) {
		// seed random function
		srand(static_cast<UINT>(time(NULL)) + rand());

		// initialize spawn pos variables (center pos)
		int x, y;

		// calculate ranges
		int xRange = (bounds.right - DIAMETER_ENEMY - bounds.left);
		int yRange = (bounds.bottom - DIAMETER_ENEMY - bounds.top);

		// calculate protected spawn radius squared
		float protectedR2 = protectedRadius * protectedRadius;

		// attempt to find valid spawn location
		while (true)
		{
			// initialize loop exit flag
			bool spawnIsValid = true;

			// choose a valid spawn location randomly within bounds
			x = rand() % xRange + bounds.left + RADIUS_ENEMY;
			y = rand() % yRange + bounds.top + RADIUS_ENEMY;

			// initialize iterator
			ENTITY_SET::iterator it;

			// loop through all players
			for (it = entities.begin(); it != entities.end(); it++)
			{
				// get position data for player
				if (PositionData* pPos = ecs->getComponent<PositionData>(*it))
				{
					// calculate delta x/y from center to spawn location
					float dx = (pPos->x + pPos->width / 2) - x;
					float dy = (pPos->y + pPos->height / 2) - y;

					// check if distance from spawn to center falls within
					// the protected radius: dx^2 + dy^2 < protectedR^2
					if ((dx * dx) + (dy * dy) <= protectedR2)
					{
						// spawn is invalid, skip remaining iterations
						// and try a new spawn location
						spawnIsValid = false;
						break;
					}
				}
			}

			// spawn is valid, break out of while loop
			if(spawnIsValid) break;
		}

		// spawn new enemy at determined spawn location (tl -> center), then
		// return the resultant entity
		return pArchetype->spawn(
			static_cast<float>(x - RADIUS_ENEMY), 
			static_cast<float>(y - RADIUS_ENEMY)
		);
	}

};

#endif // !_STV_SYSTEMS_SPAWNSYSTEM_H