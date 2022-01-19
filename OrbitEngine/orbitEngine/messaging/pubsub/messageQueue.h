// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Message Queue Generic
// ===========================================================================

#ifndef _ORBIT_PUBSUB_MESSAGEQUEUE_H
#define _ORBIT_PUBSUB_MESSAGEQUEUE_H

// import necessary headers
#include "messageBus.h"
#include "IMessageQueue.h"
#include "ISubscriber.h"
#include "../../utils/circularQueue.h"

// forward class declarations
class MessageBroker;


// main definition

// specifies a basic message queue that allows for delayed processing of
// messages in the sequence they arrived.
template <class MessageType>
class MessageQueue : public IMessageQueue
{
private:

	// members

	// internal message bus that handles subscribers
	MessageBus<MessageType> msgBus;

	// contains a queue of messages to be delivered to subscribers in order
	CircularQueue<MessageType> msgQueue;

public:

	// =======================================================================
	// constructor
	// =======================================================================
	MessageQueue() : msgBus(), msgQueue() {}


	// methods

	// =======================================================================
	// pushes a message to the back of the message queue
	// =======================================================================
	void queue(const MessageType& message)
	{
		msgQueue.pushBack(message);
	}

	// =======================================================================
	// pushes a message to the front of the message queue
	// =======================================================================
	void queueToFront(const MessageType& message)
	{
		msgQueue.pushFront(message);
	}

	// =======================================================================
	// pushes a message to all subscribed objects to be handled immediately.
	// performance: o(n), may cache miss due to subscriber pointer lookup
	// =======================================================================
	void pushImmediately(
		const MessageType&	message,
		MessageBroker*		broker		= nullptr
	) {
		// delegate message communication to the internal data bus
		msgBus.pushImmediately(message, broker);
	}

	// =======================================================================
	// registers a subscriber to the message queue
	// =======================================================================
	void addSubscriber(ISubscriber<MessageType>& subscriber)
	{
		// register subscriber with the internal data bus
		msgBus.addSubscriber(subscriber);
	}

	// =======================================================================
	// removes a subscriber from the message queue
	// =======================================================================
	void removeSubscriber(ISubscriber<MessageType>& subscriber)
	{
		// remove subscriber from the internal data bus
		msgBus.removeSubscriber(subscriber);
	}

	// =======================================================================
	// processes all messages currently in the queue. accepts an optional
	// broker pointer, which should be provided if this method was invoked by
	// a message broker.
	// =======================================================================
	void processMessages(MessageBroker* broker = nullptr)
	{
		// while the message queue still has messages,
		while (!msgQueue.isEmpty())
		{
			// cache and delete message on processing it
			MessageType msg = msgQueue.peekFront();
			msgQueue.popFront();

			// send the message to each subscriber through the message bus and
			// have them process the messages synchronously
			msgBus.pushImmediately(msg, broker);	
		}
	}

	// getters

	// checks if there are no subscribers to the message bus
	bool hasNoSubscribers() { return msgBus.hasNoSubscribers(); }
};

#endif // !_ORBIT_PUBSUB_MESSAGEQUEUE_H