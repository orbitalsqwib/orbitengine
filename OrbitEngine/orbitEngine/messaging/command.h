// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Command Abstract Class Specification
// ===========================================================================

#ifndef _ORBIT_MESSAGING_COMMAND_H
#define _ORBIT_MESSAGING_COMMAND_H

// main definition

// abstract command class. child classes should specify the state and logic
// required for the command's behaviour to work.
struct Command
{
	// virtual base destructor
	~Command() {}

	// functor operator (()). should execute the actual logic of the command.
	// should be called like a function: someCommandObject()
	virtual void operator()() = 0;
};

#endif // !_ORBIT_MESSAGING_COMMAND_H