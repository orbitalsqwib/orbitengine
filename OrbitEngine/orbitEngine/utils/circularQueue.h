// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Circular Queue Generic
// ===========================================================================

#ifndef _ORBIT_UTILS_CIRCULARQUEUE_H
#define _ORBIT_UTILS_CIRCULARQUEUE_H

// import necessary headers
#include "../error.h"
#include <vector>


// main definition

// defines a circular deque of generic elements, which is contiguous and is
// able to dynamically resize to accommodate additional elements greater than
// its current capacity
template <class ElementType>
class CircularQueue
{
private:

	// typedefs

	// vector of element types - will be used as a fixed size array with
	// delayed capacity reservation, since the automatic resizing behaviour 
	// does not take the properties of a circular queue into account.
	typedef std::vector<ElementType> ELEMENT_VECTOR;


	// members

	// internal data array
	ELEMENT_VECTOR data;

	// index of "head" of queue - guaranteed to be a valid element if queue is
	// not empty
	size_t head;

	// index of "tail" queue - guaranteed to be a valid empty element slot
	// if queue is not full
	size_t tail;

	// current number of elements in the queue
	size_t size;

	// current capacity of the queue
	size_t capacity;


	// private methods

	// =======================================================================
	// grows the data container while maintaining a circular queue structure
	// =======================================================================
	void growCapacity()
	{
		// temporarily record old capacity in case shifting occurs
		size_t nextFreeSlot = capacity;

		// resize current vector to twice its size
		data.resize(capacity *= 2);

		// if tail iterator is behind head iterator, the previous unresized
		// vector was wrapped. to preserve the circular queue structure, shift
		// all elements from the start of the resized vector to the tail 
		// iterator, to fill in the newly allocated empty space after the head
		// iterator.
		//
		// | OLD STATE:
		// |
		// |    tail/head
		// |        v
		// | [a, b, c, d]
		// |
		// | DESIRED OUTCOME:
		// |
		// |      head        tail
		// |        v           v
		// | [?, ?, c, d, a, b, _, _]
		// 
		// NOTE: ? indicates that the element is not re-initialized to the
		// default value, and is still "dirty". this is because new values
		// will always end up writing over these empty slots, and thus there
		// is no need to initialize them if they'll be eventually re-written

		// we should only reorder elements if tail is either before or at head
		if (tail <= head)
		{
			// the elements to the right of head are always guaranteed to be
			// filled if tail did wrap, according to the properties of a
			// circular list. therefore the first free space after head after
			// resizing should be equal to the old capacity of the data vector

			// additionally, all elements of the data vector are guaranteed to
			// fit in after head, even if head was the last element in the old
			// data vector. this is because the max number of elements to move
			// would be capacity - 1, while the number of free slots after 
			// head in the worst-case scenario would be = capacity, leaving 1
			// empty slot over for tail to point to.

			// create a index pointing to the current element to shift
			size_t indexToShift = 0;

			// while the index for the element to shift is < tail,
			while (indexToShift < tail)
			{
				// assign the element at nextFreeSlot to the value of the
				// element to shift. there is no need to initialize the old
				// element to a default value, but we will attempt to move
				// the values out of the old elements as far as possible for
				// compatibility with elements such as unique pointers

				// move data from existing element to new slot
				data[nextFreeSlot] = std::move(data[indexToShift]);

				// increment indexes to select next element
				indexToShift++;
				nextFreeSlot++;
			}

			// once all elements have been shifted, next free slot should
			// still be valid even in the worst-case scenario. thus we can
			// safely assign tail to this value.
			tail = nextFreeSlot;
		}
	}

public:

	// =======================================================================
	// default constructor
	// =======================================================================
	CircularQueue(size_t initialCapacity = 1) :

		// members
		data(0),
		head(0),
		tail(0),
		size(0),
		capacity(initialCapacity)
	{
		// default-initialize capacity elements at the start
		data.resize(capacity);
	}


	// methods

	// =======================================================================
	// adds a new element to the end of the queue
	// =======================================================================
	void pushBack(const ElementType& element)
	{
		// check if queue is full
		if (isFull())
		{
			// resize internal data container
			growCapacity();

			// re-enqueue the element with the new capacity
			return pushBack(element);
		}

		// set slot at tail to element
		data[tail] = element;

		// increment size
		size++;

		// increment tail. if tail index is beyond the last element of the
		// data vector, the modulo wraps it back to the start of the vector
		tail = (tail + 1) % capacity;
	}

	// =======================================================================
	// adds a new element to the start of the queue
	// =======================================================================
	void pushFront(const ElementType& element)
	{
		// check if queue is full
		if (isFull())
		{
			// resize internal data container
			growCapacity();

			// re-enqueue the element with the new capacity
			return pushFront(element);
		}

		// decrement head. if head is at the start of the vector, wrap it back
		// to the end of the vector instead.
		head = head == 0 ? capacity - 1 : head - 1;

		// set slot at new head to element
		data[head] = element;

		// increment size
		size++;
	}

	// =======================================================================
	// removes an element from the end of the queue
	// =======================================================================
	void popBack()
	{
		// check if queue is empty, and return early if so
		if (isEmpty()) return;

		// decrement size
		size--;

		// finally, just decrement tail, as there is no need to re-initialize
		// values for "empty slots" in the queue. if tail is at the start of
		// the vector, wrap it back to the end of the vector instead.
		tail = tail == 0 ? capacity - 1 : tail - 1;
	}

	// =======================================================================
	// removes an element from the start of the queue
	// =======================================================================
	void popFront()
	{
		// check if queue is empty, and return early if so
		if (isEmpty()) return;

		// decrement size
		size--;

		// finally, just increment head, as there is no need to re-initialize
		// values for "empty slots" in the queue. additionally, if head is
		// beyond the last element of the data vector, we should also wrap
		// it back to the start of the vector like we did for the tail
		head = (head + 1) % capacity;
	}


	// getters

	// =======================================================================
	// checks if the current queue is empty
	// =======================================================================
	bool isEmpty() { return size == 0; }

	// =======================================================================
	// checks if the current queue is full
	// =======================================================================
	bool isFull() { return size == capacity; }

	// =======================================================================
	// returns a mutable reference to the element at the start of the queue
	// =======================================================================
	ElementType& peekFront()
	{
		// ensure queue is not empty
		if (isEmpty())

			// else throw exception
			throw Error("Error: Queue is empty, front() is out of range!");

		// return data at head
		return data[head];
	}

	// =======================================================================
	// returns a mutable reference to the element at the end of the queue
	// =======================================================================
	ElementType& peekBack()
	{
		// ensure queue is not empty
		if (isEmpty())

			// else throw exception
			throw Error("Error: Queue is empty, back() is out of range!");

		// get the index for the last element before tail
		size_t lastElementIndex = tail == 0 ? capacity - 1 : tail - 1;

		// return data for the last element
		return data[lastElementIndex];
	}

};

#endif // !_ORBIT_UTILS_CIRCULARQUEUE_H