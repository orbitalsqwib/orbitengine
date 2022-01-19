// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Message Broker Class Specification
// ===========================================================================

#ifndef _ORBIT_PUBSUB_MESSAGEBROKER_H
#define _ORBIT_PUBSUB_MESSAGEBROKER_H

// import necessary headers
#include "messageQueue.h"
#include "IMessageQueue.h"
#include "ISubscriber.h"
#include "../../utils/pointers.h"
#include <typeinfo>
#include <unordered_map>


// main definition

// specifies an intermediary message broker in the pub/sub model responsible
// for forwarding messages from publishers to all subscribed objects.
class MessageBroker
{
private:

	// typedefs

	// defines a map of type string pointers to message queues
	typedef std::unordered_map<const char*, UniquePtr<IMessageQueue>> MQ_MAP;

	
	// members

	// mapping of type string pointers to message queues
	MQ_MAP messageQueues;

	// specifies if the broker should be strict when creating message queues,
	// where message queues are only created when registering a subscriber for
	// the first time. messages sent before this trigger are discarded and are
	// not sent again.
	bool strict;


	// private methods

	// creates a new message queue for the specified message type and returns 
	// a pointer to it
	template <class MessageType>
	MessageQueue<MessageType>* createNewQueue()
	{
		// get type string for message type
		const char* msgType = typeid(MessageType).name();

		// check if any message queues are open for the specified message type
		if (messageQueues.find(msgType) == messageQueues.end())
		{
			// if there are none, create a new message queue
			MessageQueue<MessageType>* pMQ = new MessageQueue<MessageType>();

			// construct new queue and add it to the map
			messageQueues[msgType] = UniquePtr<IMessageQueue>(pMQ);

			// return pointer to new queue
			return pMQ;
		}

		// cast message queue to the specific type and return it
		return static_cast<MessageQueue<MessageType>*>(
			messageQueues[msgType].get()
		);
	}

	// retrieves the message queue for the specified message type.
	// as the pointer returned from this method is not guaranteed to exist,
	// callers are responsible for null-checking the return value.
	template <class MessageType>
	MessageQueue<MessageType>* getMessageQueue()
	{
		// get type string for message type
		const char* msgType = typeid(MessageType).name();

		// check if any message queues are open for the specified message type
		if (messageQueues.find(msgType) == messageQueues.end())
		{
			// if there are none, return nullptr
			return nullptr;
		}

		// cast message queue to the specific type and return it
		return static_cast<MessageQueue<MessageType>*>(
			messageQueues[msgType].get()
		);
	}

public:

	// constructor
	MessageBroker(bool strictMode = true): 
		
		// members
		messageQueues	(),
		strict			(strictMode)
	{}


	// methods

	// processes all messages for each message queue. the execution order of 
	// each message queue is not guaranteed to remain constant.
	void processAllMessages()
	{
		// initialize iterator
		MQ_MAP::iterator it = messageQueues.begin();

		// for each message queue in the map
		while (it != messageQueues.end())
		{
			// process all messages in the queue
			it->second->processMessages(this);

			// increment iterator
			it++;
		}
	}

	// adds the specified message to the back of the relevant message queue
	template <class MessageType>
	void queue(const MessageType& message)
	{
		// attempt to add message to back of queue if it exists
		if (MessageQueue<MessageType>* pMQ = getMessageQueue<MessageType>())
		{
			pMQ->queue(message);
		}
		// non-strict mode, create new message queue to hold message
		else if (!strict)
		{
			createNewQueue<MessageType>()->queue(message);
		}
	}

	// adds the specified message to the front of the relevant message queue
	template <class MessageType>
	void queueToFront(const MessageType& message)
	{
		// attempt to add message to front of queue if it exists
		if (MessageQueue<MessageType>* pMQ = getMessageQueue<MessageType>())
		{
			pMQ->queueToFront(message);
		}
		// non-strict mode, create new message queue to hold message
		else if (!strict)
		{
			createNewQueue<MessageType>()->queueToFront(message);
		}
	}

	// sends a message to all relevant subscribers for processing immediately
	template <class MessageType>
	void pushImmediately(const MessageType& message)
	{
		// attempt to send message to bus immediately if queue exists
		if (MessageQueue<MessageType>* pMQ = getMessageQueue<MessageType>())
		{
			pMQ->pushImmediately(message, this);
		}
		// non-strict mode, create new message queue to send message
		else if (!strict)
		{
			createNewQueue<MessageType>()->pushImmediately(message, this);
		}
	}

	// registers the specified subscriber for the relevant message queue
	template <class MessageType>
	void addSubscriber(ISubscriber<MessageType>& subscriber)
	{
		// attempt to register subscriber to queue if it exists
		if (MessageQueue<MessageType>* pMQ = getMessageQueue<MessageType>())
		{
			pMQ->addSubscriber(subscriber);
		}
		// always create new queue on registration if it doesn't exist, then
		// register the subscriber to the queue after.
		else
		{
			createNewQueue<MessageType>()->addSubscriber(subscriber);
		}
	}

	// deregisters the specified subscriber for the relevant message queue
	template <class MessageType>
	void removeSubscriber(ISubscriber<MessageType>& subscriber)
	{
		// only attempt to remove a subscriber if the queue exists
		if (MessageQueue<MessageType>* pMQ = getMessageQueue<MessageType>())
		{
			pMQ->removeSubscriber(subscriber);
		}
	}

};

#endif // !_ORBIT_PUBSUB_MESSAGEBROKER_H