// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Collision System Specification
// ===========================================================================

#ifndef _ORBIT_PREFABS_VELOCITYSYSTEM_H
#define _ORBIT_PREFABS_VELOCITYSYSTEM_H

// import necessary headers
#include "../../ecs/ecs.h"
#include "../components/velocityData.h"
#include "../commands/moveCommand.h"
#include "../../messaging/pubsub.h"


// main definition

class VelocitySystem : public System
{
private:

	// members

	// pointer to scene broker
	MessageBroker* sceneBroker;

	// initialization flag
	bool initialized;

public:

	// constructor
	VelocitySystem(): sceneBroker(nullptr), initialized(false) {}

	// initializer
	void initialize(
		MessageBroker&	_sceneBroker
	) {
		// bind scene broker to system for move commands
		sceneBroker = &_sceneBroker;

		// update status
		initialized = true;
	}

	// sets the signature for the system
	void setSignature(
		ECSInstance&	ecs
	) {
		// register components with ecs (if not already registered)
		ecs.registerComponent<VelocityData>();

		// set system signature
		Signature s;
		s.set(ecs.getTypeEnum<VelocityData>(), true);
		ecs.setSignature<VelocitySystem>(s);
	}

	// updates entity positions based on velocity 
	void applyVelocities(const float& deltaTime)
	{
		// initialize iterator
		ENTITY_SET::iterator it;

		// loop through all relevant entities
		for (it = entities.begin(); it != entities.end(); it++)
		{
			// get velocity component for subject entity
			VelocityData* velocity = ecs->getComponent<VelocityData>(*it);

			// ensure velocity component for subject exists, else skip to next
			if (!velocity) continue;

			// apply move command to each entity based on velocity
			sceneBroker->pushImmediately(
				MoveCommand(
					*it, 
					velocity->dx * deltaTime, 
					velocity->dy * deltaTime, 
					true
				)
			);

			// reset velocity component after applying movement updates
			velocity->dx = velocity->dy = 0;
		}
	}

};

#endif // !_ORBIT_PREFABS_VELOCITYSYSTEM_H