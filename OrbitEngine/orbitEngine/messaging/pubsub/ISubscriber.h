// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Subscriber Interface Specification
// ===========================================================================

#ifndef _ORBIT_PUBSUB_ISUBSCRIBER_H
#define _ORBIT_PUBSUB_ISUBSCRIBER_H

// forward class declarations
class MessageBroker;


// main definition

// specifies a interface for an object that can be subscribed to a message
// broker and can process messages of MessageType
template <class MessageType>
class ISubscriber
{
public:

	// interface virtual destructor
	virtual ~ISubscriber() {}

	// should handle incoming messages and make changes to the object's state
	// or behaviour as necessary. may provide a pointer to the message broker
	// that invoked this event, which should be null-checked prior to use.
	virtual void handleMessage(
		MessageType			message,
		MessageBroker*		broker
	) = 0;

};

#endif // !_ORBIT_PUBSUB_ISUBSCRIBER_H