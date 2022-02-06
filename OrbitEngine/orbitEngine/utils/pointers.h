// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Smart Pointer Generics
// ===========================================================================
// NOTE: Although using the STL smart pointers are frowned upon in the GPP
// module as they obscure important memory management patterns, they are still
// necessary in some cases to avoid memory leaks. Thus, a basic implementation
// has been provided within the engine itself to showcase understanding of
// the internal mechanisms of such pointers.
// ===========================================================================

// ===========================================================================
// A Small Note on Move Semantics and Value Categories (lvalue/rvalues):
// ===========================================================================
// References: 
// (1) https://www.internalpointers.com/post/understanding-meaning-lvalues-and-rvalues-c,
// (2) https://www.internalpointers.com/post/c-rvalue-references-and-move-semantics-beginners
// (3) https://stackoverflow.com/a/37953536
// ===========================================================================
// In C++03, expressions can categorised into 2 categories:
// 
//	(1) lvalues - these refer to anything (functions, objects) that occupy 
//		a specific location in memory.
// 
//	(2) rvalues - these refer to everything else (such as literal constants or 
//		temporary function return values) that can be thought of as pure
//		values.
// 
// The first article summarises the relationships and differences between the
// two value categories well. To quote:
// 
// | "In general, rvalues are temporary and short lived, while lvalues live a
// | longer life since they exist as variables. It's also fun to think of 
// | lvalues as containers and rvalues as things contained in the containers."
// 
// When one understands this, it is then easier to understand some of the more
// complicated errors in C++, such as when attempting to obtain the reference
// of an rvalue-returning function:
// 
// | Obj getMyObj() { return obj; }
// | ...
// | Obj& myObjRef = &(getMyObj()); // lvalue required as unary '&' operand!
// 
// For example, the code snippet above won't work since the getMyObj function
// returns a temporary Obj rvalue that doesn't live at a specific memory
// location, so the address-of operator (&) is an invalid operation. Thus, the
// compiler tells us that we should give it a proper lvalue argument instead.
// 
// However, other than being able to understand cryptic error messages, the
// concept of rvalues and lvalues are also valuable when it comes to 
// optimizing the movement of data between variables.
// 
// A commonly seen C++ idiom is the use of constant lvalue references to take
// in values for functions, skipping the need to allocate memory for temporary
// variables. (when passing-by-value)
// 
// | int multiplyByTwo(const int& i) { return i*2; }
// | ...
// | int res = multiplyByTwo(2);
// 
// In the example above, i (a const. lvalue ref.) is bound to a rvalue (2) and
// can then be referenced within the function to perform operations. However,
// as a constant reference, it is immutable (cannot be modified), and is thus
// unsuitable for situations where modifications to the function arguments are
// necessary.
// 
// Taking it one step further, C++11 introduces move semantics, which allow
// for even further optimization of the program.
// 
// In article (2), the author describes a hypothetical class object that can
// be extremely memory-intensive. (it takes up N 32-bit integers worth of
// memory, where N is a value provided during construction)
// 
// | class Holder
// | {
// | public:
// | 
// | 	Holder(int size)         // Constructor
// | 	{
// | 		m_data = new int[size];
// | 		m_size = size;
// | 	}
// | 
// | 	~Holder()                // Destructor
// | 	{
// | 		delete[] m_data;
// | 	}
// | 
// | private:
// | 
// | 	int* m_data;
// |	size_t m_size;
// | };
//
// Assuming one wants to swap data values between two Holder objects, a naive
// approach might use the following steps:
//	(1) allocate a temporary Holder object using a copy constructor, which:
//			(a)	uses N units of memory
//			(b)	takes O(N) time to copy all values from Holder object A
//	(2) take O(N) time to copy all values from Holder object B to A
//	(3) take O(N) time to copy all values from the temporary object to B
//	(4) deallocate the temporary Holder object
// 
// However, with move semantics, this approach can be optimized further!
// 
// We can implement a move constructor, which will construct a Holder object
// from a pre-existing Holder object by "stealing" ownership of its integer
// array. This modifies the swap function to the following:
//	(1) allocate a empty, temporary Holder object that uses no extra memory
//	(2) move the data array from A to the temporary Holder object
//	(3) move the data array from B to A
//	(4) move the data array from the temporary Holder object to B
// 
// A naive implementation of a move constructor could be as follows:
// 
// | Holder(Holder& other)
// | {
// |	m_data = other.m_data;
// |	m_size = other.m_size;
// |	other.m_data = nullptr;
// |	other.m_size = 0;
// | }
// 
// This snippet would work for our arbitrary swap algorithm. However, note
// that we use a reference to a more permanent, lvalue Holder. Assume the
// following factory method and copy constructor:
// 
// | // copy constructor
// | Holder(const Holder& other)
// | {
// |	m_data = new int[other.m_size];  // (1)
// |	std::copy(other.m_data, other.m_data + other.m_size, m_data);  // (2)
// |	m_size = other.m_size;
// | }
// |
// | // factory method
// | Holder createHolder(int size) { return Holder(size); }
// | ...
// | Holder h(createHolder(1000));
// 
// When the above code is run, the copy constructor will run instead of the
// move constructor, as createHolder returns a temporary rvalue Holder object.
// This results in the following set of operations:
//	(1) createHolder creates and returns a temporary Holder object
//	(2) the copy constructor is called, which does a deep copy of the 
//		temporary Holder object to Holder h
//	(3)	the temporary Holder object created is then disposed off when it goes
//		outside of the scope
// 
// Note that step (1) returns a perfectly valid Holder object, where the
// ownership of its fields could have been passed directly to Holder h without
// needing to do the extra allocation/deallocation and copy steps.
// 
// Thus we are now in a dilemma:
//	(1) The move constructor can be called for lvalue references, but not 
//		rvalue references
//	(2)	The copy constructor is called on const lvalue references which work
//		for rvalues and lvalues, but is suboptimal compared to the move
//		constructor in the case of rvalues
//	(3) The const lvalue reference syntax is incompatible with movement logic
//		as the reference is immutable, thus it cannot be applied to the move
//		constructor nor the copy constructor.
// 
// To solve this problem, C++11 introduces the concept of rvalue references.
// Rvalue references are indicated by the double ampersand (&&) operator, and
// act as a mutable version of a const lvalue reference. Rvalue references
// are semantically separate from lvalue references, as they are used
// exclusively for disposable, temporary rvalues.
// 
// Thus, a proper move constructor can be implemented with an rvalue reference
// as shown below:
// 
// | Holder(Holder&& other)
// | {
// |	m_data = other.m_data;
// |	m_size = other.m_size;
// |	other.m_data = nullptr;
// |	other.m_size = 0;
// | }
// 
// When the constructor is called with an rvalue, the move constructor is then
// given precedence over the copy constructor. Meanwhile, when called with an
// lvalue, the copy constructor will still be called as per normal.
// 
// This method also adds another layer of semantic guards, where the move
// constructor must be called explicitly for lvalues through the use of the
// std::move() STL method, introduced in C++11, which casts the lvalue to a
// rvalue before it is passed into the constructor:
// 
// | Holder h1(1000)
// | Holder h2(std::move(h1))
// 
// This prevents ambiguity when working with overloaded constructors, and is
// easier to read even for beginner programmers who are unfamiliar with
// lvalues or rvalues. (e.g: "this code moves h1 to h2 somehow")
// 
// The usecases for lvalue references, const lvalue references and rvalue
// references as function argument types are summarised nicely by article (3):
// 
// |	(1) normal argument:
// |
// | // Here, let me buy you a new car just like mine. I don't care if you
// | // wreck it or give it a new paint job; you have yours and I have mine.
// | void foo(Car c);
// | 
// |	(2) lvalue reference argument:
// |
// | // Here are the keys to my car. I understand that it may come back...
// | // not quite the same... as I lent it to you, but I'm okay with that.
// | void foo(Car& c);
// |
// |	(3) const lvalue reference argument:
// | 
// | // Here are the keys to my car as long as you promise to not give it a
// | // paint job or anything like that
// | void foo(const Car& c);
// |
// |	(4) rvalue reference argument:
// | 
// | // rvalue reference argument (pass-by-reference):
// | // I don't need my car anymore, so I'm signing the title over to you now.
// | // Happy birthday!
// | void foo(Car&& c);
// 
// In summary, lvalues and rvalues are relatively important to optimizing
// C++ algorithms. As such, this note has been included to provide a
// reasonable basis for which to validate the use of C++11 move semantics 
// features, including the use of rvalue references, move constructors, move 
// assignment operators and the STL method std::move within the assignment
// codebase.
// ===========================================================================

