// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Render Systems Class Specification
// ===========================================================================

#ifndef _ORBIT_PREFABS_RENDERSYSTEMS_H
#define _ORBIT_PREFABS_RENDERSYSTEMS_H

// import necessary headers
#include "graphics/shapeRenderSystem.h"
#include "graphics/spriteAnimationSystem.h"
#include "graphics/spriteRenderSystem.h"
#include "graphics/textRenderSystem.h"
#include "../../ecs/ecs.h"


// main definition

// defines a group of rendering systems, and is responsible for registering
// and binding internal rendering systems to the ecs. A scene should import
// and use this group of systems to handle rendering-related work.
class RenderSystems
{
private:

	// members

	// systems - each system is bound to the group with a non-owning pointer 
	// to the system instances.

	ShapeRenderSystem*		pShapeRenderSystem;
	SpriteRenderSystem*		pSpriteRenderSystem;
	SpriteAnimationSystem*	pSpriteAnimationSystem;
	TextRenderSystem*		pTextRenderSystem;

	// stores a local copy of the graphics context
	GraphicsContext* graphics;

public:

	// constructor
	RenderSystems();


	// methods

	// registers and initializes internal rendering systems, saving pointers
	// to each system so operations may be carried out during the update loop.
	void initialize(
		ECSInstance&		ecs,
		GraphicsContext*	graphics
	);

	// calls each render system's render methods in order, and also updates
	// animations according to the elapsed frame time. should be called every
	// frame.
	void render(const float& deltaTime);

};

#endif // !_ORBIT_PREFABS_RENDERSYSTEMS_H