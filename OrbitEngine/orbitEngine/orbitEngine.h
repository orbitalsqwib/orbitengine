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
#include "graphics/graphicsContext.h"
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

	// graphics context
	GraphicsContext graphicsContext;


	// gameplay components

	// TODO: SCENE MANAGER

	// TODO: ECS


	// utility components

	// central gameplay message broker
	MessageBroker broker;

	// performance timer
	PerformanceTimer timer;

public:

	// provides getters to its owner's states
	class Proxy
	{
	private:

		// states

		// non-owning pointer to the owner of the proxy
		OrbitEngine* owner;


		// constructor

		// declare OrbitEngine as friend
		friend OrbitEngine;

		// can only be constructed by OrbitEngine classes
		Proxy(OrbitEngine* _owner): owner(_owner) {}

	public:

		// getters

		// returns a reference to the keyboard state container
		KeyboardState& keyboard() { return owner->keyboard; }

		// returns a reference to the mouse state container
		MouseState& mouse() { return owner->mouse; }

		// returns a reference to the gamepad handler
		GamepadHandler& gamepads() { return owner->gamepads; }

		// returns a reference to the graphics handler
		GraphicsContext& graphicsContext() { return owner->graphicsContext; }

		// returns a reference to the shared message broker
		MessageBroker& broker() { return owner->broker; }

	};

	// constructor
	OrbitEngine();

	// destructor
	~OrbitEngine();


	// methods

	// game update handler - called continuously during the main message loop,
	// delegates work to game components in order.
	void update();


	// getterse

	// returns a proxy object that provides access to member states
	Proxy getProxy() { return Proxy(this); }
};

#endif // !_ORBIT_ORBITENGINE_H