#ifndef _ORBIT_UTILS_POINTERS_H
#define _ORBIT_UTILS_POINTERS_H

// import necessary headers
#include "../macros.h"
#include <utility>


// main definition

// ===========================================================================
// Unique Pointer (Single Object Variant)
// ===========================================================================
// Ensures that only one copy of a managed object can exist at any moment, and
// cannot be copied. Does not use reference counting. Does not allow for
// custom deleters, which were included in the original STL specification.
// 
// Implemented with reference to: 
// https://en.cppreference.com/w/cpp/memory/unique_ptr
// ===========================================================================
template <class DataType>
class UniquePtr
{
private:

	// members

	// internal data pointer to the managed object - automatically deleted
	// in the following conditions
	//	(1) the instance is deleted; see destructor
	//	(2) the instance is reset or is assigned to a new managed object
	DataType* dataPtr;
	
public:

	// =======================================================================
	// default constructor
	// =======================================================================
	UniquePtr() noexcept : dataPtr(nullptr) {}

	// =======================================================================
	// nullptr constructor
	// =======================================================================
	UniquePtr(std::nullptr_t) noexcept : dataPtr(nullptr) {}

	// =======================================================================
	// constructor from pointer ("adopting" a raw pointer)
	// =======================================================================
	// NOTE: this will crash the program if the object pointed to was not
	// created using the new keyword
	// =======================================================================
	UniquePtr(DataType* ptr) noexcept : dataPtr(ptr) {}

