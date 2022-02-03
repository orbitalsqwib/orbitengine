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
#include "../entityGroups/mainMenu.h"


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


	// listeners

	// transform handler
	TransformListener transformListener;


	// managers

	// text style manager
	UniquePtr<TextStyleManager> pTextStyleManager;

	// main menu handler
	MainMenu menu;


	// states

	// specifies if the game is currently playing;
	bool gameActive;

	// specifies if the game is on the main menu
	bool onMainMenu;


	// private methods

	// handle menu selection
	void handleMenuSelection();

	// sets game states and entities
	void setupGameState();

	// resets the game state and entities
	void resetGameState();

public:

	// constructor
	MainScene(): 
		
		// systems
		renderSystems		(),
		pVelocitySystem		(nullptr),
		pCollisionSystem	(nullptr),

		// listeners
		transformListener	(),

		// managers
		pTextStyleManager	(nullptr),
		menu				(),
		gameActive			(false),
		onMainMenu			(true)
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