// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngineECS : Component Manager Class Specification
// ===========================================================================
// ACKNOWLEDGEMENT: This Entity Component System was built with reference to a 
// plethora of sources, but most of the inspiration came from this reference:
// https://austinmorlan.com/posts/entity_component_system.
// ===========================================================================

#ifndef _ORBIT_ECS_COMPONENTMANAGER_H
#define _ORBIT_ECS_COMPONENTMANAGER_H

// import necessary headers
#include "componentArray.h"
#include "../types.h"
#include "../../utils/pointers.h"
#include <unordered_map>
#include <typeinfo>


// main definition

// manager class responsible for creating and maintaining component arrays for
// the entity-component-system.
class ComponentManager
{
private:

	// typedefs

	// defines a constant type string as returned by typeid().name()
	typedef const char* TYPE_STRING;

	// defines a map of component type strings to component arrays pointers.
	// in this case, unique pointers are used to safely deallocate memory
	// when the map is destroyed
	typedef std::unordered_map<
		TYPE_STRING, UniquePtr<IComponentArray>
	> COMPONENTARRAY_MAP;


	// members

	// map of component type strings to component arrays - this is where all
	// component arrays actually reside.
	COMPONENTARRAY_MAP componentArrays;

	// map of component type strings to enumerated component types (used when
	// setting bitflags for entity signatures)
	std::unordered_map<TYPE_STRING, ComponentTypeEnum> typeEnums;

	// counter for component type enumeration - specifies the position of the
	// bitflag assigned to the next component registered with this manager.
	ComponentTypeEnum nextTypeEnum;


	// private methods

	// retrieves the component array for the specified component type, and
	// also performs the necessary checks to ensure the component type has 
	// been registered with the manager beforehand.
	template <class ComponentType>
	ComponentArray<ComponentType>* getComponentArray()
	{
		// get type string for component type
		TYPE_STRING type = typeid(ComponentType).name();

		// ensure component type has been registered before, else throw warning
		if (typeEnums.count(type) == 0) throw Error(
			"Warning: Component type " + 
			std::string(type) + 
			"has not been registered!",
			ErrorType::WARNING
		);

		// cast generic component array to type and return reference
		return reinterpret_cast<ComponentArray<ComponentType>*>(
			componentArrays[type].get()
		);
	}

public:

	// constructor
	ComponentManager() :

		// members
		componentArrays(),
		typeEnums(),
		nextTypeEnum(0)
	{}


	// methods

	// registers a component type with the manager. this must be done before
	// any components are used with the manager, else the operations will fail
	template <class ComponentType>
	void registerComponent()
	{
		// get type string for component type
		TYPE_STRING type = typeid(ComponentType).name();

		// ensure that component type has not been registered, else exit early
		if (typeEnums.count(type) > 0) return;

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

	// adds a component to the appropriate component array for a specific
	// entity. this method will do nothing if a component already exists.
	template <class ComponentType>
	void addComponent(
		const Entity&			entity, 
		const ComponentType&	component
	) {
		// delegate call to appropriate component array
		getComponentArray<ComponentType>()->addComponent(entity, component);
	}

	// removes a component from the appropriate component array for a specific
	// entity. this method will do nothing if the component does not exists.
	template <class ComponentType>
	void removeComponent(
		const Entity&	entity
	) {
		// delegate call to appropriate component array
		getComponentArray<ComponentType>()->removeComponent(entity);
	}

	// notifies this manager that the entity has been destroyed, and should
	// clean up all related component data immediately.
	void notifyEntityDestroyed(
		const Entity& entity
	) {
		// initialize iterator
		COMPONENTARRAY_MAP::iterator it;

		// iterate through map
		for (it = componentArrays.begin(); it != componentArrays.end(); it++)
		{
			// notify each component array that entity was destroyed
			it->second->notifyEntityDestroyed(entity);
		}
	}


	// getters

	// retrieves the component type enum for the specified component type.
	template <class ComponentType>
	ComponentTypeEnum getTypeEnum()
	{
		// get type string for component type
		TYPE_STRING type = typeid(ComponentType).name();

		// ensure component type has been registered before, else throw error
		if (typeEnums.count(type) < 1) throw Error(
			"Error: Component type " + 
			std::string(type) + 
			"has not been registered!",
			ErrorType::FATAL_ERROR
		);

		// return component type enum
		return typeEnums[type];
	}

	// retrieves the component for the specified entity. if no component can
	// be found, the return value will be nullptr.
	template <class ComponentType>
	ComponentType* getComponent(
		const Entity&	entity
	) {
		// delegate call to appropriate component array
		return getComponentArray<ComponentType>()->getComponent(entity);
	}

};

#endif // !_ORBIT_ECS_COMPONENTMANAGER_H