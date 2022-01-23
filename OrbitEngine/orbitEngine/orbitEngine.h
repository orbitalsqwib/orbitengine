// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Game Handler Specification
// ===========================================================================

#ifndef _ORBIT_ORBITENGINE_H
#define _ORBIT_ORBITENGINE_H

// import necessary headers
#include "graphics/graphics.h"
#include "input/keyboardState.h"
#include "input/mouseState.h"
#include "input/gamepad.h"
#include "messaging/pubsub.h"
#include "performance/timer.h"
#include "window/classes/gameWindow.h"

// main definition

// specifies the topmost handler object that encapsulates all other handlers, 
// and is responsible for the lifecycle of all major game components in the
// engine.
class OrbitEngine
{
private:

	// input components

	// keyboard input state container
	KeyboardState keyboard;

	// mouse input state container
	MouseState mouse;

	// gamepad handler
	GamepadHandler gamepads;


	// display components

	// main game window
	GameWindow window;

	// TODO: GRAPHICS


	// gameplay components

	// TODO: SCENE MANAGER

	// TODO: ECS


	// utility components

	// central gameplay message broker
	MessageBroker broker;

	// performance timer
	PerformanceTimer timer;

public:

	// constructor
	OrbitEngine();

	// destructor
	~OrbitEngine();


	// methods

	// game update handler - called continuously during the main message loop,
	// delegates work to game components in order.
	void update();

};

#endif // !_ORBIT_ORBITENGINE_H