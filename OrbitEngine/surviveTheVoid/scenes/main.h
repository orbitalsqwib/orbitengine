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
#include "../../orbitEngine/imports/commons.h"
#include "../../orbitEngine/imports/scene.h"
#include "../../orbitEngine/imports/systems.h"
#include "../../orbitEngine/imports/graphics.h"
#include "../systems/controlSystem.h"
#include "../systems/thrustSystem.h"
#include "../systems/trackingSystem.h"
#include "../systems/boostSystem.h"
#include "../systems/boostAnimSystem.h"
#include "../entityGroups/mainMenu.h"
#include "../entityGroups/player.h"
#include "../entityGroups/timer.h"
#include "../handlers/border.h"
#include <math.h>

// local constants
namespace {

	// asset filepaths
	const LPCWSTR ASSET_SHIP = L"./assets/ship.png";


	// asset info

	// ship
	const int ASSET_SHIP_HEIGHT = 64;
	const int ASSET_SHIP_WIDTH	= 64;


	// entity info

	// ship
	const int HEIGHT_SHIP		= 32;
	const int WIDTH_SHIP		= 32;

}


// main definition

class MainScene : public Scene
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

	// boost animation system
	BoostAnimSystem* pBoostAnimSystem;


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

	
	// operators

	// collider operator
	ColliderOperator colliderOp;


	// states

	// specifies if the game is currently playing;
	bool gameActive;

	// specifies if the game is on the main menu
	bool onMainMenu;


	// key entities

	// player entitiy
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
		pBoostAnimSystem	(nullptr),

		// listeners
		transformListener	(),

		// managers
		pTextStyleManager	(nullptr),
		menu				(),
		gameActive			(false),
		onMainMenu			(true),

		// key entities
		player				()
	{}

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