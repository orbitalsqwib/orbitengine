// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngineECS : ECS Instance Class Implementation
// ===========================================================================
// ACKNOWLEDGEMENT: This Entity Component System was built with reference to a 
// plethora of sources, but most of the inspiration came from this reference:
// https://austinmorlan.com/posts/entity_component_system.
// ===========================================================================

// import specification
#include "ecsInstance.h"


// ===========================================================================
// constructor
// ===========================================================================
ECSInstance::ECSInstance():

	// members
	pEntityMgr		(nullptr),
	pComponentMgr	(nullptr),
	pSystemMgr		(nullptr),
	pEngineContext	(nullptr),
	initialized		(false)
{}

// ===========================================================================
// creates manager instances for the instance. delayed initialization is
// required here as some managers are quite memory-intensive, e.g: entity
// manager, thus it is better to delay initialization until the instance
// is actually needed.
// ===========================================================================
void ECSInstance::initialize(
	IEngineContext* _pEngineContext
) {
	// ensure that the incoming engine context is non-null, else throw error
	if (!_pEngineContext) throw Error(
		"Error: No engine context was provided!"
	);

	// allocate new managers and assign them to the unique pointer members. 
	// on destruction of the instance, the unique pointers will automatically
	// deallocate them and free up memory safely.
	pEntityMgr		= new EntityManager();
	pComponentMgr	= new ComponentManager();
	pSystemMgr		= new SystemManager(pEngineContext);
}

// ===========================================================================
// manually deallocates all manager objects and resets the instance state
// to uninitialized. this is useful if the ecs instance is not destroyed
// once it stops being used, but is kept around for future reuse.
// ===========================================================================
void ECSInstance::reset()
{
	// manually deallocate managers
	pEntityMgr.reset();
	pComponentMgr.reset();
	pSystemMgr.reset();
}


// private methods

// ===========================================================================
// ensures that the instance was initialized, or throws an error otherwise
// ===========================================================================
inline void ECSInstance::guardIsInitialized()
{
	// check if instance is initialized, throw error otherwise
	if (!initialized) throw Error(
		"Error: ECSInstance has not been initialized!"
	);
}

// ===========================================================================
// convenience method to set the bit flag for a specific component type in
// an entity's signature to either true or false, and notifies other
// managers as necessary.
// ===========================================================================
template <class ComponentType>
void ECSInstance::updateEntitySignatureForComponent(
	const Entity&	entity,
	const bool&		flagValue
) {
	// assert that this method will only be called when instance initialized
	assert(initialized);

	// calculate new signature for entity, set bit flag for component to true
	Signature s = pEntityMgr->getSignature(entity);
	s.set(pComponentMgr->getTypeEnum<ComponentType>(), true);

	// update entity signature to new signature
	pEntityMgr->setSignature(s);

	// notify systems of entity's signature update
	pSystemMgr->notifyEntitySignatureChanged(entity, s);
}


// entity methods

// ===========================================================================
// creates and returns a new entity.
// ===========================================================================
Entity ECSInstance::createEntity()
{
	// ensure instance is initalized
	guardIsInitialized();

	// delegate call to entity manager
	return pEntityMgr->createEntity();
}

// ===========================================================================
// destroys the specified entity, and prepares it for reuse
// ===========================================================================
void ECSInstance::destroyEntity(
	const Entity&	entity
) {
	// ensure instance is initalized
	guardIsInitialized();

	// delegate call to entity manager
	pEntityMgr		->destroyEntity(entity);

	// inform other managers that entity has been destroyed
	pComponentMgr	->notifyEntityDestroyed(entity);
	pSystemMgr		->notifyEntityDestroyed(entity);
}


// component methods

// ===========================================================================
// registers a component type with the manager. this must be done before
// any components are used with the manager, else the operations will fail
// ===========================================================================
template <class ComponentType>
void ECSInstance::registerComponent()
{
	// ensure instance is initalized
	guardIsInitialized();

	// delegate call to component manager
	pComponentMgr->registerComponent<ComponentType>();
}

// ===========================================================================
// adds a component to the appropriate component array for a specific
// entity. this method will do nothing if a component already exists.
// ===========================================================================
template <class ComponentType>
void ECSInstance::addComponent(
	const Entity&			entity,
	const ComponentType&	component
) {
	// ensure instance is initalized
	guardIsInitialized();

	// delegate call to component manager
	pComponentMgr->addComponent<ComponentType>();

	// update entity signature
	updateEntitySignatureForComponent<ComponentType>(entity, true);
}

// ===========================================================================
// removes a component from the appropriate component array for a specific
// entity. this method will do nothing if the component does not exists.
// ===========================================================================
template <class ComponentType>
void ECSInstance::removeComponent(
	const Entity&	entity
) {
	// ensure instance is initalized
	guardIsInitialized();

	// delegate call to component manager
	pComponentMgr->removeComponent<ComponentType>();

	// update entity signature
	updateEntitySignatureForComponent<ComponentType>(entity, false);
}

// ===========================================================================
// retrieves the component type enum for the specified component type.
// ===========================================================================
template <class ComponentType>
ComponentTypeEnum ECSInstance::getTypeEnum()
{
	// ensure instance is initalized
	guardIsInitialized();

	// delegate call to component manager
	return pComponentMgr->getTypeEnum<ComponentType>();
}

// ===========================================================================
// retrieves the component for the specified entity. if no component can
// be found, the return value will be nullptr.
// ===========================================================================
template <class ComponentType>
ComponentType* ECSInstance::getComponent(
	const Entity&	entity
) {
	// ensure instance is initalized
	guardIsInitialized();

	// delegate call to component manager
	return pComponentMgr->getComponent<ComponentType>();
}


// system methods

// ===========================================================================
// registers a system with the system manager, creating a new system 
// object instance within the system manager. also returns a pointer to 
// the newly-created system so it can be used externally.
// ===========================================================================
template <class SystemType>
SystemType* ECSInstance::registerSystem()
{
	// ensure instance is initalized
	guardIsInitialized();

	// delegate call to system manager
	return pSystemMgr->registerSystem<SystemType>();
}

// ===========================================================================
// sets the standard  signature for a registered system. this controls the
// components that an entity must possess in order to be added to the
// system.
// ===========================================================================
template <class SystemType>
void ECSInstance::setSignature(
	const Signature&	signature
) {
	// ensure instance is initalized
	guardIsInitialized();

	// delegate call to system manager
	pSystemMgr->setSignature<SystemType>(signature);
}

// ===========================================================================
// sets the exclusive signature for a registered system. this controls the
// components that an entity must not have in order to be added to the
// system
// ===========================================================================
template <class SystemType>
void ECSInstance::setExclusiveSignature(
	const Signature&	signature
) {
	// ensure instance is initalized
	guardIsInitialized();

	// delegate call to system manager
	pSystemMgr->setExclusiveSignature<SystemType>(signature);
}
