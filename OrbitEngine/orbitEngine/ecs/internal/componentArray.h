// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngineECS : Component Array Generic
// ===========================================================================
// ACKNOWLEDGEMENT: This Entity Component System was built with reference to a 
// plethora of sources, but most of the inspiration came from this reference:
// https://austinmorlan.com/posts/entity_component_system.
// ===========================================================================

#ifndef _ORBIT_ECS_COMPONENTARRAY_H
#define _ORBIT_ECS_COMPONENTARRAY_H

// import necessary headers
#include "../types.h"
#include <array>

// related constructs

// interface for all component array generics. specifies a set of shared
// functions that is applicable across each generated component array class.
class IComponentArray
{
public:

	// virtual destructor
	virtual ~IComponentArray() {};

	// should handle entity destruction when called
	virtual void notifyEntityDestroyed(const Entity& entity) = 0;

};

// main definition

// describes an array of components for an entity-component-system. this class
// is responsible for storing and providing access to its components, as well 
// as managing the lifecycle of each component.
template <class ComponentType>
class ComponentArray : public IComponentArray
{
private:

	// typedefs

	// specifies the index type for the components array - in this case, the
	// underlying type is entityid, as each entity may only have one of each
	// component, thus the maximum number of components in this array is 
	// ECS_MAX_ENTITIES, which is bounded to EntityId
	typedef EntityId COMPONENT_INDEX;


	// constants

	// defines the COMPONENT_INDEX value 
	const COMPONENT_INDEX INVALID_COMPONENT_INDEX = ECS_INVALID_ENTITY;


	// members

	// dense component array - holds the actual component data for each
	// possible entity. iterable in O(n) time, where n is the number of
	// actual components, with no empty spaces in between.
	std::array<ComponentType, ECS_MAX_ENTITIES> components;

	// sparse index array - maps entities to the index of each component in
	// the dense component array. (note that entityid type is used here, as
	// the maximum size of the components array is the max entityid size)
	std::array<COMPONENT_INDEX, ECS_MAX_ENTITIES> indexForEntity;

	// sparse index array - maps indexes of the component array to entitiy ids
	std::array<EntityId, ECS_MAX_ENTITIES> entityForIndex;

	// size of dense component array.
	COMPONENT_INDEX size;

	// assuming the following scenario:
	// let a = sizeof(ComponentType) bytes, 
	// ECS_MAX_ENTITIES = 4096,
	// 
	// total mem. used	= (4096) a + (4096) * 2B (WORD) + (4096) * 4B (DWORD)
	//					= (4096a)B + ~24kB
	// 
	// as previously mentioned, we trade memory for speed, so this has been
	// taken into consideration when using sparse arrays instead of unordered
	// maps. (though in some cases, unordered maps may take up even more
	// memory due to the map bucket pointer overheads!)
	// 
	// e.g: this article -> https://stackoverflow.com/a/59480898

public:

	// =======================================================================
	// constructor
	// =======================================================================
	ComponentArray():

		// members
		components		(),
		indexForEntity	(),
		entityForIndex	(),
		size			(0)
	{
		// initialize arrays
		indexForEntity.fill(INVALID_COMPONENT_INDEX);
		entityForIndex.fill(ECS_INVALID_ENTITY);
	}


	// methods

	// =======================================================================
	// adds a component to the array for a specified entity
	// =======================================================================
	void addComponent(
		const Entity&	entity,
		ComponentType	component
	) {
		// ensure that entity is valid
		EntityUtils::guardIsValid(entity);

		// get entity id from entity
		EntityId id = EntityUtils::getId(entity);

		// ensure that component for entity does not exist, else exit early
		if (indexForEntity[id] != INVALID_COMPONENT_INDEX) return;

		// if component does not exist, add component to end of array
		components[size] = component;

		// update array maps
		indexForEntity[id] = size;
		entityForIndex[size] = id;

		// increment size
		size++;
	}

	// =======================================================================
	// removes a component from the array for a specified entity
	// =======================================================================
	void removeComponent(
		const Entity&	entity
	) {
		// ensure that entity is valid
		EntityUtils::guardIsValid(entity);

		// get entity id from entity
		EntityId id = EntityUtils::getId(entity);

		// ensure that component for entity exists, else exit early
		if (indexForEntity[id] == INVALID_COMPONENT_INDEX) return;

		COMPONENT_INDEX iDeleted	= indexForEntity[id];
		COMPONENT_INDEX iLast		= size - 1;
		EntityId		lastEntity	= entityForIndex[iLast];

		// copy last component to "deleted" component to maintain density
		components[iDeleted]		= components[iLast];

		// update array maps
		indexForEntity[lastEntity]	= iDeleted;
		entityForIndex[iDeleted]	= lastEntity;
		indexForEntity[id]			= INVALID_COMPONENT_INDEX;
		entityForIndex[iLast]		= ECS_INVALID_ENTITY;

		// reduce size
		size--;
	}


	// implement pure virtuals

	// =======================================================================
	// handle entity destruction
	// =======================================================================
	virtual void notifyEntityDestroyed(
		const Entity&	entity
	) {
		// delegate work to removeComponent() method, which will just exit
		// quietly if no component exists for the entity.
		removeComponent(entity);
	}


	// getters

	// =======================================================================
	// returns the component for an entity, if it exists.
	// =======================================================================
	ComponentType* getComponent(
		const Entity&	entity
	) {
		// ensure that entity is valid
		EntityUtils::guardIsValid(entity);

		// get entity id from entity
		EntityId id = EntityUtils::getId(entity);

		// ensure that component for entity exists, else exit early
		if (indexForEntity[id] == INVALID_COMPONENT_INDEX) return nullptr;

		// return a pointer to the component
		return &components[indexForEntity[id]];
	}

};

#endif // !_ORBIT_ECS_COMPONENTARRAY_H