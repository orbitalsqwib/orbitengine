// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Player Entity Group Specification
// ===========================================================================

#ifndef _STV_ENTITYGROUPS_PLAYER_H
#define _STV_ENTITYGROUPS_PLAYER_H

// import necessary headers
#include "../../orbitEngine/imports/ecs.h"
#include "../../orbitEngine/imports/graphics.h"
#include "../../orbitEngine/imports/components.h"
#include "../components/boostData.h"
#include "../components/fuelData.h"
#include "../components/directionData.h"
#include "../components/massData.h"
#include "../components/playerData.h"
#include "../components/playerControl.h"
#include "../components/thrustData.h"
#include <string>

// local constants
namespace {

	// player asset
	const LPCWSTR ASSET_PATH_PLAYER = L"./assets/ship.png";
	const std::string ASSET_NAME_PLAYER = "PLAYER_ASSET";

	// asset info
	const int ASSET_WIDTH_PLAYER	= 64;
	const int ASSET_HEIGHT_PLAYER	= 64;

	// entity dimensions
	const int RADIUS_PLAYER			= 16;
	const int DIAMETER_PLAYER		= RADIUS_PLAYER * 2;

	// player stats

	// thrust data
	const float PLAYER_THRUST_BASE		= 75;

	// boost data
	const float PLAYER_BOOST_MAXFUEL	= 2.5f;
	const float PLAYER_BOOST_RECOVERY	= 0.45f;
	const float PLAYER_BOOST_FWDTHRUST	= 75;
	const float PLAYER_BOOST_BCKTHRUST	= 45;
}


// main definition

// defines and manages the player entity
class Player
{
private:

	// members

	// player entity
	Entity player;

	// pointer reference to ecs instance
	ECSInstance* ecs;

	// pointer reference to graphics context
	GraphicsContext* graphics;

	// pointer reference to texture manager
	TextureManager* pTextureMgr;

	// initialization flag
	bool initialized;

public:

	// constructor
	Player(): 
		
		// members
		player		(ECS_INVALID_ENTITY),
		ecs			(nullptr),
		graphics	(nullptr),
		pTextureMgr	(nullptr),
		initialized	(false)
	{}

	// initializer
	void initialize (
		ECSInstance&		_ecs,
		GraphicsContext&	_graphics,
		TextureManager*		_pTextureMgr
	) {
		// update states
		ecs = &_ecs;
		graphics = &_graphics;
		pTextureMgr = _pTextureMgr;

		// setup player textures
		pTextureMgr->addTexture(
			ASSET_NAME_PLAYER,
			TextureData(ASSET_PATH_PLAYER)
		);

		// register player data component
		ecs->registerComponent<PlayerData>();

		// update initialization flag
		initialized = true;
	}


	// methods

	// builds the player instance
	void create()
	{
		// ensure player has been initialized
		if (!initialized) throw Error("Error: Player not initialized!");

		// ! create player
		player = ecs->createEntity();
		ecs->addComponent<PlayerData>(player, PlayerData());


		// ! create player sprite

		// setup temporary sprite operator
		AnimSpriteOperator animOp(graphics);

		// calculate x and y positions
		float x = (float(graphics->getDisplayWidth()) - DIAMETER_PLAYER) / 2;
		float y = (float(graphics->getDisplayHeight()) - DIAMETER_PLAYER) / 2;

		// build ship sprite
		SpriteData shipSprite(
			x,
			y,
			ZValues::FOREGROUND,
			ASSET_WIDTH_PLAYER,
			ASSET_HEIGHT_PLAYER,
			0,
			float(DIAMETER_PLAYER) / float(ASSET_WIDTH_PLAYER),
			{ 0, 0, ASSET_WIDTH_PLAYER, ASSET_HEIGHT_PLAYER },
			pTextureMgr->getTextureData(ASSET_NAME_PLAYER)
		);

		// select sprite frame
		animOp.updateSpriteForAnimation(
			AnimSpriteData(0, 0, 4, 0, 0, 5),
			shipSprite
		);

		// add sprite data to player entity
		ecs->addComponent<SpriteData>(player, shipSprite);


		// ! create player collider
		ecs->addComponent<ColliderData>(player,
			ColliderData("player", x, y, RADIUS_PLAYER)
		);


		// ! create player kinematics

		// add position component
		ecs->addComponent<PositionData>(player,
			PositionData(x, y, DIAMETER_PLAYER, DIAMETER_PLAYER)
		);

		// add velocity component
		ecs->addComponent<VelocityData>(player, VelocityData());

		// add mass component
		ecs->addComponent<MassData>(player, MassData());

		// add thrust component
		ecs->addComponent<ThrustData>(player, ThrustData(PLAYER_THRUST_BASE));

		// add direction component (-90 from 0 (align to x-axis) is upwards)
		ecs->addComponent<DirectionData>(player, 
			DirectionData(D3DXToRadian(-90))
		);

		// add boost component
		ecs->addComponent<BoostData>(player, BoostData(
			PLAYER_BOOST_FWDTHRUST,
			PLAYER_BOOST_BCKTHRUST
		));

		// add fuel component
		ecs->addComponent<FuelData>(player, FuelData(
			PLAYER_BOOST_MAXFUEL,
			PLAYER_BOOST_RECOVERY
		));


		// ! add player control component
		ecs->addComponent<PlayerControl>(player, PlayerControl());
	}

	// destroys the player instance
	void destroy()
	{
		// destroy entity if it exists
		if (player != ECS_INVALID_ENTITY) ecs->destroyEntity(player);

		// reset player entity
		player = ECS_INVALID_ENTITY;
	}
	
	// resets the player instance
	void reset()
	{
		// destroy instance
		destroy();

		// rebuild instance
		create();
	}

	// returns the life state of the player
	bool isAlive() { return player != ECS_INVALID_ENTITY; }

	// returns the entity for the player
	Entity getEntity() { return player; }

};

#endif // !_STV_ENTITYGROUPS_PLAYER_H