	// =======================================================================
	// move constructor - releases ownership of the object from ptr and
	// transfers ownership to the new unique pointer instance
	// =======================================================================
	UniquePtr(UniquePtr&& ptr) noexcept : dataPtr(ptr.release()) {}

	// =======================================================================
	// destructor - called automatically in the following circumstances
	//	(1) the instance moves out of scope
	//	(2) the instance is manually destroyed
	// =======================================================================
	~UniquePtr() noexcept
	{
		// safely delete and free memory for the currently managed object
		SAFE_DELETE(dataPtr);
	}


	// operators

	// =======================================================================
	// move assignment operator. releases ownership of the object from the
	// other unique pointer and transfers it to this instance
	// =======================================================================
	UniquePtr& operator=(UniquePtr&& other) noexcept
	{
		// reset this instance's managed object to the managed object released
		// by the other unique pointer instance
		reset(other.release());

		// return a reference to the current instance for daisy chaining
		return *this;
	}

	// =======================================================================
	// nullptr assignment operator. resets the instance to the empty state.
	// =======================================================================
	UniquePtr& operator=(std::nullptr_t) noexcept
	{
		// passing in a nullptr is equivalent to resetting the managed object
		// to a nullptr
		reset();

		// return a reference to the current instance for daisy chaining
		return *this;
	}

	// =======================================================================
	// bool operator. checks if the managed data pointer is nullptr
	// =======================================================================
	operator bool() const { return dataPtr != nullptr; }

	// =======================================================================
	// dereference operator (*)
	// =======================================================================
	DataType& operator*() const { return *dataPtr; }

	// =======================================================================
	// indirection operator (->)
	// =======================================================================
	DataType* operator->() const { return dataPtr; }


	// methods

	// =======================================================================
	// releases the ownership of the managed object and returns a raw pointer;
	// the caller is then responsible for deleting the object
	// =======================================================================
	DataType* release()
	{
		// save original data pointer
		DataType* oldPtr = dataPtr;

		// reset instance's managed object pointer to nullptr
		dataPtr = nullptr;

		// return old managed object pointer
		return oldPtr;
	}

	// =======================================================================
	// replaces the managed object pointer with ptr; safely deletes the 
	// previous object from program memory if it's a non-null value
	// =======================================================================
	void reset(DataType* ptr = nullptr)
	{
		// save original data pointer
		DataType* oldPtr = dataPtr;

		// save incoming pointer to the internal data pointer; its associated
		// object is now managed by this instance
		dataPtr = ptr;

		// safely delete and free memory for the previous object
		SAFE_DELETE(oldPtr);
	}

	// =======================================================================
	// swaps the managed object of another unique pointer with this instance's
	// =======================================================================
	void swap(UniquePtr& ptr)
	{
		// move this instance's contents to a temporary instance
		UniquePtr<DataType> tmp(std::move(*this));
		
		// move the incoming pointer's contents to the current instance
		*this = std::move(ptr);

		// move the temporary instance's contents to the incoming pointer
		ptr = std::move(tmp);
	}


	// getters

	// =======================================================================
	// returns a raw pointer to the managed object. this is the non-owning
	// counterpart for unique pointers, as weak pointers are for shared
	// pointers
	// =======================================================================
	DataType* get() { return dataPtr; }


	// prohibited methods (C++11 feature) - uses the delete keyword to prevent
	// the compiler from automatically generating each function

	// =======================================================================
	// bans the copy constructor for unique pointers
	// =======================================================================
	UniquePtr(const UniquePtr&) = delete;

	// =======================================================================
	// bans the copy assignment operator for unique pointers
	// =======================================================================
	UniquePtr& operator=(const UniquePtr&) = delete;
};

#endif // !_ORBIT_UTILS_POINTERS_H