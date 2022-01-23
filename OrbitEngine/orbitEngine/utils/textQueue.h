// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Text Queue Utility Class Specification / Implementation
// ===========================================================================

#ifndef _ORBIT_UTILS_TEXTQUEUE_H
#define _ORBIT_UTILS_TEXTQUEUE_H

// import necessary headers
#include <string>


// main definition

// specifies a constant length text buffer that stores the last N characters
// written to it, where N is the maximum size of the buffer.
class TextQueue
{
private:

	// members

	// internal string buffer
	std::string buffer;

	// maximum buffer size
	size_t maxSize;

	
	// working states
	
	// specifies the amount of free character spaces needed for the append
	// operator to concatenate the incoming string
	size_t nCharsExceeded;


	// private methods

	// =======================================================================
	// calculates the number of characters exceeding over the buffer size for
	// a given size
	// =======================================================================
	size_t& calcNCharsExceeded(const size_t& incoming)
	{
		// calculate excess chars (negative values are floored to 0)
		nCharsExceeded = incoming - maxSize;

		// return reference to nCharsExceeded
		return nCharsExceeded;
	}

public:

	// =======================================================================
	// standard constructor
	// =======================================================================
	TextQueue(size_t bufferSize):

		// members
		buffer			(""),
		maxSize			(bufferSize),

		// working states
		nCharsExceeded	(0)
	{ 
		// reserve maximum buffer size for internal string buffer
		buffer.reserve(maxSize);
	}

	// =======================================================================
	// copy constructor
	// =======================================================================
	TextQueue(const TextQueue& other):

		// members
		buffer		(""),
		maxSize		(other.maxSize),

		// working states
		nCharsExceeded(other.nCharsExceeded)
	{
		// reserve maximum buffer size for internal string buffer
		buffer.reserve(maxSize);

		// copy buffer from other
		buffer = other.buffer;
	}

	
	// methods

	// =======================================================================
	// appends a string to the text buffer. if the text buffer would exceed
	// the maximum buffer size, this is resolved by adopting a FIFO approach,
	// erasing characters from the start of the text buffer to make space for
	// the rhs. this does not guarantee that rhs will remain intact if the
	// size of rhs is larger than the max buffer size.
	// =======================================================================
	TextQueue& append(const std::string& rhs)
	{
		// if the incoming string size is greater than the max buffer size
		if (rhs.size() > maxSize)
		{
			// assign the string to TextQueue
			assign(rhs);

			// return reference to the current object
			return *this;
		}

		// calculate number of excess characters if appending succeeds
		calcNCharsExceeded(buffer.size() + rhs.size());

		// if the resultant string size is greater than the max buffer size
		if (nCharsExceeded > 0)
		{
			// delete the first nCharsExceeded characters from buffer to
			// make space for the appended string
			buffer.erase(0, nCharsExceeded);
		}

		// append string, buffer size + rhs size should be <= max buffer size
		buffer.append(rhs);

		// return reference to the current object
		return *this;
	}

	// =======================================================================
	// assigns a string to the text buffer, replacing its contents. if the
	// string exceeds maxSize, assigns the last maxSize characters of the
	// incoming string to the text buffer
	// =======================================================================
	TextQueue& assign(const std::string& rhs)
	{
		// calculate number of excess characters
		calcNCharsExceeded(rhs.size());

		// copy last maxSize characters from rhs string to buffer (or
		// rhs size if rhs size is smaller than max buffer size)
		buffer = rhs.substr(nCharsExceeded);

		// return reference to the current object
		return *this;
	}

	// =======================================================================
	// appends a character to the text buffer. if the text buffer would exceed
	// the maximum buffer size, this is resolved by adopting a FIFO approach,
	// erasing characters from the start of the text buffer to make space for
	// the new character.
	// =======================================================================
	TextQueue& pushBack(const char& rhs)
	{
		// if buffer has hit max length, free up one character space by
		// erasing the first character in the buffer
		if (buffer.size() == maxSize) buffer.erase(buffer.cbegin());

		// append character, buffer size + 1 should be <= max buffer size
		buffer.push_back(rhs);

		// return reference to the current object
		return *this;
	}

	// =======================================================================
	// deletes the last len characters from the text buffer
	// =======================================================================
	TextQueue& popBack(const size_t& len = 1)
	{
		// if len is greater than the buffer size, erase the entire buffer
		if (len > maxSize) buffer.erase();

		// if len is smaller than the buffer size, erase the last len chars
		// from the buffer
		else buffer.erase(maxSize - len);

		// return reference to the current object
		return *this;
	}

	// =======================================================================
	// clears all text from the text buffer
	// =======================================================================
	void clear() { buffer.clear(); }


	// operators

	// string addition operator (+)
	TextQueue operator+(const std::string& rhs) { return append(rhs); }

	// string addition assignment operator (+=)
	TextQueue& operator+=(const std::string& rhs) { return append(rhs); }

	// string assignment operator (=)
	TextQueue& operator=(const std::string& rhs) { return assign(rhs); }

	// character addition operator (+)
	TextQueue operator+(const char& rhs) { return pushBack(rhs); }

	// character addition assignment operator (+=)
	TextQueue& operator+=(const char& rhs) { return pushBack(rhs); }


	// getters

	// returns the length of the string buffer
	size_t length() { return buffer.length(); }

	// returns the internal string buffer as a non-modifiable string ref
	const std::string& getString() { return buffer; }
};

#endif // !_ORBIT_UTILS_TEXTQUEUE_H