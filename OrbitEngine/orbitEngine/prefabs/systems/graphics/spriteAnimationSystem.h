// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngineECS : Sprite Animation System Specification
// ===========================================================================

#ifndef _ORBIT_PREFABS_SPRITEANIMATIONSYSTEM_H
#define _ORBIT_PREFABS_SPRITEANIMATIONSYSTEM_H

// import necessary headers
#include "../../../ecs/ecs.h"
#include "../../../graphics/components.h"
#include "../../../graphics/operators.h"
#include "../../../utils/pointers.h"


// main definition

// handles animations for entities with a sprite data component and an
// animated sprite data component
class SpriteAnimationSystem : public System
{
private:

	// animated sprite operator
	UniquePtr<AnimSpriteOperator> animSpriteOp;

	// initialization flag
	bool initialized;

public:

	// constructor
	SpriteAnimationSystem() : animSpriteOp(), initialized(false) {}

	// initializer
	void initialize(
		GraphicsContext* graphics
	) {
		// initialize sprite operator (deallocated through unique ptr)
		animSpriteOp = new AnimSpriteOperator(graphics);

		// update flag
		initialized = true;
	}

	// sets the signature for the system
	void setSignature(
		ECSInstance& ecs
	) {
		// add animated sprite data component to ecs
		ecs.registerComponent<AnimSpriteData>();

		// set system signature
		Signature s;
		s.set(ecs.getTypeEnum<AnimSpriteData>(), true);
		s.set(ecs.getTypeEnum<SpriteData>(), true);
		ecs.setSignature<SpriteAnimationSystem>(s);
	}

	// update method
	void update(const float& deltaTime)
	{
		// ensure system is initialized, else exit early
		if (!initialized) return;

		// loop through all system entities
		ENTITY_SET::iterator it;
		for (it = entities.begin(); it != entities.end(); it++)
		{
			// update sprite and animation states
			animSpriteOp->updateAnimation(
				*ecs->getComponent<AnimSpriteData>(*it),
				*ecs->getComponent<SpriteData>(*it),
				deltaTime
			);
		}
	}
};

#endif // !_ORBIT_PREFABS_SPRITEANIMATIONSYSTEM_H