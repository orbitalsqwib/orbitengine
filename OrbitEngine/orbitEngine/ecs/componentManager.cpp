// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngineECS : Component Manager Class Implementation
// ===========================================================================
// ACKNOWLEDGEMENT: This Entity Component System was built with reference to a 
// plethora of sources, but most of the inspiration came from this reference:
// https://austinmorlan.com/posts/entity_component_system.
// ===========================================================================

// import specification
#include "componentManager.h"


// ===========================================================================
// constructor
// ===========================================================================
ComponentManager::ComponentManager():

	// members
	componentArrays	(),
	typeEnums		(),
	nextTypeEnum	(0)
{}


// private methods

// ===========================================================================
// retrieves the component array for the specified component type, and
// also performs the necessary checks to ensure the component type has 
// been registered with the manager beforehand.
// ===========================================================================
template <class ComponentType>
ComponentArray<ComponentType>* ComponentManager::getComponentArray()
{
	// get type string for component type
	TYPE_STRING type = typeid(ComponentType).name();

	// ensure component type has been registered before, else throw warning
	if (typeEnums.count(type) == 0) throw Error(
		"Warning: Component type " + type + "has not been registered!",
		ErrorType::WARNING
	);

	// cast generic component array to type and return reference
	return reinterpret_cast<ComponentArray<ComponentType>*>(
		componentArrays[type].get()
	);
}


// methods

// ===========================================================================
// registers a component type with the manager. this must be done before
// any components are used with the manager, else the operations will fail
// ===========================================================================
template <class ComponentType>
void ComponentManager::registerComponent()
{
	// get type string for component type
	TYPE_STRING type = typeid(ComponentType).name();

	// ensure that component type has not been registered, else throw warning
	if (typeEnums.count(type) > 0) throw Error(
		"Warning: Component type " + type + "has been registered before!",
		ErrorType::WARNING
	);

	// ensure that the number of registered components remains less than or
	// equal to the maximum number of components
	if (nextTypeEnum >= ECS_MAX_COMPONENTS) throw Error(
		"Warning: Maximum (per-system) component limit reached!",
		ErrorType::WARNING
	);

	// add new component type enum to component type enum map
	typeEnums[type] = nextTypeEnum;

	// add new component array to component array map
	componentArrays[type] = UniquePtr<IComponentArray>(
		new ComponentArray<ComponentType>()
	);

	// increment value of nextTypeEnum for next component type
	nextTypeEnum++;
}

// ===========================================================================
// adds a component to the appropriate component array for a specific
// entity. this method will do nothing if a component already exists.
// ===========================================================================
template <class ComponentType>
void ComponentManager::addComponent(
	const Entity&			entity, 
	const ComponentType&	component
) {
	// delegate call to appropriate component array
	getComponentArray<ComponentType>()->addComponent(entity, component);
}

// ===========================================================================
// removes a component from the appropriate component array for a specific
// entity. this method will do nothing if the component does not exists.
// ===========================================================================
template <class ComponentType>
void ComponentManager::removeComponent(
	const Entity&			entity
) {
	// delegate call to appropriate component array
	getComponentArray<ComponentType>()->removeComponent(entity);
}

// ===========================================================================
// handles entity destruction
// ===========================================================================
void ComponentManager::entityDestroyed(
	const Entity& entity
) {
	// initialize iterator
	COMPONENTARRAY_MAP::iterator it = componentArrays.begin();

	// iterate through map
	while (it != componentArrays.end())
	{
		// notify each component array that entity was destroyed
		it->second->notifyEntityDestroyed(entity);

		// increment iterator
		it++;
	}
}


// getters

// ===========================================================================
// retrieves the component type enum for the specified component type.
// ===========================================================================
template <class ComponentType>
ComponentTypeEnum ComponentManager::getTypeEnum()
{
	// get type string for component type
	TYPE_STRING type = typeid(ComponentType).name();

	// ensure component type has been registered before, else throw warning
	if (typeEnums.count(type) == 0) throw Error(
		"Warning: Component type " + type + "has not been registered!",
		ErrorType::WARNING
	);

	// return component type enum
	return typeEnums[type];
}

// retrieves the component for the specified entity. if no component can
// be found, the return value will be nullptr.
template <class ComponentType>
ComponentType* ComponentManager::getComponent(
	const Entity&	entity
){
	// delegate call to appropriate component array
	return getComponentArray<ComponentType>()->getComponent(entity);
}
