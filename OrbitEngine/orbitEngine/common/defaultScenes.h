// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Default Scenes Specification
// ===========================================================================

#ifndef _ORBIT_COMMON_DEFAULTSCENES_H
#define _ORBIT_COMMON_DEFAULTSCENES_H

// import necessary headers
#include <string>


// main definition

// specifies special scene names that map to special scene behaviours 
namespace DefaultScenes
{
	// displays the engine startup scene - removes itself from the scene stack
	// once the startup scene finishes displaying
	const std::string StartupScene	= "SCENE_STARTUP";

	// tells the scene manager to immediately quit the application
	const std::string ExitScene		= "SCENE_EXIT";
};

#endif // !_ORBIT_COMMON_DEFAULTSCENES_H