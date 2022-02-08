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

			// setup game state
			setupGameState();

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

			// refresh game state
			resetGameState();
			setupGameState();
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
			menu.resetOptions();
			menu.addOption("Start");
			menu.addOption("Quit");
			

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
	// create player
	player.create();
}

// ===========================================================================
// resets the game state
// ===========================================================================
void MainScene::resetGameState() 
{
	// reset timer to zero
	timer.reset();

	// reset enemy spawn cooldown timer to 0
	enemySpawnTimer = 0;

	// reset pickup spawn cooldown timer to max cooldown
	pickupSpawnTimer = Config::PICKUP_SPAWN_COOLDOWN;


	// destroy all tracked entities and their components

	// destroy player
	player.destroy();

	// reset enemies
	if (pEnemyResetSystem) pEnemyResetSystem->resetEntities();

	// reset pickups
	if (pPickupResetSystem) pPickupResetSystem->resetEntities();

	// reset blasts
	if (pBlastResetSystem) pBlastResetSystem->resetEntities();


	// return title to normal pause menu
	menu.setTitle("Paused");
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

// ===========================================================================
// adds tracking data to the specified entity to track another entity
// ===========================================================================
void MainScene::addTracking(
	const Entity& entity,
	const Entity& tracked
) {
	// add tracking component to entity
	ecs.addComponent<TrackingData>(entity, TrackingData(tracked));
}


// subscriber methods

// ===========================================================================
// handles collision events
// ===========================================================================
void MainScene::handleMessage(
	EntityCollided	message,
	MessageBroker*	broker
) {
	// handle player->enemy collisions
	if (message.subjectTag == "player" && message.targetTag == "enemy")
	{
		// if iframe component exists, ignore collision
		if (IFrameData* pFrame = ecs.getComponent<IFrameData>(message.subject))
		{
			// exit early
			return;
		}

		// player dies, handle gameover
		gameOver("Void's Thrall");
	}

	// handle player->pickup collisions
	else if (message.subjectTag == "player" && message.targetTag == "pickup")
	{
		// attempt to get pickup position
		if (PositionData* pPos = ecs.getComponent<PositionData>(message.target))
		{
			// get center of pickup
			float x = pPos->x + pPos->width / 2;
			float y = pPos->y + pPos->height / 2;

			// spawn blast at pickup center
			blastArchetype.spawn(
				x, 
				y,
				Config::PICKUP_BLAST_RADIUS,
				Config::PICKUP_BLAST_DURATION
			);
		}
		
		// kill pickup
		ecs.destroyEntity(message.target);
	}

	// handle blast->enemy collisions
	else if (message.subjectTag == "blast" && message.targetTag == "enemy")
	{
		// kill enemy
		ecs.destroyEntity(message.target);
	}

	// handle enemy->enemy collisions
	else if (message.subjectTag == "enemy" && message.targetTag == "enemy")
	{
		// get velocity data for subject enemy
		if (VelocityData* pV = ecs.getComponent<VelocityData>(message.subject))
		{
			// nudge enemy in direction of collision vector
			pV->dx += message.cV.x;
			pV->dy += message.cV.y;
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

	// prepare to render colliders on debug
	#if defined(DEBUG) | defined(_DEBUG)
		pCollisionSystem->DEBUG_initializeRenderer(&engine->graphics());
	#endif

	// add collision listeners
	pCollisionSystem->addCollisionHandler(*this);

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
	pFuelAnimSystem = ecs.registerSystem<FuelAnimSystem>();
	pFuelAnimSystem->setSignature(ecs);
	pFuelAnimSystem->initialize(engine->graphics());

	// register tracking system
	pTrackingSystem = ecs.registerSystem<TrackingSystem>();
	pTrackingSystem->setSignature(ecs);

	// register spawning system
	pSpawnSystem = ecs.registerSystem<SpawnSystem>();
	pSpawnSystem->setSignature(ecs);


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
	border.initialize(
		Config::xBorderPadding, 
		Config::yBorderPadding, 
		engine->graphics()
	);


	// ! prepare player

	// register player iframe system
	pIFrameSystem = ecs.registerSystem<IFrameSystem>();
	pIFrameSystem->setSignature(ecs);
	pIFrameSystem->initalize(engine->graphics());

	// register player entity group
	player.initialize(ecs, engine->graphics(), pTextureManager.get());

	
	// ! prepare enemies

	// register enemy reset system
	pEnemyResetSystem = ecs.registerSystem<ResetSystem<EnemyData>>();
	pEnemyResetSystem->setSignature(ecs);

	// register enemy archetype
	enemyArchetype.initialize(ecs, engine->graphics(), pTextureManager.get());


	// ! prepare pickups

	// register pickup reset system
	pPickupResetSystem = ecs.registerSystem<ResetSystem<PickupData>>();
	pPickupResetSystem->setSignature(ecs);

	// register pickup archetype
	pickupArchetype.initialize(ecs, engine->graphics(), pTextureManager.get());


	// ! prepare blasts

	// register blast reset system
	pBlastResetSystem = ecs.registerSystem<ResetSystem<BlastData>>();
	pBlastResetSystem->setSignature(ecs);

	// register blast despawn system
	pBlastSystem = ecs.registerSystem<BlastSystem>();
	pBlastSystem->setSignature(ecs);

	// register blast archetype
	blastArchetype.initialize(ecs, pTextureManager.get());
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

	// handle game updates when game is active and player is alive
	if (gameActive && player.isAlive())
	{
		// ! timer

		// update timers
		timer.update(deltaTime);
		enemySpawnTimer -= deltaTime;
		pickupSpawnTimer -= deltaTime;


		// ! velocity

		// apply last frame's velocities
		pVelocitySystem->applyVelocities(deltaTime);


		// ! enemy

		// run enemy tracking
		pTrackingSystem->updateDirection();

		// attempt to spawn enemy
		if (enemySpawnTimer <= 0)
		{
			// reset timer
			enemySpawnTimer = enemySpawnCooldown;

			// spawn enemy
			Entity newEnemy = pSpawnSystem->spawn(
				&enemyArchetype,
				border.getCorners().getRECT(),
				Config::SPAWN_PROTECT_RADIUS
			);

			// add tracking component to enemy
			addTracking(newEnemy, player.getEntity());
		}


		// ! player

		// enforce game boundary on player
		enforceGameBorder();

		// handle player control
		pControlSystem->handleUserInputs(deltaTime);

		// apply boost mechanics
		pBoostSystem->applyBoost(deltaTime);

		// update player sprite to reflect boost fuel %
		pFuelAnimSystem->updatePlayerSprite();

		// ! handle iframes if iframes exist
		pIFrameSystem->updateIFrames(deltaTime);


		// ! pickups

		// attempt to spawn pickup
		if (pickupSpawnTimer <= 0)
		{
			// reset timer
			pickupSpawnTimer = pickupSpawnCooldown;

			// spawn pickup
			pSpawnSystem->spawn(
				&pickupArchetype,
				border.getCorners().getRECT(),
				Config::SPAWN_PROTECT_RADIUS
			);
		}


		// ! blasts

		// update blast timers, despawn on expiry
		pBlastSystem->updateBlasts(deltaTime);


		// ! colliders

		// check collisions between player and enemies
		pCollisionSystem->checkCollisions(player.getEntity(), "enemy");

		// check collisions between player and pickups
		pCollisionSystem->checkCollisions(player.getEntity(), "pickup");

		// check collisions between blasts and enemies
		pCollisionSystem->checkAllCollisions("blast", "enemy");

		// check collisions between enemies
		pCollisionSystem->checkAllCollisions("enemy", "enemy");


		// ! thrust

		// run thrust system
		pThrustSystem->applyThrust();

		// process leftover scene messages
		sceneBroker.processAllMessages();
	}

	// render colliders on debug
	#if defined(DEBUG) | defined(_DEBUG)
		pCollisionSystem->DEBUG_render();
	#endif

	// render border when not on main menu
	if (!onMainMenu) border.render();

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