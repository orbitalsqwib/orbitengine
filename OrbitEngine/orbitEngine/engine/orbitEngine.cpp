// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Game Handler Specification
// ===========================================================================

// import specification
#include "orbitEngine.h"


// ===========================================================================
// constructor
// ===========================================================================
OrbitEngine::OrbitEngine(
	LPCWSTR	gameName
):
	// input components
	keyboardState	(),
	mouseState		(),
	gamepadHandler	(),

	// display components
	window			(&keyboardState, &mouseState),
	graphicsContext	(),

	// gameplay components
	sceneManager	(new Context(this)), // manually allocate new context obj,
										 // auto. destroyed by scene manager

	// utility components
	messageBroker	(),
	timer			(240.0f, 1.0f),

	// flags
	ready			(false),
	paused			(false)
{
	// bind new instance of game window class, throw on failure
	if (!window.bindWindow(gameName)) throw Error(
		"Error: Failed to bind game window!"
	);

	// set window presentation mode
	window.getBroker()->pushImmediately(DisplayCommands::BORDEREDWINDOWED);

	// initialize graphics context
	graphicsContext.initialize(
		window.getHwndPtr(),
		window.getWidth(),
		window.getHeight(),
		false
	);
}


// methods

// ===========================================================================
// sets the initial game scene. this function must be called for the game
// engine to function, and must provide a valid scene name (that has been
// registered with the engine before-hand).
// ===========================================================================
void OrbitEngine::setInitialScene(
	const std::string&	sceneName
) {
	// attempt to push scene onto scene stack
	sceneManager.transition(sceneName, false);
}

// ===========================================================================
// game update handler - called continuously during the main message loop,
// delegates work to game components in order.
// ===========================================================================
void OrbitEngine::update()
{
	// run timer at the start of every update frame
	float frameTime = timer.runTimer();

	// check that engine is in a valid state to run
	if (!ready || paused) return;

	// run current scene's update method
	sceneManager.updateCurrentScene(frameTime);

	// handle all messages within the game's message broker
	messageBroker.processAllMessages();
	
	// handle all messages within the window's message broker
	window.getBroker()->processAllMessages();

	// update controller inputs and handle vibration
	gamepadHandler.updateInputs();
	gamepadHandler.updateGamepads(frameTime);
}


// delegate (passthrough) methods

// ===========================================================================
// registers a scene with the engine's scene manager under sceneName. at
// least one scene should be registered with the game engine for it to run
// ===========================================================================
template <class SceneType>
OrbitEngine& OrbitEngine::registerScene(
	const std::string&	sceneName
) {
	// delegate scene registration to scene manager
	sceneManager.registerScene<SceneType>(sceneName);

	// return reference to self to allow method chaining
	return *this;
}

// ===========================================================================
// registers a scene with the engine's scene manager under sceneName, but
// adopts a manually allocated scene instead of creating a new scene
// object internally.
// ===========================================================================
OrbitEngine& OrbitEngine::registerScene(
	const std::string&	sceneName,
	IScene*				scene
) {
	// delegate scene registration to scene manager
	sceneManager.registerScene(sceneName, scene);

	// return reference to self to allow method chaining
	return *this;
}
