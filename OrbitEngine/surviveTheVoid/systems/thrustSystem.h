// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Thrust System Specification
// ===========================================================================

#ifndef _STV_SYSTEMS_THRUSTSYSTEM_H
#define _STV_SYSTEMS_THRUSTSYSTEM_H

// import necessary headers
#include "../components/directionData.h"
#include "../components/massData.h"
#include "../components/thrustData.h"
#include "../../orbitEngine/imports/ecs.h"
#include "../../orbitEngine/imports/components.h"


// main definition

// handles thrust physics for entities
class ThrustSystem : public System
{
public:

	// sets the signature for the system
	void setSignature(
		ECSInstance& ecs
	) {
		// register components (if not already registered)
		ecs.registerComponent<VelocityData>();
		ecs.registerComponent<DirectionData>();
		ecs.registerComponent<MassData>();
		ecs.registerComponent<ThrustData>();

		// set system signature
		Signature s;
		s.set(ecs.getTypeEnum<VelocityData>(), true);
		s.set(ecs.getTypeEnum<DirectionData>(), true);
		s.set(ecs.getTypeEnum<MassData>(), true);
		s.set(ecs.getTypeEnum<ThrustData>(), true);
		ecs.setSignature<ThrustSystem>(s);
	}

	// applies thrust to entities with respect to direction and mass through
	// updating velocity (which will be applied in the next frame)
	void applyThrust()
	{
		// initialize iterator
		ENTITY_SET::iterator it;

		// loop through all relevant entities
		for (it = entities.begin(); it != entities.end(); it++)
		{
			// retrieve components
			VelocityData*	pVel	= ecs->getComponent<VelocityData>	(*it);
			DirectionData*	pDir	= ecs->getComponent<DirectionData>	(*it);
			MassData*		pMass	= ecs->getComponent<MassData>		(*it);
			ThrustData*		pThrust = ecs->getComponent<ThrustData>		(*it);

			// ensure components exist, else skip to next iteration
			if (!pVel || !pDir || !pMass || !pThrust) continue;

			// check that thrust is active, else skip to next iteration
			if (!pThrust->active) continue;

			// calculate direction vector of force applied
			// dir. vec. =	[cos0  -sin0][x (1)]
			//				[sin0   cos0][y (0)]
			//			 =	[cos0]
			//				[sin0]

			float theta = pDir->rotation;
			float uvX = cos(theta);
			float uvY = sin(theta);

			// ===============================================================
			// velocity(res) = velocity(initial) + acceleration * time
			// v(res) = (0) + acceleration * (1s)
			// v(res) = acceleration
			// ===============================================================
			// force = mass * acceleration
			// acceleration = force / mass
			// v(res) = force / mass
			// ===============================================================

			// calculate total thrust force
			float fRes
				= (pThrust->baseThrust + pThrust->bonusThrust)
				* pThrust->thrustScale;

			// reset bonus thrust for the frame
			pThrust->bonusThrust = 0;

			// calculate instantaneous velocity
			float vRes = fRes / pMass->mass;

			// apply velocity according to direction
			pVel->dx += vRes * uvX;
			pVel->dy += vRes * uvY;
		}
	}

};

#endif // !_STV_SYSTEMS_THRUSTSYSTEM_H