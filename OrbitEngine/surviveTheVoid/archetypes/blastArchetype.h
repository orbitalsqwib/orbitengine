// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Blast Archetype Specification
// ===========================================================================

#ifndef _STV_ARCHETYPES_BLASTARCHETYPE_H
#define _STV_ARCHETYPES_BLASTARCHETYPE_H

// import necessary headers
#include "IArchetype.h"
#include "../../orbitEngine/imports/ecs.h"
#include "../../orbitEngine/imports/graphics.h"
#include "../../orbitEngine/imports/components.h"
#include "../components/blastData.h"
#include <string>

// local constants
namespace {

	// player asset
	const LPCWSTR ASSET_PATH_BLAST = L"./assets/circleOutline.png";
	const std::string ASSET_NAME_BLAST = "BLAST_ASSET";

	// asset info
	const int ASSET_WIDTH_BLAST		= 256;
	const int ASSET_HEIGHT_BLAST	= 256;
}


// main definition

// defines the entity archetype for blasts
class BlastArchetype
{
private:

	// members

	// pointer reference to ecs instance
	ECSInstance* ecs;

	// pointer reference to texture manager
	TextureManager* pTextureMgr;

	// initialization flag
	bool initialized;

public:

	// constructor
	BlastArchetype():

		// members
		ecs			(nullptr),
		pTextureMgr	(nullptr),
		initialized	(false)
	{}

	// initializer
	void initialize(
		ECSInstance&		_ecs,
		TextureManager*		_pTextureMgr
	) {
		// update states
		ecs = &_ecs;
		pTextureMgr = _pTextureMgr;

		// setup blast textures
		pTextureMgr->addTexture(
			ASSET_NAME_BLAST,
			TextureData(ASSET_PATH_BLAST)
		);

		// register blast data component
		ecs->registerComponent<BlastData>();

		// update initialization flag
		initialized = true;
	}


	// methods

	// spawns a blast at the given coordinates
	virtual Entity spawn(
		const float& centerX,
		const float& centerY,
		const float& blastRadius,
		const float& blastTime
	) {
		// convert center x and y to top-left x and y
		float x = centerX - blastRadius;
		float y = centerY - blastRadius;

		// get blast diameter
		float blastDiameter = blastRadius * 2;

		// ensure entity has been initialized
		if (!initialized) throw Error(
			"Error: Blast archetype not initialized!"
		);

		// ! create blast
		Entity newBlast = ecs->createEntity();
		ecs->addComponent<BlastData>(newBlast, BlastData(
			blastTime, 
			blastRadius, 
			blastRadius * 2 / ASSET_WIDTH_BLAST
		));


		// ! create blast sprite

		// build ship sprite
		SpriteData blastSprite(
			x,
			y,
			ZValues::BACKGROUND,
			ASSET_WIDTH_BLAST,
			ASSET_HEIGHT_BLAST,
			0,
			0,
			{ 0, 0, ASSET_WIDTH_BLAST, ASSET_HEIGHT_BLAST },
			pTextureMgr->getTextureData(ASSET_NAME_BLAST)
		);

		// set relative positions
		blastSprite.relX = blastRadius;
		blastSprite.relY = blastRadius;

		// add sprite data to player entity
		ecs->addComponent<SpriteData>(newBlast, blastSprite);


		// ! create blast collider (circle)
		ColliderData blastCollider("blast", x, y, blastRadius);

		// set scale
		blastCollider.setScale(0);

		// add collider to blast
		ecs->addComponent<ColliderData>(newBlast, blastCollider);


		// return spawned blast
		return newBlast;
	}

};

#endif // !_STV_ARCHETYPES_BLASTARCHETYPE_H