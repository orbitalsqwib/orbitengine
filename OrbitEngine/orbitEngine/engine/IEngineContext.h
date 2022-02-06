// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Engine Context Interface Specification
// ===========================================================================

#ifndef _ORBIT_SCENE_IENGINECONTEXT_H
#define _ORBIT_SCENE_IENGINECONTEXT_H

// import necessary headers
#include "../graphics/graphicsContext.h"
#include "../input/keyboardState.h"
#include "../input/mouseState.h"
#include "../input/gamepad.h"
#include "../messaging/pubsub.h"

// forward declarations
class OrbitEngine;


// main definition

// defines an interface for the engine context object, which provides access
// to various game components and handlers that reside in the game engine.
class IEngineContext
{
public:

	// pure virtual getters

	// returns a reference to the keyboard state container
	virtual KeyboardState& keyboard() = 0;

	// returns a reference to the mouse state container
	virtual MouseState& mouse() = 0;

	// returns a reference to the gamepad handler
	virtual GamepadHandler& gamepads() = 0;

	// returns a reference to the graphics handler
	virtual GraphicsContext& graphics() = 0;

	// returns a reference to the shared message broker
	virtual MessageBroker& broker() = 0;

};

#endif // !_ORBIT_SCENE_IENGINECONTEXT_H