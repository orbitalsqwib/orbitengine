// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Scene Manager Class Implementation
// ===========================================================================

// import specification
#include "sceneManager.h"


// ===========================================================================
// constructor
// ===========================================================================
SceneManager::SceneManager(
	IEngineContext* _pEngineContext
):
	// members
	sceneStack		(),
	sceneRegistry	(),
	pEngineContext	(nullptr)
{
	// ensure that the incoming engine context is non-null, else throw error
	if (!_pEngineContext) throw Error(
		"Error: No engine context was provided!"
	);

	// set engine context pointer - should always be valid
	pEngineContext = _pEngineContext;
}


// methods

// ===========================================================================
// registers a scene class with the scene manager under sceneName. this
// will construct a new scene object and store it in the scene registry.
// scenes constructed this way will require a default (no-argument)
// constructor.
// ===========================================================================
template <class SceneType>
void SceneManager::registerScene(
	const std::string&	sceneName
) {
	// ensure scene name has not been used yet, else throw error
	if (sceneRegistry.count(sceneName) > 0) throw Error(
		"Error: A scene has already been registered for: " + sceneName
	);

	// create new scene for type
	IScene* pNewScene = new SceneType();

	// set scene's scene manager to this instance
	pNewScene->setSceneManager(this);

	// copy instance's engine context to the scene
	pNewScene->setEngineContext(pEngineContext);

	// add scene to scene registry
	sceneRegistry[sceneName] = pNewScene;
}

// ===========================================================================
// registers a scene class with the scene manager under sceneName, but
// accepts a pointer to a manually allocated scene object and inserts
// it into the scene registry instead of creating a new scene object using
// the scene's default constructor.
// ===========================================================================
void SceneManager::registerScene(
	const std::string&	sceneName,
	IScene*				scene
) {
	// ensure scene name has not been used yet, else throw error
	if (sceneRegistry.count(sceneName) > 0) throw Error(
		"Error: A scene has already been registered for: " + sceneName
	);

	// set scene's scene manager to this instance
	scene->setSceneManager(this);

	// set scene's scene manager to this instance
	scene->setEngineContext(pEngineContext.get());

	// add provided scene into scene registry
	sceneRegistry[sceneName] = scene;
}

// ===========================================================================
// invokes the update function for the current scene
// ===========================================================================
void SceneManager::updateCurrentScene(
	const float&	deltaTime
) {
	// if scene stack has no scenes, exit early
	if (sceneStack.size() < 1) return;

	// else, run the top-most scene
	sceneStack.top()->update(deltaTime);
}


// implement pure virtuals

// ===========================================================================
// transitions to the specified scene, pausing or replacing the current
// scene according to the 'replace' boolean.
// ===========================================================================
void SceneManager::transition(
	const std::string&	sceneName,
	const bool&			replace
) {
	// ensure scene name has been registered, else throw error
	if (sceneRegistry.count(sceneName) == 0) throw Error(
		"Error: A scene has already been registered for: " + sceneName
	);

	// if replace is true, remove top-most scene to prepare for new scene
	if (replace) pop();

	// get non-owning pointer to new scene
	IScene* pScene = sceneRegistry[sceneName].get();

	// initialize new scene
	pScene->initialize();

	// push scene pointer (non-owning) onto scene stack
	sceneStack.push(pScene);
}

// ===========================================================================
// should pop the current scene from the scene stack, resuming the last
// scene placed on the scene stack. this will destroy the current scene!
// ===========================================================================
void SceneManager::pop()
{
	// ensure that the scene stack is not empty, else exit early
	if (sceneStack.empty()) return;

	// clean up top-most stack
	sceneStack.top()->reset();

	// remove top-most stack from scene stack
	sceneStack.pop();

	// the scene that was last placed on the scene stack is now on top of the
	// scene stack, and will automatically be run on updateCurrentScene()
}