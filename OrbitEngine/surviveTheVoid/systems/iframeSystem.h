// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : IFrame System Specification
// ===========================================================================

#ifndef _STV_SYSTEMS_IFRAMESYSTEM_H
#define _STV_SYSTEMS_IFRAMESYSTEM_H

// import necessary headers
#include "../components/playerData.h"
#include "../components/iframeData.h"
#include "../../orbitEngine/imports/ecs.h"
#include "../../orbitEngine/imports/components.h"
#include "../../orbitEngine/imports/graphics.h"


// main definition

// handles blast entities
class IFrameSystem : public System
{
private:

	// members

	// local sprite animation operator
	UniquePtr<AnimSpriteOperator> pAnimOp;

public:

	// constructor
	IFrameSystem(): pAnimOp(nullptr) {}

	// initializer
	void initalize(
		GraphicsContext& _graphicsContext
	) {
		// build new sprite animation operator
		pAnimOp = new AnimSpriteOperator(&_graphicsContext);
	}

	// sets the signature for the system
	void setSignature(
		ECSInstance& ecs
	) {
		// register components (if not already registered)
		ecs.registerComponent<IFrameData>();
		ecs.registerComponent<SpriteData>();
		ecs.registerComponent<PlayerData>();

		// set system signature
		Signature s;
		s.set(ecs.getTypeEnum<IFrameData>(), true);
		s.set(ecs.getTypeEnum<SpriteData>(), true);
		s.set(ecs.getTypeEnum<PlayerData>(), true);
		ecs.setSignature<IFrameSystem>(s);
	}

	// update iframe data and sync sprite to match current iframe
	void updateIFrames(const float& deltaTime)
	{
		// initialize delete set
		ENTITY_SET deleteSet;

		// initialize iterator
		ENTITY_SET::iterator it;

		// loop through relevant entities
		for (it = entities.begin(); it != entities.end(); it++)
		{
			// retrieve components for entity
			IFrameData* pIFrame = ecs->getComponent<IFrameData>(*it);
			SpriteData* pSprite = ecs->getComponent<SpriteData>(*it);

			// ensure all components exist, else skip iteration
			if (!pIFrame || !pSprite) continue;

			// update iframe time
			pIFrame->timeLeft -= deltaTime;

			// if iframe expired, mark it for deletion
			if (pIFrame->timeLeft <= 0)
			{
				deleteSet.insert(*it);
			}

			// else, update sprite to reflect iframe state
			else
			{
				// select 7th frame of player ship sprite
				if (pAnimOp) pAnimOp->updateSpriteForAnimation(
					AnimSpriteData(0, 0, 7, 0, 0, 5),
					*pSprite
				);
			}
		}

		// loop through delete set
		for (it = deleteSet.begin(); it != deleteSet.end(); it++)
		{
			// delete iframe component for entity
			ecs->removeComponent<IFrameData>(*it);
		}
	}

};

#endif // !_STV_SYSTEMS_IFRAMESYSTEM_H