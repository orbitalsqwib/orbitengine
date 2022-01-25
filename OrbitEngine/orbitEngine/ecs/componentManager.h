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
#include "types.h"
#include "componentArray.h"
#include "../utils/pointers.h"
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
	ComponentArray<ComponentType>* getComponentArray();

public:

	// constructor
	ComponentManager();


	// methods

	// registers a component type with the manager. this must be done before
	// any components are used with the manager, else the operations will fail
	template <class ComponentType>
	void registerComponent();

	// adds a component to the appropriate component array for a specific
	// entity. this method will do nothing if a component already exists.
	template <class ComponentType>
	void addComponent(
		const Entity&			entity, 
		const ComponentType&	component
	);

	// removes a component from the appropriate component array for a specific
	// entity. this method will do nothing if the component does not exists.
	template <class ComponentType>
	void removeComponent(const Entity& entity);

	// handles entity destruction
	void entityDestroyed(const Entity& entity);


	// getters

	// retrieves the component type enum for the specified component type.
	template <class ComponentType>
	ComponentTypeEnum getTypeEnum();

	// retrieves the component for the specified entity. if no component can
	// be found, the return value will be nullptr.
	template <class ComponentType>
	ComponentType* getComponent(const Entity& entity);

};

#endif // !_ORBIT_ECS_COMPONENTMANAGER_H