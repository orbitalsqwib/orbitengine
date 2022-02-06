// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Pickup Archetype Specification
// ===========================================================================

#ifndef _STV_ARCHETYPES_PICKUPARCHETYPE_H
#define _STV_ARCHETYPES_PICKUPARCHETYPE_H

// import necessary headers
#include "IArchetype.h"
#include "../../orbitEngine/imports/ecs.h"
#include "../../orbitEngine/imports/graphics.h"
#include "../../orbitEngine/imports/components.h"
#include "../components/pickupData.h"
#include <string>

// local constants
namespace {

	// player asset
	const LPCWSTR ASSET_PATH_PICKUP = L"./assets/pickup.png";
	const std::string ASSET_NAME_PICKUP = "PICKUP_ASSET";

	// asset info
	const int ASSET_WIDTH_PICKUP	= 64;
	const int ASSET_HEIGHT_PICKUP	= 64;

	// entity dimensions
	const int RADIUS_PICKUP			= 16;
	const int DIAMETER_PICKUP		= RADIUS_PICKUP * 2;
}


// main definition

// defines the entity archetype for pickups
class PickupArchetype : public IArchetype
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
	PickupArchetype() :

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

		// setup pickup textures
		pTextureMgr->addTexture(
			ASSET_NAME_PICKUP,
			TextureData(ASSET_PATH_PICKUP)
		);

		// register pickup data component
		ecs->registerComponent<PickupData>();

		// update initialization flag
		initialized = true;
	}


	// methods

	// spawns an pickup at the given coordinates
	virtual Entity spawn(
		const float& x,
		const float& y
	) {
		// ensure entity has been initialized
		if (!initialized) throw Error(
			"Error: Pickup archetype not initialized!"
		);

		// ! create pickup
		Entity newPickup = ecs->createEntity();
		ecs->addComponent<PickupData>(newPickup, PickupData());


		// ! create pickup sprite

		// setup temporary sprite operator
		AnimSpriteOperator animOp(graphics);

		// build ship sprite
		SpriteData pickupSprite(
			x,
			y,
			ZValues::BACKGROUND,
			ASSET_WIDTH_PICKUP,
			ASSET_HEIGHT_PICKUP,
			0,
			float(DIAMETER_PICKUP) / float(ASSET_WIDTH_PICKUP),
			{ 0, 0, ASSET_WIDTH_PICKUP, ASSET_HEIGHT_PICKUP },
			pTextureMgr->getTextureData(ASSET_NAME_PICKUP),
			0,
			0,
			Colors::LIME
		);

		// select sprite frame
		animOp.updateSpriteForAnimation(
			AnimSpriteData(0, 0, 0, 0, 0, 5),
			pickupSprite
		);

		// add sprite data to player entity
		ecs->addComponent<SpriteData>(newPickup, pickupSprite);


		// ! create pickup collider (circle)
		ecs->addComponent<ColliderData>(newPickup,
			ColliderData("pickup", x, y, RADIUS_PICKUP)
		);


		// ! add pickup position

		// add position component
		ecs->addComponent<PositionData>(newPickup,
			PositionData(x, y, DIAMETER_PICKUP, DIAMETER_PICKUP)
		);

		// return spawned pickup
		return newPickup;
	}

	// should return the entity's width at spawn time
	virtual float getWidth() { return RADIUS_PICKUP; };

	// should return the entity's height at spawn time
	virtual float getHeight() { return RADIUS_PICKUP; };

};

#endif // !_STV_ARCHETYPES_PICKUPARCHETYPE_H