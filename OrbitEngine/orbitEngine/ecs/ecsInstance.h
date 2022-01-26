// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngineECS : ECS Instance Class Specification
// ===========================================================================
// ACKNOWLEDGEMENT: This Entity Component System was built with reference to a 
// plethora of sources, but most of the inspiration came from this reference:
// https://austinmorlan.com/posts/entity_component_system.
// ===========================================================================

#ifndef _ORBIT_ECS_ECSINSTANCE_H
#define _ORBIT_ECS_ECSINSTANCE_H

// import necessary headers
#include "entityManager.h"
#include "componentManager.h"
#include "systemManager.h"
#include "../utils/pointers.h"


// main definition

// defines a single instance of an entity-component-system, and coordinates
// between the entity, component and system managers. this is essentially just
// a wrapper class that delegates method calls and does some slight management
// on top of it.
class ECSInstance
{
private:

	// members

	// manages entities and entity signatures - created on initialize()
	UniquePtr<EntityManager> pEntityMgr;

	// manages components for each entity - created on initialize()
	UniquePtr<ComponentManager> pComponentMgr;

	// manages systems' entities and signatures - created on initialize()
	UniquePtr<SystemManager> pSystemMgr;

	// initialization flag - only set to true after initialization complete
	bool initialized;


	// private methods

	// ensures that the instance was initialized, or throws an error otherwise
	// inlining this function tells the compiler to insert the method code
	// wherever it was called, similar to a macro.
	inline void guardIsInitialized();

	// convenience method to set the bit flag for a specific component type in
	// an entity's signature to either true or false, and notifies other
	// managers as necessary.
	template <class ComponentType>
	void updateEntitySignatureForComponent(
		const Entity&	entity,
		const bool&		flagValue
	);

public:

	// constructor
	ECSInstance();

	// creates manager instances for the instance. delayed initialization is
	// required here as some managers are quite memory-intensive, e.g: entity
	// manager, thus it is better to delay initialization until the instance
	// is actually needed.
	void initialize();

	// manually deallocates all manager objects and resets the instance state
	// to uninitialized. this is useful if the ecs instance is not destroyed
	// once it stops being used, but is kept around for future reuse.
	void reset();


	// entity methods

	// creates and returns a new entity.
	Entity createEntity();

	// destroys the specified entity, and prepares it for reuse
	void destroyEntity(const Entity& entity);


	// component methods

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

	// retrieves the component type enum for the specified component type.
	template <class ComponentType>
	ComponentTypeEnum getTypeEnum();

	// retrieves the component for the specified entity. if no component can
	// be found, the return value will be nullptr.
	template <class ComponentType>
	ComponentType* getComponent(const Entity& entity);


	// system methods

	// registers a system with the system manager, creating a new system 
	// object instance within the system manager. also returns a pointer to 
	// the newly-created system so it can be used externally.
	template <class SystemType>
	SystemType* registerSystem();

	// sets the standard signature for a registered system. this controls the
	// components that an entity must possess in order to be added to the
	// system.
	template <class SystemType>
	void setSignature(const Signature& signature);

	// sets the exclusive signature for a registered system. this controls the
	// components that an entity must not have in order to be added to the
	// system
	template <class SystemType>
	void setExclusiveSignature(const Signature& signature);

};

#endif // !_ORBIT_ECS_ECSINSTANCE_H