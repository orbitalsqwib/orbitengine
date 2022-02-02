// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Scene Base Class Implementation
// ===========================================================================

// import specification
#include "scene.h"


// ===========================================================================
// constructor
// ===========================================================================
Scene::Scene():

	// members
	ecs			(),
	engine		(nullptr),
	pSceneMgr	(nullptr),
	sceneBroker	()
{}


// implement private pure virtuals

// ===========================================================================
// should bind the scene to the specified scene manager.
// ===========================================================================
void Scene::setSceneManager(SceneManager* _pSceneMgr)
{
	// ensure specified scene manager is a valid pointer and assign if so
	if (_pSceneMgr) pSceneMgr = _pSceneMgr;
}

// ===========================================================================
// should bind the engine context to the specified scene manager.
// ===========================================================================
void Scene::setEngineContext(IEngineContext* _pEngineContext)
{
	// ensure specified scene manager is a valid pointer and assign if so
	if (_pEngineContext) engine = _pEngineContext;
}


// methods

// ===========================================================================
// delayed initializer method - sets up underlying managers before any
// scene methods are called. this is only called when the scene is
// transitioned to, and calls setup once all initialization is complete
// ===========================================================================
void Scene::initialize()
{
	// ensure engine and scene manager pointers are valid, else throw error
	if (!engine || !pSceneMgr) throw Error(
		"Error: Engine context for scene is missing!"
	);

	// initialize ecs - the scene is valid from this point onwards
	ecs.initialize();

	// call scene setup
	setup();
}

// ===========================================================================
// scene cleanup method - frees all allocated memory for base scene states
// when the scene is transitioned out of. this method invokes teardown
// before actually freeing any managers so the scene remains valid at the
// point of teardown invocation.
// ===========================================================================
void Scene::reset()
{
	// allow user-specified teardown logic to run first
	teardown();

	// reset ecs and free all ecs-reserved memory - the scene is invalid after
	// this method is called.
	ecs.reset();
}