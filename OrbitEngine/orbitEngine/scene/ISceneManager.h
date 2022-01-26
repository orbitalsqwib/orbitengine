// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Scene Manager Interface Implementation
// ===========================================================================

#ifndef _ORBIT_SCENE_ISCENEMANAGER_H
#define _ORBIT_SCENE_ISCENEMANAGER_H

// import necessary headers
#include <string>


// main definition

// defines an interface for a scene manager that can be accessed by a scene
// to notify its manager to transition to another scene as needed.
class ISceneManager
{
public:

	// virtual destructor
	virtual ~ISceneManager() {}

	// should transition to the specified scene, pausing or replacing the
	// current scene according to the 'replace' boolean.
	virtual void transition(
		const std::string&	sceneName,
		const bool&			replace
	) = 0;
};

#endif // !_ORBIT_SCENE_ISCENEMANAGER_H