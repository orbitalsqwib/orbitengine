// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Exit Scene Specification
// ===========================================================================

#ifndef _ORBIT_PREFABS_EXITSCENE_H
#define _ORBIT_PREFABS_EXITSCENE_H

// import necessary headers
#include "../../../scene/scene.h"


// main definition

// defines the logic for the engine's startup scene
class ExitScene : public Scene
{
public:

	// scene methods

	// scene setup method - should set up all entities, components and systems
	// that will be used / displayed within the scene. this method is invoked
	// on transitioning to the scene, and is guaranteed to be run before the
	// scene update loop is run.
	virtual void setup() { PostQuitMessage(0); }

	// scene update method - should specify the order in which systems are run
	// as well as handle other game logic that will be run every frame. this
	// method is invoked every frame, and constitutes the main update loop for
	// a particular scene. this method is guaranteed to not be run when the
	// scene is paused or halted, thus all updates within this loop will be
	// put in a sort of "stasis" until the scene is resumed.
	virtual void update(const float& deltaTime) {}

	// scene teardown method - should clean up all non-ecs objects or states
	// that the scene introduces over its lifecycle. (ecs-managed objects will
	// be handled automatically by the ecs system) this method is only invoked
	// when transitioning out of the scene, and will not be called if the
	// scene is paused or halted temporarily.
	virtual void teardown() {}

};

#endif // !_ORBIT_PREFABS_EXITSCENE_H