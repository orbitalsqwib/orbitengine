// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Text Rendering System Specification
// ===========================================================================

#ifndef _ORBIT_PREFABS_TEXTRENDERSYSTEM_H
#define _ORBIT_PREFABS_TEXTRENDERSYSTEM_H

// import necessary headers
#include "../../../ecs/ecs.h"
#include "../../../graphics/components.h"
#include "../../../graphics/operators.h"
#include "../../../utils/pointers.h"


// main definition

// renders entities with a text data component
class TextRenderSystem : public System
{
private:

	// text operator
	UniquePtr<TextOperator> textOp;

	// initialization flag
	bool initialized;

public:

	// constructor
	TextRenderSystem() : textOp(), initialized(false) {}

	// initializer
	void initialize(
		GraphicsContext* graphics
	) {
		// initialize sprite operator (deallocated through unique ptr)
		textOp = new TextOperator(graphics);

		// update flag
		initialized = true;
	}

	// sets the signature for the system
	void setSignature(
		ECSInstance& ecs
	) {
		// add text data component to ecs
		ecs.registerComponent<TextData>();

		// set system signature
		Signature s;
		s.set(ecs.getTypeEnum<TextData>(), true);
		ecs.setSignature<TextRenderSystem>(s);
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
			textOp->render(*ecs->getComponent<TextData>(*it));
		}
	}
};

#endif // !_ORBIT_PREFABS_TEXTRENDERSYSTEM_H