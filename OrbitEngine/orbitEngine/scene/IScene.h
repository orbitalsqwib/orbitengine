// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Scene Interface Implementation
// ===========================================================================

#ifndef _ORBIT_SCENE_ISCENE_H
#define _ORBIT_SCENE_ISCENE_H

// forward declarations
class IEngineContext;


// main definition

// defines the method interfaces for a base scene class.
class IScene
{
private:

	// only allow access to scene manager
	friend class SceneManager;

	// should bind the scene to the specified scene manager.
	virtual void setSceneManager(ISceneManager* pSceneMgr) = 0;

	// should bind the scene to the specified engine context
	virtual void setEngineContext(IEngineContext* pEngineContext) = 0;

public:

	// virtual destructor
	virtual ~IScene() {}

	// should return the current initialization state of the scene
	virtual bool isInitialized() = 0;

	// delayed initializer method - sets up underlying managers before any
	// scene methods are called. this is only called when the scene is
	// transitioned to, and calls setup once all initialization is complete
	virtual void initialize() = 0;

	// scene cleanup method - frees all allocated memory for base scene states
	// when the scene is transitioned out of. this method invokes teardown
	// before actually freeing any managers so the scene remains valid at the
	// point of teardown invocation.
	virtual void reset() = 0;

	// scene update method - should specify the order in which systems are run
	// as well as handle other game logic that will be run every frame. this
	// method is invoked every frame, and constitutes the main update loop for
	// a particular scene. this method is guaranteed to not be run when the
	// scene is paused or halted, thus all updates within this loop will be
	// put in a sort of "stasis" until the scene is resumed.
	virtual void update(const float& deltaTime) = 0;

};

#endif // !_ORBIT_SCENE_ISCENE_H