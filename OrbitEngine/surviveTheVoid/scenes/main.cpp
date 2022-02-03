// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Main Scene Implementation
// ===========================================================================

// import specification
#include "main.h"


// private methods

// ===========================================================================
// handle menu selection
// ===========================================================================
void MainScene::handleMenuSelection()
{
	// handle selection for main menu
	if (onMainMenu)
	{
		// switch based on option chosen
		switch (menu.getSelected())
		{
		case 0:
		{
			// START GAME

			// toggle menu off
			menu.toggleMenu(false);

			// update menu states
			menu.setTitle("Paused");
			menu.setOption("Resume", 0);
			menu.setOption("Reset", 1);
			menu.addOption("Return To Main Menu");

			// set game active to true
			gameActive = true;

			// menu will now be the pause menu
			onMainMenu = false;
		}
		break;
		case 1:
		{
			// QUIT
			pSceneMgr->transition(DefaultScenes::ExitScene, false);
			return;
		}
		}
	}

	// handle selection for pause menu
	else
	{
		switch (menu.getSelected())
		{
		case 1:
		{
			// RESET GAME

			// reset game states
			resetGameState();
		}
		// no breaks, case 1 is a superset of case 0 functionality
		case 0:
		{
			// RESUME GAME

			// toggle menu off
			menu.toggleMenu(false);

			// set game active to true
			gameActive = true;
		}
		break;
		case 2:
		{
			// RETURN TO MAIN MENU

			// update menu
			menu.setTitle("Survive The Void");
			menu.setOption("Start", 0);
			menu.setOption("Quit", 1);
			menu.removeOption(2);
			menu.setSelected(0);

			// set game active to false
			gameActive = false;

			// menu will now be the main menu
			onMainMenu = true;

			// reset game states
			resetGameState();
		}
		}
	}
}

// ===========================================================================
// sets game states and entities
// ===========================================================================
void MainScene::setupGameState()
{

}

// ===========================================================================
// resets the game state
// ===========================================================================
void MainScene::resetGameState() 
{
	
}


// scene methods

// ===========================================================================
// scene setup method - should set up all entities, components and systems
// that will be used / displayed within the scene. this method is invoked
// on transitioning to the scene, and is guaranteed to be run before the
// scene update loop is run.
// ===========================================================================
void MainScene::setup()
{
	// ! setup graphics

	// setup rendering system
	renderSystems.initialize(ecs, &engine->graphics());

	// set background color
	engine->graphics().setBGColor(Colors::BLACK);


	// ! setup kinematics systems

	// register and initialize velocity system
	pVelocitySystem = ecs.registerSystem<VelocitySystem>();
	pVelocitySystem->initialize(sceneBroker);

	// initialize transform listener
	transformListener.initialize(ecs, sceneBroker);

	// register and initialize collision system
	pCollisionSystem = ecs.registerSystem<CollisionSystem>();
	pCollisionSystem->DEBUG_initializeRenderer(&engine->graphics());


	// ! setup text objects

	// build new text style manager
	pTextStyleManager = new TextStyleManager(&engine->graphics());

	// register text styles
	pTextStyleManager->addStyle("default",
		TextStyleData(L"OCR A", 18, 0, 0, Colors::WHITE)
	);


	// ! create entities

	// setup main menu group
	menu.initialize(
		ecs,
		*pTextStyleManager,
		"Survive The Void",
		false
	);

	// setup main menu options
	menu.addOption("Start");
	menu.addOption("Quit");
}

// ===========================================================================
// scene update method - should specify the order in which systems are run
// as well as handle other game logic that will be run every frame. this
// method is invoked every frame, and constitutes the main update loop for
// a particular scene. this method is guaranteed to not be run when the
// scene is paused or halted, thus all updates within this loop will be
// put in a sort of "stasis" until the scene is resumed.
// ===========================================================================
void MainScene::update(
	const float&	deltaTime
) {
	// if game is paused and menu is active, handle menu controls
	if (!gameActive)
	{
		// handle cursor
		if (engine->keyboard().wasKeyPressed(VK_DOWN))
		{
			// go to next menu option
			menu.selectNextOption();
		}
		else if (engine->keyboard().wasKeyPressed(VK_UP))
		{
			// go to previous menu option
			menu.selectPrevOption();
		}
		
		// handle selection for main menu
		if (engine->keyboard().wasKeyPressed(VK_RETURN))
		{
			handleMenuSelection();
		}
	}
	// if game is active, handle game controls
	else
	{
		// handle pausing
		if (engine->keyboard().wasKeyPressed(VK_ESCAPE))
		{
			// pause game
			gameActive = false;

			// show menu
			menu.toggleMenu(true);
		}
	}

	// render scene
	renderSystems.render(deltaTime);
}

// ===========================================================================
// scene teardown method - should clean up all non-ecs objects or states
// that the scene introduces over its lifecycle. (ecs-managed objects will
// be handled automatically by the ecs system) this method is only invoked
// when transitioning out of the scene, and will not be called if the
// scene is paused or halted temporarily.
// ===========================================================================
void MainScene::teardown()
{
	// reset background color
	engine->graphics().setBGColor(Colors::LIME);
}