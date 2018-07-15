/*
 * Copyright (c) 2018 Marcus Larwill
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>

using std::ostringstream;
using std::string;

namespace mjl {
namespace homebrew {

    /*********************
     * Table of contents *
     *********************
     *
     * DynamicArray<T>::iterator class
     *
     *     DynamicArray<T>::iterator(DynamicArray<T>& theParent, unsigned int index)
     *     iterator& operator=(const iterator& rhs)
     *     T& operator*()
     *     iterator& operator++()
     *     iterator operator++(int)
     *     bool operator==(const iterator& it) const
     *     bool operator!=(const iterator& it) const
     *
     * DynamicArray<T> class
     *
     *     DynamicArray(const DynamicArray& from)
     *     DynamicArray(DynamicArray&& from)
     *     DynamicArray& operator=(const DynamicArray& from)
     *     DynamicArray& operator=(DynamicArray&& from)
     *     DynamicArray(DynamicArray<T>::iterator& start, DynamicArray<T>::iterator& end)
     *     virtual ~DynamicArray()
     *
     *     DynamicArray<T>::iterator begin(void)
     *     DynamicArray<T>::iterator end(void)
     *     T& operator[](unsigned int i)
     *     const T& operator[](unsigned int i) const
     *     void append(T data)
     *	   int size(void)
	 *     int capacity(void)
	 *     void clear(void)
     *
     */

template <typename T> class DynamicArray
{
public:

	// FIXME: Is this really the best way to get the range constructor to work?
	friend class iterator;

    class iterator
    {
    public:

        iterator(DynamicArray<T>& theParent, unsigned int index) : parent(theParent), currentIndex(0) {

        	ostringstream oss;

            if (index <= theParent.theSize) {
                currentIndex = index;
            }
            else {
            	oss << "Attempted to create iterator to element "
            	    << index << " but DynamicArray has theSize=" << theParent.theSize;
                throw std::out_of_range(string(oss.str()));
            }
        }

        // Copy assignment operator
        iterator& operator=(const iterator& rhs) {
        	this->parent = rhs.parent;
        	this->currentIndex = rhs.currentIndex;
        	return *this;
        }

        // Dereference operator
        T& operator*() {
        	return parent.array[currentIndex];
        }

        // Prefix increment operator (++c)
        iterator& operator++() {
        	if (currentIndex < parent.theSize)
        		currentIndex++;
        	return *this;
        }

        // Postfix increment operator (c++)
        iterator operator++(int) {
        	if (currentIndex < parent.theSize)
        		currentIndex++;
        	return *this;
        }

        bool operator==(const iterator& it) const {
        	// If iterator points to same spot of same object they are equal
        	if (&it.parent == &this->parent && it.currentIndex == this->currentIndex)
        		return true;
        	else
        		return false;
		}

        bool operator!=(const iterator& it) const {
        	if (&it.parent == &this->parent && it.currentIndex == this->currentIndex)
        		return false;
        	else
        		return true;
		}

    private:
        DynamicArray<T>& parent;
        unsigned int currentIndex;
    };


	DynamicArray() : theSize(0), theCapacity(initialArrayCapacity) {
		array = new T[initialArrayCapacity];
		theCapacity = initialArrayCapacity; // FIXME: why is initializer list failing making this necessary?
	}

	// Initialize count copies of data
	DynamicArray(unsigned int count, const T& data) : array(nullptr), theSize(count), theCapacity(initialArrayCapacity) {

		// The number of bits in an int - the number of bits required to represent initialArrayCapacity = 8;
		const unsigned int shiftLimit = std::numeric_limits<unsigned int>::digits - 4;

		// Find next power of two that is >= count
		unsigned int n = theCapacity;
		unsigned int shifts = 0;

		// The shift limit is used to avoid overflow
		while (n < count && shifts < shiftLimit) {
			n = n << 1;	// Left shift 1 in order to multiply by 2
			shifts++;	// Keep track of how many times we have shifted
		}

		// Allocate n T with default constructor
		array = new T[n];

		 // Copy data to newly allocated objects (object T's copy assignment operator is used)
		for(unsigned int i = 0; i < count; i++) {
			array[i] = data;
		}
	}

	// Range constructor
	DynamicArray(DynamicArray<T>::iterator& start, DynamicArray<T>::iterator& end) {

		theSize = end.currentIndex - start.currentIndex + 1;
		theCapacity = start.parent.capacity();

		array = new T[size];

		for (int i = 0; start != end; start++) {
			array[i] = *start;
		}
	}


	// Copy constructor
	DynamicArray(const DynamicArray& from) {

		this->theSize = from.theSize;
		this->theCapacity = from.theCapacity;

		array = new T[from.theCapacity];

		for (unsigned int i = 0; i < from.theSize; i++) {
			array[i] = from.array[i];
		}
	}

	// Move constructor
	DynamicArray(DynamicArray&& from) noexcept {

		theSize = from.theSize;
		theCapacity = from.theCapacity;
		array = from.array;
		from.array = nullptr;
	}

	// Copy assignment operator
	DynamicArray& operator=(const DynamicArray& from) {

		// Case 1: from.theSize < this.theSize
		// Case 2: from.theSize == this.theSize
		// Case 3: from.size > this.theSize

		// Allocate enough memory to hold new array
		T* temp = new T[from.theCapacity];

		// Copy over the data
		for (unsigned int i = 0; i < from.theSize; i++) {
			temp[i] = from.array[i];
		}

		// Free up the old memory
		delete[] array;

		// Assign new memory
		array = temp;

		return *this;
	}

	// Move assignment operator
	DynamicArray& operator=(DynamicArray&& from) noexcept {

		if (this == &from) {
			return *from;
		}

		theSize = from.theSize;
		theCapacity = from.theCapacity;

		delete[] array;
		array = from.array;
		from.array = nullptr;

		return *this;
	}

	virtual ~DynamicArray() {
		delete array;
	}

    DynamicArray<T>::iterator begin(void) {
        return DynamicArray<T>::iterator(*this, 0);
    }

    DynamicArray<T>::iterator end(void) {
        return DynamicArray<T>::iterator(*this, theSize);
    }

	T& operator[](unsigned int i) {
		return array[i];
	}

	const T& operator[](unsigned int i) const {
		return array[i];
	}

	void append(T data) {

		if (theSize + 1 > theCapacity) {

			// Expand the array if necessary
			theCapacity *= 2;
			T* oldArray = array;
			array = new T[theCapacity];
			for (unsigned int i = 0; i < theSize; i++) {
				array[i] = oldArray[i];
			}
			delete[] oldArray;
		}

		array[theSize] = data;
		theSize++;
	}

	unsigned int size(void) {
		return theSize;
	}

	unsigned int capacity(void) {
		return theCapacity;
	}

	void clear(void) {
		delete[] array;
		array = new T[theCapacity];
	}

private:
	T* array;
	unsigned int theSize;						// How many elements is the array holding
	unsigned int theCapacity;					// How many elements can be held without resizing
	static const int initialArrayCapacity = 8;
};

} // end namespace homebrew
} // end namespace mjl

#endif // DYNAMIC_ARRAY_H
