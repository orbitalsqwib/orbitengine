// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Scene Manager Class Specification
// ===========================================================================

#ifndef _ORBIT_SCENE_SCENEMANAGER_H
#define _ORBIT_SCENE_SCENEMANAGER_H

// import necessary headers
#include "ISceneManager.h"
#include "IScene.h"
#include "../engine/IEngineContext.h"
#include "../utils/pointers.h"
#include "../error.h"
#include <stack>
#include <string>
#include <unordered_map>


// main definition

class SceneManager : public ISceneManager
{
private:

	// members

	// defines a stack of active scenes, where only the top-most scene is
	// continuously run each frame. note: each scene will take up memory until 
	// removed from the stack.
	std::stack<IScene*> sceneStack;

	// stores all registered scenes and maps them to their scene names.
	std::unordered_map<std::string, UniquePtr<IScene>> sceneRegistry;

	// stores an engine context that is copied to each scene on registration
	// and is automatically deallocated when the scene manager is destroyed.
	UniquePtr<IEngineContext> pEngineContext;

public:

	// constructor
	SceneManager(IEngineContext* _pEngineContext);

	
	// methods

	// registers a scene class with the scene manager under sceneName. this
	// will construct a new scene object and store it in the scene registry.
	// scenes constructed this way will require a default (no-argument)
	// constructor.
	template <class SceneType>
	void registerScene(
		const std::string&	sceneName
	) {
		// ensure scene name has not been used yet, else throw error
		if (sceneRegistry.count(sceneName) > 0) throw Error(
			"Error: A scene has already been registered for: " + sceneName
		);

		// create new scene for type and cast it to interface
		IScene* pNewScene = new SceneType();

		// set scene's scene manager to this instance
		pNewScene->setSceneManager(this);

		// copy instance's engine context to the scene
		pNewScene->setEngineContext(pEngineContext.get());

		// add scene to scene registry
		sceneRegistry[sceneName] = pNewScene;
	}

	// registers a scene class with the scene manager under sceneName, but
	// accepts a pointer to a manually allocated scene object and inserts
	// it into the scene registry instead of creating a new scene object using
	// the scene's default constructor.
	void registerScene(
		const std::string&	sceneName,
		IScene*				scene
	);

	// invokes the update function for the current scene
	void updateCurrentScene(const float& deltaTime);


	// implement pure virtuals

	// transitions to the specified scene, pausing or replacing the current
	// scene according to the 'replace' boolean.
	virtual void transition(
		const std::string&	sceneName,
		const bool&			replace
	);

	// should pop the current scene from the scene stack, resuming the last
	// scene placed on the scene stack. this will destroy the current scene!
	virtual void pop();

};

#endif // !_ORBIT_SCENE_SCENEMANAGER_H