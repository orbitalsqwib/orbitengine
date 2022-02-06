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

// checks for collisions between entities and emits a entitycollided message
// on a successful collision check. this message should be picked up and
// handled by the relevant collision resolution systems.
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
	void checkAllCollisions(
		const char	subjectTag[32],
		const char	targetTag[32]
	) {
		// initialize iterators for all entities
		ENTITY_SET::iterator itAll;

		// initialize iterators for uncollided entities
		ENTITY_SET::iterator itSet;

		// setup collision vector container
		Vec2 cV;

		// loop through all entities
		for (itAll = entities.begin(); itAll != entities.end(); itAll++)
		{
			// get collider component for subject entity
			ColliderData* cSub = ecs->getComponent<ColliderData>(*itAll);

			// if no collider found, skip to next iteration
			if (!cSub) continue;

			// if tag does not match target tag, skip to next iteration
			if (cSub->getTag() != subjectTag) continue;

			// check collisions from each entity in the set after subject
			for (itSet = entities.begin(); itSet != entities.end(); itSet++)
			{
				// get collider component for target entity
				ColliderData* cTgt = ecs->getComponent<ColliderData>(*itSet);

				// if no collider found, skip to next iteration
				if (!cTgt) continue;
				
				// if tag does not match target tag, skip to next iteration
				if (cTgt->getTag() != targetTag) continue;

				// check collision between both entities from subject's persp.
				if (colliderOp.collide(*cSub, *cTgt, cV))
				{
					// entities did collide, send collision events to queue
					collisionBroker.queue(EntityCollided(
						*itAll, *itSet, subjectTag, targetTag, cV * -1
					));
					collisionBroker.queue(EntityCollided(
						*itSet, *itAll, targetTag, subjectTag, cV
					));
				}
			}
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

		// get subject collider tag
		std::string subjectTag = cSub->getTag();

		// setup collision vector container
		Vec2 cV;

		// initialize iterator
		ENTITY_SET::iterator it;

		// check collisions for each entity with the target tag
		for (it = entities.begin(); it != entities.end(); it++)
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
				collisionBroker.queue(EntityCollided(
					subject, *it, subjectTag.c_str(), targetTag, cV * -1
				));
				collisionBroker.queue(EntityCollided(
					*it, subject, targetTag, subjectTag.c_str(), cV
				));
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
			// attempt to get component data for entity
			if (ColliderData* pCol = ecs->getComponent<ColliderData>(*it))
			{
				// render text
				colliderOp.renderDebug(*pCol, Colors::LIME);
			}
		}
	}
};

#endif // !_ORBIT_PREFABS_COLLISIONSYSTEM_H