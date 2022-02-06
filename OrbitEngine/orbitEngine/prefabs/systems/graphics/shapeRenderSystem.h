// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Shape Rendering System Specification
// ===========================================================================

#ifndef _ORBIT_PREFABS_SHAPERENDERSYSTEM_H
#define _ORBIT_PREFABS_SHAPERENDERSYSTEM_H

// import necessary headers
#include "../../../ecs/ecs.h"
#include "../../../graphics/components.h"
#include "../../../graphics/operators.h"
#include "../../../utils/pointers.h"


// main definition

// renders entities with a shape data component
class ShapeRenderSystem : public System
{
private:

	// shape operator
	UniquePtr<ShapeOperator> shapeOp;

	// initialization flag
	bool initialized;

public:

	// constructor
	ShapeRenderSystem() : shapeOp(nullptr), initialized(false) {}

	// initializer
	void initialize(
		GraphicsContext*	graphics
	) {
		// initialize sprite operator (deallocated through unique ptr)
		shapeOp = new ShapeOperator(graphics);

		// update flag
		initialized = true;
	}

	// sets the signature for the system
	void setSignature(
		ECSInstance& ecs
	) {
		// add shape data component to ecs
		ecs.registerComponent<ShapeData>();

		// set system signature
		Signature s;
		s.set(ecs.getTypeEnum<ShapeData>(), true);
		ecs.setSignature<ShapeRenderSystem>(s);
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
			// render text
			shapeOp->render(*ecs->getComponent<ShapeData>(*it));
		}
	}
};

#endif // !_ORBIT_PREFABS_SHAPERENDERSYSTEM_H