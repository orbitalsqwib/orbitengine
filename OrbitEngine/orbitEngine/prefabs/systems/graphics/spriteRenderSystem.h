// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Sprite Rendering System Specification
// ===========================================================================

#ifndef _ORBIT_PREFABS_SPRITERENDERSYSTEM_H
#define _ORBIT_PREFABS_SPRITERENDERSYSTEM_H

// import necessary headers
#include "../../../ecs/ecs.h"
#include "../../../graphics/components.h"
#include "../../../graphics/operators.h"
#include "../../../utils/pointers.h"


// main definition

// renders entities with a sprite data component
class SpriteRenderSystem : public System
{
private:

	// sprite operator
	UniquePtr<SpriteOperator> spriteOp;

	// initialization flag
	bool initialized;

public:

	// constructor
	SpriteRenderSystem(): spriteOp(), initialized(false) {}

	// initializer
	void initialize(
		GraphicsContext* graphics
	) {
		// initialize sprite operator (deallocated through unique ptr)
		spriteOp = new SpriteOperator(graphics);

		// update flag
		initialized = true;
	}

	// sets the signature for the system
	void setSignature(
		ECSInstance& ecs
	) {
		// add sprite data component to ecs
		ecs.registerComponent<SpriteData>();

		// set system signature
		Signature s;
		s.set(ecs.getTypeEnum<SpriteData>(), true);
		ecs.setSignature<SpriteRenderSystem>(s);
	}

	// render method
	void render()
	{
		// ensure system is initialized, else exit early
		if (!initialized) return;

		// loop through all system entities
		ENTITY_SET::iterator it;
		for (it = entities.begin(); it != entities.end(); it++)
		{
			// attempt to get sprite for entity
			if (SpriteData* pSprite = ecs->getComponent<SpriteData>(*it))
			{
				// render sprite
				spriteOp->render(*pSprite);
			}
		}
	}
};

#endif // !_ORBIT_PREFABS_SPRITERENDERSYSTEM_H