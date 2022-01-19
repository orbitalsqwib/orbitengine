// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Message Queue Interface Specification
// ===========================================================================

#ifndef _ORBIT_PUBSUB_IMESSAGEQUEUE_H
#define _ORBIT_PUBSUB_IMESSAGEQUEUE_H

// forward class declarations
class MessageBroker;


// main definition

// specifies a generic message queue object that must be cast to a concrete
// message queue type before it can be used.
class IMessageQueue
{
public:

	// interface virtual destructor
	virtual ~IMessageQueue() {}

	// should process all messages currently in the queue. accepts an optional
	// broker pointer, which should be provided if this method was invoked by
	// a message broker.
	virtual void processMessages(MessageBroker* broker = nullptr) = 0;
};

#endif // !_ORBIT_PUBSUB_IMESSAGEQUEUE_H