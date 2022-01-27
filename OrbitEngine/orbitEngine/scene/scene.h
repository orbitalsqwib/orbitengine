// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Scene Base Class Specification
// ===========================================================================

#ifndef _ORBIT_SCENE_SCENE_H
#define _ORBIT_SCENE_SCENE_H

// import necessary headers
#include "ISceneManager.h"
#include "IScene.h"
#include "../ecs/ecsInstance.h"
#include "../engine/IEngineContext.h"
#include "../error.h"


// main definition

// defines a base scene class that should be inherited by all game scenes.
// provides a basic entity component system instance, as well as the game
// engine's context. this is where all game logic should be implemented in.
class Scene : public IScene
{
private:

	// implement private pure virtuals

	// should bind the scene to the specified scene manager.
	virtual void setSceneManager(ISceneManager* _pSceneMgr);

	// should bind the engine context to the specified scene manager.
	virtual void setEngineContext(IEngineContext* _pEngineContext);

protected:

	// members

	// ecs instance for the scene, which is only initialized when the scene
	// is loaded by the scene manager. manages the entities, components and
	// systems for the scene.
	ECSInstance ecs;

	// game engine proxy, provides access to various game handlers that may
	// be utilised by systems to implement game logic. guaranteed to be valid
	// at the point of scene runtime.
	IEngineContext* engine;

	// pointer to the scene manager. can be used to transition to another
	// scene, or quit the game entirely.
	ISceneManager* pSceneMgr;

public:

	// constructor
	Scene();

	// virtual destructor
	~Scene() {}


	// implement pure virtuals

	// delayed initializer method - sets up underlying managers before any
	// scene methods are called. this is only called when the scene is
	// transitioned to, and calls setup once all initialization is complete
	void initialize();

	// scene cleanup method - frees all allocated memory for base scene states
	// when the scene is transitioned out of. this method invokes teardown
	// before actually freeing any managers so the scene remains valid at the
	// point of teardown invocation.
	void reset();


	// pure virtual methods

	// scene setup method - should set up all entities, components and systems
	// that will be used / displayed within the scene. this method is invoked
	// on transitioning to the scene, and is guaranteed to be run before the
	// scene update loop is run.
	virtual void setup() = 0;

	// scene update method - should specify the order in which systems are run
	// as well as handle other game logic that will be run every frame. this
	// method is invoked every frame, and constitutes the main update loop for
	// a particular scene. this method is guaranteed to not be run when the
	// scene is paused or halted, thus all updates within this loop will be
	// put in a sort of "stasis" until the scene is resumed.
	virtual void update(const float& deltaTime) = 0;

	// scene teardown method - should clean up all non-ecs objects or states
	// that the scene introduces over its lifecycle. (ecs-managed objects will
	// be handled automatically by the ecs system) this method is only invoked
	// when transitioning out of the scene, and will not be called if the
	// scene is paused or halted temporarily.
	virtual void teardown() = 0;
	
};

#endif // !_ORBIT_SCENE_SCENE_H