// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Message Bus Generic
// ===========================================================================

#ifndef _ORBIT_PUBSUB_MESSAGEBUS_H
#define _ORBIT_PUBSUB_MESSAGEBUS_H

// import necessary headers
#include "ISubscriber.h"
#include <vector>

// forward class declarations
class MessageBroker;


// main definition

// specifies a basic broker object that keeps a list of subscribers and
// forwards new messages to them when sent a new message.
template <class MessageType>
class MessageBus
{
private:

	// typedefs

	// specifies a subscriber that implements the handling of message type
	typedef ISubscriber<MessageType> SUBSCRIBER;

	// specifies a vector of pointers to subscribers of a certain message type
	typedef std::vector<SUBSCRIBER*> SUBSCRIBER_SET;



	// members

	// records the subscribers listening to messages from this bus
	SUBSCRIBER_SET subscriberPtrs;

public:

	// =======================================================================
	// constructor
	// =======================================================================
	MessageBus() : subscriberPtrs() {}


	// methods

	// =======================================================================
	// pushes a message to all subscribed objects to be handled immediately.
	// accepts a pointer to a message queue, which should be the message queue
	// from which the message was sent from.
	// performance: o(n), may cache miss due to subscriber pointer lookup
	// =======================================================================
	void pushImmediately(
		const MessageType&	message,
		MessageBroker*		broker		= nullptr
	) {
		// initialize iterator
		typename SUBSCRIBER_SET::iterator it = subscriberPtrs.begin();

		// iterate through vector of subscriber pointers
		while (it != subscriberPtrs.end())
		{
			// tell each subscriber to handle the incoming message
			(*it)->handleMessage(message, broker);

			// increment iterator
			it++;
		}
	}

	// =======================================================================
	// registers a subscriber to the message bus: o(n)
	// =======================================================================
	void addSubscriber(SUBSCRIBER& subscriber)
	{
		// check if the subscriber already exists in the vector
		
		// initialize iterator
		typename SUBSCRIBER_SET::iterator it = subscriberPtrs.begin();

		// iterate through vector of subscriber pointers
		while (it != subscriberPtrs.end())
		{
			// check if subscriber pointers are identical, exit early if true
			if (*it == &subscriber) return;

			// increment iterator
			it++;
		}

		// if the subscriber does not already exist in the vector, add it
		subscriberPtrs.push_back(&subscriber);
	}

	// =======================================================================
	// deregisters a subscriber from the message bus
	// =======================================================================
	void removeSubscriber(SUBSCRIBER& subscriber)
	{
		// look through the vector for the subscriber and delete it

		// initialize iterator
		typename SUBSCRIBER_SET::iterator it = subscriberPtrs.begin();

		// iterate through vector of subscriber pointers
		while (it != subscriberPtrs.end())
		{
			// check if subscriber pointers are identical
			if (*it == &subscriber)
			{
				// if they are identical, remove it from the vector
				subscriberPtrs.erase(it);

				// erase invalidates all iterators, exit immediately
				return;
			}

			// increment iterator
			it++;
		}
	}

	
	// getters

	// checks if there are no subscribers to the message bus
	bool hasNoSubscribers() { return subscriberPtrs.size() == 0; }
};

#endif // !_ORBIT_PUBSUB_MESSAGEBUS_H