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

			// reset game states
			resetGameState();

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
		}
		}
	}
}

// ===========================================================================
// handles menu controls
// ===========================================================================
void MainScene::handleMenu()
{
	// if game is paused and menu is active, handle menu controls
	if (!gameActive)
	{
		// unpause game if on pause menu
		if (engine->keyboard().wasKeyPressed(VK_ESCAPE) && !onMainMenu)
		{
			// unpause game
			gameActive = true;

			// show menu
			menu.toggleMenu(false);
		}

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
}

// ===========================================================================
// sets game states and entities
// ===========================================================================
void MainScene::setupGameState()
{
	// create entities
	player.create();
}

// ===========================================================================
// resets the game state
// ===========================================================================
void MainScene::resetGameState() 
{
	// reset timer to zero
	timer.reset();

	// destroy all tracked entities and their components
	player.destroy();

	// return title to normal pause menu
	menu.setTitle("Paused");

	// setup game state again
	setupGameState();
}

// ===========================================================================
// kills the player and handles player death
// ===========================================================================
void MainScene::gameOver(const std::string& cause)
{
	// destroy player entity
	player.destroy();

	// stop game
	gameActive = false;

	// update menu title to present score
	menu.setTitle(
		"You have died. The Void's Loop activates...\n\n"
		"Survival Time: " + timer.getTimeStr() + "\n"
		"Killed By: " + cause
	);

	// present menu
	menu.toggleMenu(true);
}

// ===========================================================================
// kills the player if the player's collider is outside of the border
// ===========================================================================
void MainScene::enforceGameBorder()
{
	// ensure player is alive, else skip check.
	if (!player.isAlive()) return;

	// retrieve entity for player
	Entity pEntity = player.getEntity();

	// attempt to get collider data for player
	if (ColliderData* pCol = ecs.getComponent<ColliderData>(pEntity))
	{
		// check if player exceeded game border
		if (colliderOp.outsideRect(*pCol, border.getCorners().getRECT()))
		{
			// kill player
			gameOver("The Void's Border");
		}
	}
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
	pVelocitySystem->setSignature(ecs);
	pVelocitySystem->initialize(sceneBroker);

	// initialize transform listener
	transformListener.initialize(ecs, sceneBroker);
	ecs.registerComponent<PositionData>();

	// register and initialize collision system
	pCollisionSystem = ecs.registerSystem<CollisionSystem>();
	pCollisionSystem->setSignature(ecs);
	pCollisionSystem->DEBUG_initializeRenderer(&engine->graphics());

	// register thrust system
	pThrustSystem = ecs.registerSystem<ThrustSystem>();
	pThrustSystem->setSignature(ecs);


	// ! setup game logic systems

	// register and initializes player control system
	pControlSystem = ecs.registerSystem<ControlSystem>();
	pControlSystem->setSignature(ecs);
	pControlSystem->initialize(sceneBroker, engine->keyboard());

	// register boost system
	pBoostSystem = ecs.registerSystem<BoostSystem>();
	pBoostSystem->setSignature(ecs);

	// register boost animation system
	pBoostAnimSystem = ecs.registerSystem<BoostAnimSystem>();
	pBoostAnimSystem->setSignature(ecs);
	pBoostAnimSystem->initialize(engine->graphics());


	// ! setup managers

	// build new texture manager
	pTextureManager = new TextureManager(&engine->graphics());

	// build new text style manager
	pTextStyleManager = new TextStyleManager(&engine->graphics());


	// ! setup scene text objects

	// register text styles
	pTextStyleManager->addStyle("default",
		TextStyleData(L"OCR A", 18, 0, 0, Colors::WHITE)
	);


	// ! create main menu

	// setup main menu group
	menu.initialize(
		ecs,
		engine->graphics(),
		*pTextStyleManager,
		"Survive The Void",
		false
	);

	// setup main menu options
	menu.addOption("Start");
	menu.addOption("Quit");


	// ! setup timer
	timer.initialize(
		ecs,
		engine->graphics(),
		pTextStyleManager.get()
	);


	// ! setup border
	border.initialize(32, 32, engine->graphics());


	// ! prepare player
	player.initialize(ecs, engine->graphics(), pTextureManager.get());


	setupGameState();
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
	// handle menu controls
	handleMenu();

	// handle game updates
	if (gameActive)
	{
		// update timer
		timer.update(deltaTime);

		// apply last frame's velocities
		pVelocitySystem->applyVelocities(deltaTime);

		// enforce game boundary on player
		enforceGameBorder();

		// handle player control
		pControlSystem->handleUserInputs(deltaTime);

		// apply boost mechanics
		pBoostSystem->applyBoost(deltaTime);

		// update player sprite to reflect boost fuel %
		pBoostAnimSystem->updatePlayerSprite();

		// run thrust system
		pThrustSystem->applyThrust();

		// render border
		border.render();
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