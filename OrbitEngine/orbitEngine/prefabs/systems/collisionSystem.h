// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Collision System Specification
// ===========================================================================

#ifndef _ORBIT_PREFABS_COLLISIONSYSTEM_H
#define _ORBIT_PREFABS_COLLISIONSYSTEM_H

// import necessary headers
#include "../notifications/entityCollided.h"
#include "../../ecs/ecs.h"
#include "../../collisions/colliderData.h"
#include "../../collisions/colliderOperator.h"


// main definition

// renders entities with a text data component
class CollisionSystem : public System
{
private:

	// collider operator
	ColliderOperator colliderOp;

	// collision message queue
	MessageBroker collisionBroker;

	// debug initialization flag
	bool debugReady;

public:

	// constructor
	CollisionSystem() : colliderOp(), collisionBroker(), debugReady(false) {}

	// sets the signature for the system
	void setSignature(
		ECSInstance& ecs
	) {
		// add collider data component to ecs
		ecs.registerComponent<ColliderData>();

		// set system signature
		Signature s;
		s.set(ecs.getTypeEnum<ColliderData>(), true);
		ecs.setSignature<CollisionSystem>(s);
	}

	// adds a collision handler to the system
	void addCollisionHandler(ISubscriber<EntityCollided>& listener)
	{
		// subscribe handler to broker, gets notified for batches of checks
		collisionBroker.addSubscriber(listener);
	}

	// general collision check method, targets all entities with tag - o(n!)
	void checkAllCollisions(const char targetTag[32])
	{
		// copy entity set to collider set
		ENTITY_SET colliderSet = entities;

		// while collider set still has entities,
		while (!colliderSet.empty())
		{
			// let first entity in set be the collision subject
			// let other entities in set be the collision target

			// setup iterator
			ENTITY_SET::iterator it = colliderSet.begin();

			// cache entity id for subject
			Entity subject = *it;

			// setup collision vector container
			Vec2 cV;

			// get collider component for subject entity
			ColliderData* cSub = ecs->getComponent<ColliderData>(*it);
			
			// ensure collider component for subject exists, else skip to next
			if (!cSub) continue;

			// check collisions from each entity in the set after subject
			for (it++; it != colliderSet.end(); it++)
			{
				// get collider component for target entity
				ColliderData* cTgt = ecs->getComponent<ColliderData>(*it);

				// ensure collider for target exists, else skip to next target
				if (!cTgt) continue;

				// ensure target's tag matches targetTag, else skip target
				if (cTgt->getTag() != targetTag) continue;

				// check collision between both entities from subject's persp.
				if (colliderOp.collide(*cSub, *cTgt, cV))
				{
					// entities did collide, send collision events to queue
					collisionBroker.queue(
						EntityCollided(subject, *it, targetTag, cV)
					);
					collisionBroker.queue(
						EntityCollided(*it, subject, targetTag, cV * -1)
					);
				}

				// increment iterator
				it++;
			}

			// once all collisions checked, remove subject from collider set
			colliderSet.erase(subject);
		}

		// once all collisions processed, tell handlers to process events
		collisionBroker.processAllMessages();
	}

	// targeted collision check method, targets all entities with tag - o(n)
	void checkCollisions(const Entity& subject, const char targetTag[32])
	{
		// get collider component for subject entity
		ColliderData* cSub = ecs->getComponent<ColliderData>(subject);

		// ensure collider component for subject exists, else exit early
		if (!cSub) return;

		// setup collision vector container
		Vec2 cV;

		// initialize iterator
		ENTITY_SET::iterator it;

		// check collisions for each entity with the target tag
		for (it++; it != entities.end(); it++)
		{
			// check that entity at iterator is not subject, else skip to next
			if (*it == subject) continue;

			// get collider component for target entity
			ColliderData* cTgt = ecs->getComponent<ColliderData>(*it);

			// ensure collider for target exists, else skip to next target
			if (!cTgt) continue;

			// ensure target's tag matches targetTag, else skip target
			if (cTgt->getTag() != targetTag) continue;

			// check collision between both entities from subject's persp.
			if (colliderOp.collide(*cSub, *cTgt, cV))
			{
				// entities did collide, send collision events to queue
				collisionBroker.queue(
					EntityCollided(subject, *it, targetTag, cV)
				);
				collisionBroker.queue(
					EntityCollided(*it, subject, targetTag, cV * -1)
				);
			}
		}

		// once all collisions processed, tell handlers to process events
		collisionBroker.processAllMessages();
	}

	// initialize debug renderer
	void DEBUG_initializeRenderer(
		GraphicsContext* graphics
	) {
		// initialize collider operator debug renderer
		colliderOp.initializeDebug(graphics);

		// update flag
		debugReady = true;
	}

	// debug render method
	void DEBUG_render()
	{
		// ensure system is initialized, else exit early
		if (!debugReady) return;

		// loop through all system entities
		ENTITY_SET::iterator it;
		for (it = entities.begin(); it != entities.end(); it++)
		{
			// render text
			colliderOp.renderDebug(
				*ecs->getComponent<ColliderData>(*it),
				Colors::LIME
			);
		}
	}
};

#endif // !_ORBIT_PREFABS_COLLISIONSYSTEM_H