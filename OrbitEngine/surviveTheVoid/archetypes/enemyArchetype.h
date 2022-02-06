// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Enemy Archetype Specification
// ===========================================================================

#ifndef _STV_ARCHETYPES_ENEMYARCHETYPE_H
#define _STV_ARCHETYPES_ENEMYARCHETYPE_H

// import necessary headers
#include "IArchetype.h"
#include "../../orbitEngine/imports/ecs.h"
#include "../../orbitEngine/imports/graphics.h"
#include "../../orbitEngine/imports/components.h"
#include "../components/directionData.h"
#include "../components/massData.h"
#include "../components/enemyData.h"
#include "../components/thrustData.h"
#include "../components/trackingData.h"
#include <string>

// local constants
namespace {

	// enemy asset
	const LPCWSTR ASSET_PATH_ENEMY = L"./assets/enemy.png";
	const std::string ASSET_NAME_ENEMY = "ENEMY_ASSET";

	// asset info
	const int ASSET_WIDTH_ENEMY		= 64;
	const int ASSET_HEIGHT_ENEMY	= 64;

	// entity dimensions
	const int RADIUS_ENEMY			= 16;
	const int DIAMETER_ENEMY		= RADIUS_ENEMY * 2;

	// enemy stats

	// thrust data
	const float ENEMY_THRUST_BASE	= 200;
}


// main definition

// defines the entity archetype for enemies
class EnemyArchetype : public IArchetype
{
private:

	// members

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
	EnemyArchetype():

		// members
		ecs			(nullptr),
		graphics	(nullptr),
		pTextureMgr	(nullptr),
		initialized	(false)
	{}

	// initializer
	void initialize(
		ECSInstance&		_ecs,
		GraphicsContext&	_graphics,
		TextureManager*		_pTextureMgr
	) {
		// update states
		ecs = &_ecs;
		graphics = &_graphics;
		pTextureMgr = _pTextureMgr;

		// setup enemy textures
		pTextureMgr->addTexture(
			ASSET_NAME_ENEMY,
			TextureData(ASSET_PATH_ENEMY)
		);

		// register enemy data component
		ecs->registerComponent<EnemyData>();

		// update initialization flag
		initialized = true;
	}


	// methods

	// spawns an enemy at the given coordinates
	virtual Entity spawn(
		const float& x,
		const float& y
	) {
		// ensure entity has been initialized
		if (!initialized) throw Error(
			"Error: Enemy archetype not initialized!"
		);

		// ! create enemy
		Entity newEnemy = ecs->createEntity();
		ecs->addComponent<EnemyData>(newEnemy, EnemyData());


		// ! create enemy sprite

		// setup temporary sprite operator
		AnimSpriteOperator animOp(graphics);

		// build ship sprite
		SpriteData enemySprite(
			x,
			y,
			ZValues::FOREGROUND,
			ASSET_WIDTH_ENEMY,
			ASSET_HEIGHT_ENEMY,
			0,
			float(DIAMETER_ENEMY) / float(ASSET_WIDTH_ENEMY),
			{ 0, 0, ASSET_WIDTH_ENEMY, ASSET_HEIGHT_ENEMY },
			pTextureMgr->getTextureData(ASSET_NAME_ENEMY)
		);

		// select sprite frame
		animOp.updateSpriteForAnimation(
			AnimSpriteData(0, 0, 1, 0, 0, 5),
			enemySprite
		);

		// add sprite data to enemy entity
		ecs->addComponent<SpriteData>(newEnemy, enemySprite);


		// ! create enemy collider (circle)
		ecs->addComponent<ColliderData>(newEnemy,
			ColliderData("enemy", x, y, RADIUS_ENEMY)
		);


		// ! create enemy kinematics

		// add position component
		ecs->addComponent<PositionData>(newEnemy,
			PositionData(x, y, DIAMETER_ENEMY, DIAMETER_ENEMY)
		);

		// add velocity component
		ecs->addComponent<VelocityData>(newEnemy, VelocityData());

		// add mass component
		ecs->addComponent<MassData>(newEnemy, MassData(4));

		// add thrust component
		ecs->addComponent<ThrustData>(newEnemy, ThrustData(ENEMY_THRUST_BASE));

		// add direction component (-90 from 0 (align to x-axis) is upwards)
		ecs->addComponent<DirectionData>(newEnemy,
			DirectionData(D3DXToRadian(-90))
		);

		// return spawned enemy
		return newEnemy;
	}

	// should return the entity's width at spawn time
	virtual float getWidth() { return RADIUS_ENEMY; };

	// should return the entity's height at spawn time
	virtual float getHeight() { return RADIUS_ENEMY; };

};

#endif // !_STV_ARCHETYPES_ENEMYARCHETYPE_H