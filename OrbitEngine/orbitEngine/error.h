// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Error Handler Specification
// ===========================================================================

#ifndef _ORBIT_ERROR_H
#define _ORBIT_ERROR_H

// import necessary headers
#include <string>
#include <exception>

// related constructs

enum class ErrorType : int
{
	FATAL_ERROR		= -1,
	WARNING			= 0
};


// main definition

// basic error handler for the engine.
class Error : public std::exception
{
private:

	// members

	// code of error being thrown
	ErrorType errorCode;

	// message describing error being thrown
	std::string errorMsg;

public:

	// default constructor
	Error():
		errorCode		(ErrorType::FATAL_ERROR),
		errorMsg		("An undefined fatal engine error occurred.")
	{}

	// copy constructor
	Error(
		const Error&	e
	):
		std::exception	(e),
		errorCode		(e.errorCode),
		errorMsg		(e.errorMsg)
	{}

	// constructor with args
	Error(
		std::string		msg,
		ErrorType		errCode	= ErrorType::FATAL_ERROR
	):
		errorCode		(errCode),
		errorMsg		(msg)
	{}

	// assignment operator (=)
	Error& operator= (const Error& rhs)
	{
		// set this object's exception to rhs exception
		std::exception::operator=(rhs);

		// set this object's members to rhs members
		this->errorCode = rhs.errorCode;
		this->errorMsg = rhs.errorMsg;
	}

	// destructor
	~Error() {};


	// overriding methods

	// override original exception class what() method
	virtual const char* what() const { return getMessage(); }


	// getters

	// return pointer to error message
	const char* getMessage() const { return errorMsg.c_str(); }

	// return error code of error
	int getErrorCode() const { return static_cast<int>(errorCode); }
};

#endif // !_ORBIT_ERROR_H