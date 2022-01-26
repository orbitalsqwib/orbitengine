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
#include "scene.h"
#include "../utils/pointers.h"
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
	std::stack<Scene*> sceneStack;

	// stores all registered scenes and maps them to their scene names.
	std::unordered_map<std::string, UniquePtr<Scene>> sceneRegistry;

public:

	// constructor
	SceneManager();

	
	// methods

	// registers a scene class with the scene manager under sceneName. this
	// will construct a new scene object and store it in the scene registry.
	// scenes constructed this way will require a default (no-argument)
	// constructor.
	template <class SceneType>
	void registerScene(const std::string& sceneName);

	// registers a scene class with the scene manager under sceneName, but
	// accepts a pointer to a manually allocated scene object and inserts
	// it into the scene registry instead of creating a new scene object using
	// the scene's default constructor.
	void registerScene(
		const std::string&	sceneName,
		Scene*				scene
	);

	// invokes the update function for the current scene
	void updateCurrentScene(const float& deltaTime);


	// implement pure virtuals

	// transitions to the specified scene, pausing or replacing the current
	// scene according to the 'replace' boolean.
	virtual void transition(
		const std::string& sceneName,
		const bool& replace
	);

};

#endif // !_ORBIT_SCENE_SCENEMANAGER_H