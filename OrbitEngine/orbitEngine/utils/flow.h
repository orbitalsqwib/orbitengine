// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Flow Control Generic
// ===========================================================================

#ifndef _ORBIT_UTILS_FLOW_H
#define _ORBIT_UTILS_FLOW_H

// import windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "../common/priority.h"


// main definition

// generic flow control class that supports a basic pipeline structure pattern
// for data processing.
template <class ResultType>
class Flow
{
private:

	// members

	// contains the end-result of the flow process
	ResultType result;

	// specifies the priority value of the current result
	Priority priority;

	// specifies whether the current flow is still active
	BOOL isActive;


	// internal setters

	// =======================================================================
	// updates the current result and priority to new values
	// =======================================================================
	void setResultAndPriority(
		const ResultType&	newResult, 
		const Priority&		newPriority
	) {
		result		= newResult;
		priority	= newPriority;
	}

public:

	// =======================================================================
	// constructor
	// =======================================================================
	Flow(const ResultType& defaultVal):

		// fields
		result			(defaultVal),
		priority		(Priority::NONE),
		isActive		(TRUE)
	{}


	// methods

	// =======================================================================
	// updates the flow's result value depending on the update priority
	// =======================================================================
	void update(
		const ResultType&	newResult,
		const Priority&		updatePriority	= Priority::LOW
	) {
		switch (priority)
		{
		// should be overridden by any priority, including itself
		case Priority::NONE:
		{
			setResultAndPriority(newResult, updatePriority);
			break;
		}
		// should be overridden only by higher priorities, excluding itself
		case Priority::LOW:
		case Priority::MEDIUM:
		case Priority::HIGH:
		{
			// casts priorities to int and checks if update priority has a
			// higher priority than the current priority
			if (static_cast<int>(updatePriority) > static_cast<int>(priority))
				setResultAndPriority(newResult, updatePriority);
			break;
		}
		// should be overridden only by itself
		case Priority::MAX:
		{
			if (updatePriority == Priority::MAX)
				setResultAndPriority(newResult, updatePriority);
			break;
		}
		}
	}

	// =======================================================================
	// specifies that subsequent flow processing should halt
	// =======================================================================
	void skipRemaining() { isActive = false; }

	// =======================================================================
	// convenience method: updates the flow with maximum priority and halts
	// subsequent processing for the flow. this function guarantees that the
	// value passed in will be returned on getResult() when called.
	// =======================================================================
	// this function is equivalent to calling update() with Priority::MAX,
	// then calling skipRemaining()
	// =======================================================================
	void resolve(const ResultType& finalResult)
	{
		// always update result and halt processing, 
		result = finalResult;
		isActive = false;
	}


	// getters

	// =======================================================================
	// return current result of the flow
	// =======================================================================
	ResultType getResult() const { return result; }

	// =======================================================================
	// specifies if subsequent flow processing should still take place
	// =======================================================================
	BOOL stillRunning() const { return isActive; }
};

#endif // !_ORBIT_UTILS_FLOW_H