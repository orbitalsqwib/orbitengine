// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Player Control System Specification
// ===========================================================================

#ifndef _STV_SYSTEMS_CONTROLSYSTEM_H
#define _STV_SYSTEMS_CONTROLSYSTEM_H

// import necessary headers
#include "../config.h"
#include "../components/playerControl.h"
#include "../components/directionData.h"
#include "../components/boostData.h"
#include "../components/iframeData.h"
#include "../components/fuelData.h"
#include "../../orbitEngine/imports/ecs.h"
#include "../../orbitEngine/imports/graphics.h"
#include "../../orbitEngine/imports/messaging.h"
#include "../../orbitEngine/imports/engine.h"

// constants
namespace {

	// keys
	const UCHAR W_KEY = 0x57;
	const UCHAR A_KEY = 0x41;
	const UCHAR S_KEY = 0x53;
	const UCHAR D_KEY = 0x44;
	const UCHAR E_KEY = 0x45;

}


// main definition

// renders entities with a sprite data component
class ControlSystem : public System
{
private:

	// members

	// pointer reference to scene broker
	MessageBroker* sceneBroker;

	// pointer reference to keyboard state
	KeyboardState* keyboard;


	// private methods

	// update the bonus thrust of all relevant entities
	void updateBoost(const bool& _speedUp, const bool& _active)
	{
		// initialize iterator
		ENTITY_SET::iterator it;

		// loop through all relevant entities
		for (it = entities.begin(); it != entities.end(); it++)
		{
			// update boost component for entity
			if (BoostData* pBoost = ecs->getComponent<BoostData>(*it))
			{
				pBoost->speedUp = _speedUp;
				pBoost->active = _active;
			}
		}
	}

	// update the direction of all relevant entities
	void addRotation(float _incrementVal)
	{
		// initialize iterator
		ENTITY_SET::iterator it;

		// loop through all relevant entities
		for (it = entities.begin(); it != entities.end(); it++)
		{
			// update direction component for entity
			if (DirectionData* pDir = ecs->getComponent<DirectionData>(*it))
			{
				pDir->rotation += _incrementVal;
			}

			// send rotate command if scene broker is attached
			if (sceneBroker) sceneBroker->pushImmediately(
				RotateCommand(*it, _incrementVal, true)
			);
		}
	}

	// attempts to add an iframe to all relevant entities
	void addIFrames()
	{
		// initialize iterator
		ENTITY_SET::iterator it;

		// loop through all relevant entities
		for (it = entities.begin(); it != entities.end(); it++)
		{
			// attempt to convert 90% of fuel to an iframe
			if (FuelData* pFuel = ecs->getComponent<FuelData>(*it))
			{
				// ensure enough fuel exists, else skip iteration
				if ((pFuel->fuel / pFuel->maxFuel) 
					< Config::PLAYER_IFRAME_FUEL_COST)
				continue;
				
				// consume fuel for iframe
				pFuel->fuel = max(
					pFuel->fuel - pFuel->maxFuel 
						* Config::PLAYER_IFRAME_FUEL_COST,
					0
				);

				// add iframe component
				ecs->addComponent<IFrameData>(*it,
					IFrameData(Config::PLAYER_IFRAME_DURATION)
				);
			}
		}
	}

public:

	// constructor
	ControlSystem(): sceneBroker(nullptr), keyboard(nullptr) {}

	// initializer - sceneBroker should be bound to the same broker as
	// the transform system.
	void initialize(MessageBroker& _sceneBroker, KeyboardState& _keyboard)
	{
		// bind scene broker
		sceneBroker = &_sceneBroker;

		// bind keyboard state
		keyboard = &_keyboard;
	}


	// sets the signature for the system
	void setSignature(
		ECSInstance& ecs
	) {
		// register components (if not already registered)
		ecs.registerComponent<PlayerControl>();

		// set system signature
		Signature s;
		s.set(ecs.getTypeEnum<PlayerControl>(), true);
		ecs.setSignature<ControlSystem>(s);
	}

	// handle user controls
	void handleUserInputs(const float& deltaTime)
	{
		// ensure keyboard input exists, else exit early
		if (!keyboard) return;

		// handle user inputs

		// handle speed up
		if (keyboard->isKeyDown(W_KEY))
		{
			updateBoost(true, true);
		}
		else if (keyboard->isKeyDown(S_KEY))
		{
			updateBoost(false, true);
		}
		else
		{
			updateBoost(true, false);
		}

		// handle turning
		if (keyboard->isKeyDown(A_KEY))
		{
			// rotate anticlockwise
			addRotation(deltaTime * D3DXToRadian(-Config::PLAYER_TURN_SPEED));
		}
		else if (keyboard->isKeyDown(D_KEY))
		{
			// rotate clockwise
			addRotation(deltaTime * D3DXToRadian(Config::PLAYER_TURN_SPEED));
		}

		// handle iframe cast
		if (keyboard->wasKeyPressed(E_KEY))
		{
			// attempt to add iframes for controlled entities by consuming
			// an appropriate percentage of their current fuel.
			addIFrames();
		}
	}

};

#endif // !_STV_SYSTEMS_CONTROLSYSTEM_H