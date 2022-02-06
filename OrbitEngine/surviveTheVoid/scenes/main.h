// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Main Scene Specification
// ===========================================================================

#ifndef _STV_SCENES_MAIN_H
#define _STV_SCENES_MAIN_H

// import necessary headers
#include "../config.h"
#include "../../orbitEngine/imports/commons.h"
#include "../../orbitEngine/imports/scene.h"
#include "../../orbitEngine/imports/systems.h"
#include "../../orbitEngine/imports/graphics.h"
#include "../systems/controlSystem.h"
#include "../systems/thrustSystem.h"
#include "../systems/trackingSystem.h"
#include "../systems/boostSystem.h"
#include "../systems/fuelAnimSystem.h"
#include "../systems/resetSystem.h"
#include "../systems/spawnSystem.h"
#include "../systems/blastSystem.h"
#include "../systems/iframeSystem.h"
#include "../entityGroups/mainMenu.h"
#include "../entityGroups/player.h"
#include "../entityGroups/timer.h"
#include "../archetypes/enemyArchetype.h"
#include "../archetypes/pickupArchetype.h"
#include "../archetypes/blastArchetype.h"
#include "../handlers/border.h"
#include <math.h>


// main definition

class MainScene : 
	public Scene, 
	public ISubscriber<EntityCollided>
{
private:

	// systems

	// scene render group
	RenderSystems renderSystems;

	// velocity system
	VelocitySystem* pVelocitySystem;

	// collision system
	CollisionSystem* pCollisionSystem;

	// thrust system
	ThrustSystem* pThrustSystem;

	// player control system
	ControlSystem* pControlSystem;

	// boost mechanic system
	BoostSystem* pBoostSystem;

	// fuel animation system
	FuelAnimSystem* pFuelAnimSystem;

	// tracking system
	TrackingSystem* pTrackingSystem;

	// enemy reset system
	ResetSystem<EnemyData>* pEnemyResetSystem;

	// pickup reset system
	ResetSystem<PickupData>* pPickupResetSystem;

	// blast reset system
	ResetSystem<BlastData>* pBlastResetSystem;

	// entity spawning system
	SpawnSystem* pSpawnSystem;

	// blast despawn system
	BlastSystem* pBlastSystem;

	// player iframe system
	IFrameSystem* pIFrameSystem;


	// listeners

	// transform handler
	TransformListener transformListener;


	// managers

	// text style manager
	UniquePtr<TextStyleManager> pTextStyleManager;

	// texture manager
	UniquePtr<TextureManager> pTextureManager;

	// main menu handler
	MainMenu menu;

	// timer handler
	Timer timer;

	// border handler
	Border border;


	// archetypes

	// enemy archetype
	EnemyArchetype enemyArchetype;

	// pickup archetype
	PickupArchetype pickupArchetype;

	// blast archetype
	BlastArchetype blastArchetype;

	
	// operators

	// collider operator
	ColliderOperator colliderOp;


	// states

	// specifies if the game is currently playing;
	bool gameActive;

	// specifies if the game is on the main menu
	bool onMainMenu;

	// enemy spawn timer
	float enemySpawnCooldown, enemySpawnTimer;

	// pickup spawn timer
	float pickupSpawnCooldown, pickupSpawnTimer;


	// key entities

	// player entity
	Player player;


	// private methods

	// handle menu selection
	void handleMenuSelection();

	// handles menu controls
	void handleMenu();

	// sets game states and entities
	void setupGameState();

	// resets the game state and entities
	void resetGameState();

	// stops the game and presents the game over screen
	void gameOver(const std::string& cause = "The Architects");

	// calls gameover if the player's collider is outside of the border
	void enforceGameBorder();

	// adds tracking data to the specified entity to track another entity
	void addTracking(const Entity& entity, const Entity& tracked);

public:

	// constructor
	MainScene(): 
		
		// systems
		renderSystems		(),
		pVelocitySystem		(nullptr),
		pCollisionSystem	(nullptr),
		pThrustSystem		(nullptr),
		pControlSystem		(nullptr),
		pBoostSystem		(nullptr),
		pFuelAnimSystem		(nullptr),
		pTrackingSystem		(nullptr),
		pEnemyResetSystem	(nullptr),
		pPickupResetSystem	(nullptr),
		pBlastResetSystem	(nullptr),
		pSpawnSystem		(nullptr),
		pBlastSystem		(nullptr),
		pIFrameSystem		(nullptr),

		// listeners
		transformListener	(),

		// managers
		pTextStyleManager	(nullptr),
		menu				(),
		timer				(),
		border				(),

		// archetypes
		enemyArchetype		(),
		pickupArchetype		(),

		// operators
		colliderOp			(),

		// states
		gameActive			(false),
		onMainMenu			(true),
		enemySpawnCooldown	(Config::ENEMY_SPAWN_COOLDOWN),
		enemySpawnTimer		(0),
		pickupSpawnCooldown	(Config::PICKUP_SPAWN_COOLDOWN),
		pickupSpawnTimer	(Config::PICKUP_SPAWN_COOLDOWN),

		// key entities
		player				()
	{}

	// subscriber methods

	// handles collision events
	virtual void handleMessage(
		EntityCollided	message,
		MessageBroker*	broker
	);

	// scene methods

	// scene setup method - should set up all entities, components and systems
	// that will be used / displayed within the scene. this method is invoked
	// on transitioning to the scene, and is guaranteed to be run before the
	// scene update loop is run.
	virtual void setup();

	// scene update method - should specify the order in which systems are run
	// as well as handle other game logic that will be run every frame. this
	// method is invoked every frame, and constitutes the main update loop for
	// a particular scene. this method is guaranteed to not be run when the
	// scene is paused or halted, thus all updates within this loop will be
	// put in a sort of "stasis" until the scene is resumed.
	virtual void update(const float& deltaTime);

	// scene teardown method - should clean up all non-ecs objects or states
	// that the scene introduces over its lifecycle. (ecs-managed objects will
	// be handled automatically by the ecs system) this method is only invoked
	// when transitioning out of the scene, and will not be called if the
	// scene is paused or halted temporarily.
	virtual void teardown();

};

#endif // !_STV_SCENES_MAIN_H