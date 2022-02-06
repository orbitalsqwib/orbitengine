// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Game Engine Specification
// ===========================================================================

#ifndef _ORBIT_ORBITENGINE_H
#define _ORBIT_ORBITENGINE_H

// import necessary headers
#include "IEngineContext.h"
#include "../common/defaultScenes.h"
#include "../graphics/graphicsContext.h"
#include "../input/keyboardState.h"
#include "../input/mouseState.h"
#include "../input/gamepad.h"
#include "../messaging/pubsub.h"
#include "../performance/timer.h"
#include "../prefabs/scenes/exit/exitScene.h"
#include "../prefabs/scenes/startup/startup.h"
#include "../scene/sceneManager.h"
#include "../window/classes/gameWindow.h"
#include <string>


// main definition

// specifies the topmost handler object that encapsulates all other handlers, 
// and is responsible for the lifecycle of all major game components in the
// engine.
class OrbitEngine
{
private:

	// input components

	// keyboard input state container
	KeyboardState keyboardState;

	// mouse input state container
	MouseState mouseState;

	// gamepad handler
	GamepadHandler gamepadHandler;


	// display components

	// main game window
	GameWindow window;

	// graphics context
	GraphicsContext graphicsContext;


	// gameplay components

	// game-wide scene manager
	SceneManager sceneManager;


	// messaging

	// central gameplay message broker
	MessageBroker messageBroker;


	// fps / performance components

	// performance timer
	PerformanceTimer timer;

	// fps text style manager
	TextStyleManager textStyleMgr;

	// fps text operator
	TextOperator textOp;

	// fps text data
	TextData fpsTextData;


	// flags

	// specifies if the engine has been set up and is ready to run
	bool ready;

	// specifies if the engine is currently paused
	bool paused;


	// private methods

	// updates the fps counter according to the performance timer
	void updateFPSCounter();

public:

	// provides access to specific engine components and states
	class Context : public IEngineContext
	{
	private:

		// states

		// non-owning pointer to the owner of the proxy
		OrbitEngine* owner;


		// constructor

		// declare OrbitEngine as friend
		friend OrbitEngine;

		// can only be constructed by OrbitEngine classes
		Context(OrbitEngine* _owner) : owner(_owner) {}

	public:

		// implement pure virtual getters

		// returns a reference to the keyboard state container
		virtual KeyboardState& keyboard() { return owner->keyboardState; }

		// returns a reference to the mouse state container
		virtual MouseState& mouse() { return owner->mouseState; }

		// returns a reference to the gamepad handler
		virtual GamepadHandler& gamepads() { return owner->gamepadHandler; }

		// returns a reference to the graphics handler
		virtual GraphicsContext& graphics() { return owner->graphicsContext; }

		// returns a reference to the shared message broker
		virtual MessageBroker& broker() { return owner->messageBroker; }

	};

	// constructor
	OrbitEngine(LPCWSTR gameName);


	// methods

	// sets the initial game scene. this function must be called for the game
	// engine to function, and must provide a valid scene name (that has been
	// registered with the engine before-hand).
	void setInitialScene(const std::string& sceneName);

	// game update handler - called continuously during the main message loop,
	// delegates work to game components in order.
	void update();

	
	// delegate (passthrough) methods

	// registers a scene class with the scene manager under sceneName. this
	// will construct a new scene object and store it in the scene registry.
	// scenes constructed this way will require a default (no-argument)
	// constructor.

	// registers a scene with the engine's scene manager under sceneName. at
	// least one scene should be registered with the game engine for it to run
	template <class SceneType>
	OrbitEngine& registerScene(
		const std::string&	sceneName
	) {
		// delegate scene registration to scene manager
		sceneManager.registerScene<SceneType>(sceneName);

		// return reference to self to allow method chaining
		return *this;
	}

	// registers a scene with the engine's scene manager under sceneName, but
	// adopts a manually allocated scene instead of creating a new scene
	// object internally.
	OrbitEngine& registerScene(
		const std::string&	sceneName,
		IScene*				scene
	);


	// getters

	// returns a context object that provides access to member states
	Context getContext() { return Context(this); }
};

#endif // !_ORBIT_ORBITENGINE_H