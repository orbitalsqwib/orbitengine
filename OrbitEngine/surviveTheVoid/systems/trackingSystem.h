// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Tracking System Specification
// ===========================================================================

#ifndef _STV_SYSTEMS_TRACKINGSYSTEM_H
#define _STV_SYSTEMS_TRACKINGSYSTEM_H

// import necessary headers
#include "../components/directionData.h"
#include "../components/trackingData.h"
#include "../../orbitEngine/imports/ecs.h"
#include "../../orbitEngine/imports/components.h"


// main definition

// renders entities with a sprite data component
class TrackingSystem : public System
{
public:

	// sets the signature for the system
	void setSignature(
		ECSInstance& ecs
	) {
		// register components (if not already registered)
		ecs.registerComponent<TrackingData>();
		ecs.registerComponent<DirectionData>();
		ecs.registerComponent<PositionData>();

		// set system signature
		Signature s;
		s.set(ecs.getTypeEnum<TrackingData>(), true);
		s.set(ecs.getTypeEnum<DirectionData>(), true);
		s.set(ecs.getTypeEnum<PositionData>(), true);
		ecs.setSignature<TrackingSystem>(s);
	}

	// updates entity direction according to tracked entity's relative pos.
	void updateDirection()
	{
		// initialize iterator
		ENTITY_SET::iterator it;

		// loop through all relevant entities
		for (it = entities.begin(); it != entities.end(); it++)
		{
			// retrieve components for entity
			TrackingData* pTrack = ecs->getComponent<TrackingData>(*it);
			DirectionData* pDir = ecs->getComponent<DirectionData>(*it);
			PositionData* pThisPos = ecs->getComponent<PositionData>(*it);

			// ensure components exist, else skip to next iteration
			if (!pTrack || !pDir) continue;

			// attempt to retrieve position component for tracked entity
			Entity tracked = pTrack->tracked;
			PositionData* pTrackPos = ecs->getComponent<PositionData>(tracked);

			// ensure position data for tracked entity exists, else skip
			if (!pTrackPos) continue;

			// get vector of this->track = normalized(AB = OB - OA), where
			// OA = this entity's pos, OB = tracked entity's pos
			Vec2 trackUV (
				pTrackPos->x - pThisPos->x,
				pTrackPos->y - pThisPos->y
			);

			// A * B = |a||b|cos0
			// when A and B are normalized, A * B = (1)(1)cos0 = cos0
			// thus, the angle 0 between the two vectors = acos(A * B)

			// normalize UV
			Vec2Math::normalize(&trackUV);

			// get normalized UV for normal dir.
			Vec2 normal(1.0f, 0.0f);

			// get rotation from normal
			float rTheta = acos(Vec2Math::dot(&trackUV, &normal));

			// update direction rotation
			pDir->rotation = rTheta;
		}
	}

};

#endif // !_STV_SYSTEMS_TRACKINGSYSTEM_H