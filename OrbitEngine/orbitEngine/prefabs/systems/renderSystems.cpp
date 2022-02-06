// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Render Systems Class Implementation
// ===========================================================================

// import specification
#include "renderSystems.h"


// ===========================================================================
// constructor
// ===========================================================================
RenderSystems::RenderSystems():

	// members
	pShapeRenderSystem		(nullptr),
	pSpriteRenderSystem		(nullptr),
	pSpriteAnimationSystem	(nullptr),
	pTextRenderSystem		(nullptr),
	graphics				(nullptr)
{}


// methods

// ===========================================================================
// registers and initializes internal rendering systems, saving pointers
// to each system so operations may be carried out during the update loop.
// ===========================================================================
void RenderSystems::initialize(
	ECSInstance&		ecs,
	GraphicsContext*	graphics
) {
	// register and initialize systems
	pShapeRenderSystem		= ecs.registerSystem<ShapeRenderSystem>();
	pSpriteRenderSystem		= ecs.registerSystem<SpriteRenderSystem>();
	pSpriteAnimationSystem	= ecs.registerSystem<SpriteAnimationSystem>();
	pTextRenderSystem		= ecs.registerSystem<TextRenderSystem>();

	// register components and signatures for systems
	pShapeRenderSystem		->setSignature(ecs);
	pSpriteRenderSystem		->setSignature(ecs);
	pSpriteAnimationSystem	->setSignature(ecs);
	pTextRenderSystem		->setSignature(ecs);

	// set graphics contexts for rendering systems
	pShapeRenderSystem		->initialize(graphics);
	pSpriteAnimationSystem	->initialize(graphics);
	pSpriteRenderSystem		->initialize(graphics);
	pTextRenderSystem		->initialize(graphics);

	// store graphics context for later rendering
	this->graphics = graphics;
}

// ===========================================================================
// calls each render system's render methods in order, and also updates
// animations according to the elapsed frame time. should be called every
// frame.
// ===========================================================================
void RenderSystems::render(
	const float&		deltaTime
) {
	// update sprite animations before rendering
	pSpriteAnimationSystem->update(deltaTime);

	// prepare to draw all graphics components
	if (graphics->beginSpriteDraw() != D3D_OK) return;

	// render graphics components
	pShapeRenderSystem		->render();
	pSpriteRenderSystem		->render();
	pTextRenderSystem		->render();

	// finish draw sequence
	graphics->endSpriteDraw();
}