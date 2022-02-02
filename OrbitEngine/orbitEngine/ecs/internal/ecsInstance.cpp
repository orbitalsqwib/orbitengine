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
	initialized		(false)
{}

// ===========================================================================
// creates manager instances for the instance. delayed initialization is
// required here as some managers are quite memory-intensive, e.g: entity
// manager, thus it is better to delay initialization until the instance
// is actually needed.
// ===========================================================================
void ECSInstance::initialize()
{
	// allocate new managers and assign them to the unique pointer members. 
	// on destruction of the instance, the unique pointers will automatically
	// deallocate them and free up memory safely.
	pEntityMgr		= new EntityManager();
	pComponentMgr	= new ComponentManager();
	pSystemMgr		= new SystemManager(this);

	// set initialized flag to true
	initialized = true;
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
