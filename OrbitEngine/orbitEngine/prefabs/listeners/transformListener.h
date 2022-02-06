// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Transform System Specification
// ===========================================================================

#ifndef _ORBIT_PREFABS_TRANSFORMSYSTEM_H
#define _ORBIT_PREFABS_TRANSFORMSYSTEM_H

// import necessary headers
#include "../../ecs/ecs.h"
#include "../../graphics/components.h"
#include "../../graphics/operators.h"
#include "../../collisions/colliderData.h"
#include "../../utils/pointers.h"
#include "../components/positionData.h"
#include "../../messaging/pubsub.h"
#include "../commands/moveCommand.h"
#include "../commands/rotateCommand.h"


// main definition

// handles transforms made on entities with basic data components, including
// position, collision and graphics components.
class TransformListener:
	public ISubscriber<MoveCommand>,
	public ISubscriber<RotateCommand>
{
private:

	// members

	// reference to scene ecs instance
	ECSInstance* ecs;

public:

	// constructor
	TransformListener() : ecs(nullptr) {}

	// initializer
	void initialize(ECSInstance& ecs, MessageBroker& sceneBroker)
	{
		// bind ecs access
		this->ecs = &ecs;

		// subscribe listener to scene broker for transform commands
		sceneBroker.addSubscriber<MoveCommand>(*this);
		sceneBroker.addSubscriber<RotateCommand>(*this);
	}


	// subscriber methods

	// should handle incoming messages and make changes to the object's state
	// or behaviour as necessary. may provide a pointer to the message broker
	// that invoked this event, which should be null-checked prior to use.
	virtual void handleMessage(
		MoveCommand		message,
		MessageBroker*	broker
	) {
		// attempt to update position data component for entity
		if (PositionData* pC = ecs->getComponent<PositionData>(message.entity))
		{
			// update component position
			pC->x = message.relative ? pC->x + message.x : message.x;
			pC->y = message.relative ? pC->y + message.y : message.y;
		}

		// attempt to update collider data component for entity
		if (ColliderData* pC = ecs->getComponent<ColliderData>(message.entity))
		{
			// update component position for relative movement
			if (message.relative)
			{
				// get component position
				const Vec2& currPos = pC->getPos();

				// update position
				pC->setPos(message.x + currPos.x, message.y + currPos.y);
			}

			// else set component position for absolute movement
			else pC->setPos(message.x, message.y);
		}

		// attempt to update shape data component for entity
		if (ShapeData* pC = ecs->getComponent<ShapeData>(message.entity))
		{
			// update component position
			pC->x = message.relative ? pC->x + message.x : message.x;
			pC->y = message.relative ? pC->y + message.y : message.y;
		}

		// attempt to update sprite data component for entity
		if (SpriteData* pC = ecs->getComponent<SpriteData>(message.entity))
		{
			// update component position
			pC->x = message.relative ? pC->x + message.x : message.x;
			pC->y = message.relative ? pC->y + message.y : message.y;
		}

		// attempt to update text data component for entity
		if (TextData* pC = ecs->getComponent<TextData>(message.entity))
		{
			// update component position
			pC->x = message.relative ? pC->x + message.x : message.x;
			pC->y = message.relative ? pC->y + message.y : message.y;
		}
	}

	// should handle incoming messages and make changes to the object's state
	// or behaviour as necessary. may provide a pointer to the message broker
	// that invoked this event, which should be null-checked prior to use.
	virtual void handleMessage(
		RotateCommand	message,
		MessageBroker*	broker
	) {
		// attempt to update sprite data component for entity
		if (SpriteData* pC = ecs->getComponent<SpriteData>(message.entity))
		{
			// update component angle
			pC->angle = message.relative 
				? pC->angle + message.angle 
				: message.angle;
		}

		// attempt to update collider data component for entity
		if (ColliderData* pC = ecs->getComponent<ColliderData>(message.entity))
		{
			// update component angle
			pC->setRotation(
				message.relative
					? pC->getRotation() + message.angle
					: message.angle
			);
		}
	}

};

#endif // !_ORBIT_PREFABS_GRAPHICSTRANSFORMSYSTEM_H