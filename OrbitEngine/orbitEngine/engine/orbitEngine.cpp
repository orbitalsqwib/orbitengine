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

	// messaging
	messageBroker	(),

	// fps / performance components
	timer			(240.0f, 1.0f),
	textStyleMgr	(&graphicsContext),
	textOp			(&graphicsContext),
	fpsTextData		(),

	// flags
	ready			(false),
	paused			(false)
{
	// game setup sequence

	// ! bind new instance of game window class, throw on failure
	if (!window.bindWindow(gameName)) throw Error(
		"Error: Failed to bind game window!"
	);

	// ! set window presentation mode
	window.getBroker()->pushImmediately(DisplayCommands::BORDEREDWINDOWED);

	// ! initialize graphics context
	graphicsContext.initialize(
		window.getHwndPtr(),
		window.getWidth(),
		window.getHeight(),
		false
	);

	// ! subscribe graphics context to window broker
	window.getBroker()->addSubscriber<WindowResized>(graphicsContext);

	// ! register default scenes
	registerScene<StartupScene>(DefaultScenes::StartupScene);
	registerScene<ExitScene>(DefaultScenes::ExitScene);

	// ! setup fps counter

	// create fps text style
	textStyleMgr.addStyle(
		"fps", 
		TextStyleData(L"OCR A", 14, 0, 0, Colors::BLACK, Colors::LIME)
	);

	// configure fps text data
	fpsTextData.x = 16;
	fpsTextData.y = 16;
	fpsTextData.z = ZValues::RESERVED;
	fpsTextData.pStyle = textStyleMgr.getStyle("fps");
}


// private methods

// ===========================================================================
// updates the fps counter according to the performance timer
// ===========================================================================
void OrbitEngine::updateFPSCounter()
{
	// update fps text
	int fps = int(timer.getFPS());
	fpsTextData.text = "fps: " + std::to_string(fps);

	// change fps indicator color according to current fps
	COLOR_ARGB fpsBG = fps >= 60
		? Colors::LIME
		: fps >= 30
		? Colors::YELLOW
		: Colors::RED;

	// update fps bg
	textStyleMgr.getStyle("fps")->highlightColor = fpsBG;
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

	// push startup scene onto scene stack above initial scene - removes
	// itself from the scene stack once it finishes playing
	sceneManager.transition(DefaultScenes::StartupScene, false);

	// tell engine that engine is ready to run.
	ready = true;
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
	if (!ready || paused || frameTime < 0) 
		return;

	// maintain graphics device
	graphicsContext.maintainDevice();

	// start rendering for the frame in advance
	HRESULT sceneStarted = graphicsContext.beginSceneDraw();

	// attempt to render fps display
	if (graphicsContext.beginSpriteDraw() == D3D_OK)
	{
		updateFPSCounter();
		textOp.render(fpsTextData);
		graphicsContext.endSpriteDraw();
	}

	// run current scene's update method
	sceneManager.updateCurrentScene(frameTime);

	// handle all messages within the game's message broker
	messageBroker.processAllMessages();
	
	// handle all messages within the window's message broker
	window.getBroker()->processAllMessages();

	// finish draw sequence, then show current frame via page flip
	if (sceneStarted == D3D_OK)
	{
		graphicsContext.endSceneDraw();
		graphicsContext.showBackBuffer();
	}

	// update controller inputs and handle vibration
	gamepadHandler.updateInputs();
	gamepadHandler.updateGamepads(frameTime);

	// clear key presses at end of each frame
	keyboardState.clearKeyPresses();
}


// delegate (passthrough) methods

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
