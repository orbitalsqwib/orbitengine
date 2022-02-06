// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Blast System Specification
// ===========================================================================

#ifndef _STV_SYSTEMS_BLASTSYSTEM_H
#define _STV_SYSTEMS_BLASTSYSTEM_H

// import necessary headers
#include "../components/blastData.h"
#include "../../orbitEngine/imports/ecs.h"
#include "../../orbitEngine/imports/components.h"
#include "../../orbitEngine/imports/graphics.h"


// main definition

// handles blast entities
class BlastSystem : public System
{
public:

	// sets the signature for the system
	void setSignature(
		ECSInstance& ecs
	) {
		// register components (if not already registered)
		ecs.registerComponent<BlastData>();
		ecs.registerComponent<SpriteData>();
		ecs.registerComponent<ColliderData>();

		// set system signature
		Signature s;
		s.set(ecs.getTypeEnum<BlastData>(), true);
		s.set(ecs.getTypeEnum<SpriteData>(), true);
		s.set(ecs.getTypeEnum<ColliderData>(), true);
		ecs.setSignature<BlastSystem>(s);
	}

	// destroys blast entities which have expired, and update blast timers
	void updateBlasts(const float& deltaTime)
	{
		// initialize iterator
		ENTITY_SET::iterator it;

		// initialize destroy set
		ENTITY_SET toDestroy;

		// loop through all relevant entities
		for (it = entities.begin(); it != entities.end(); it++)
		{
			// get components for entity
			BlastData* pBlast = ecs->getComponent<BlastData>(*it);
			SpriteData* pSprite = ecs->getComponent<SpriteData>(*it);
			ColliderData* pCol = ecs->getComponent<ColliderData>(*it);

			// ensure all components exist, else skip iteration
			if (!pBlast || !pSprite || !pCol) continue;

			// decrease blast life timer
			pBlast->timeLeft -= deltaTime;

			// if time < 0, queue blast to be destroyed
			if (pBlast->timeLeft <= 0)
			{
				// queue blast to be destroyed
				toDestroy.insert(*it);
			}

			// else, update sprite and collider for blast
			{
				// calculate time scale
				float timeScale = pBlast->timeLeft / pBlast->blastTime;

				// update sprite offset to keep image centered
				pSprite->relX = pBlast->blastRadius * timeScale;
				pSprite->relY = pBlast->blastRadius * timeScale;

				// update collider position to keep image centered
				pCol->setPos(
					pSprite->x + pSprite->relX,
					pSprite->y + pSprite->relY
				);

				// update sprite scale
				pSprite->scale = pBlast->spriteScale * (1 - timeScale);

				// update collider scale
				pCol->setScale(1 - timeScale);
			}
		}

		// loop through destroy set
		for (it = toDestroy.begin(); it != toDestroy.end(); it++)
		{
			// destroy blast entity
			ecs->destroyEntity(*it);
		}
	}

};

#endif // !_STV_SYSTEMS_BLASTSYSTEM_H