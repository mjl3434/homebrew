/*
 * Copyright (c) 2017 Marcus Larwill
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

namespace Mjl {
namespace Homebrew {

template <typename T> class DynamicArray
{
public:

    /*
    int i = 0;
    DynamicArray<int> da;
    da.append(i++);
    da.append(i++);
    da.append(i++);
    da.append(i++);
    da.append(i);     //  1, 2, 3, 4, 5
    DynamicArray<int>::iterator itr = da.begin();

    for (itr = da.begin(); itr != da.end(); itr++) {
        cout << *itr << "\n";
    }
     */

    class iterator
    {
    public:

        iterator(DynamicArray<T>& theParent, unsigned int index) : parent(theParent), currentIndex(0) {

        	ostringstream oss;

            if (index < size) {
                currentIndex = index;
            }
            else {
            	oss << "Attempted to create iterator to element "
            	    << index << " but DynamicArray has size=" << size;
                throw std::out_of_range(string(oss.str()));
            }
        }

        T& operator*()
        {
            return array[currentIndex];
        }

        void operator++()
        {
        	if (currentIndex < size)
        		currentIndex++;
        }

        bool operator!=(const iterator& it)
        {
        	return &it.currentIndex != &this->currentIndex;

            //return it.node != this->node;
        }

    private:
        DynamicArray<T>& parent;
        int currentIndex;
    };




	DynamicArray() : size(0), capacity(initialArrayCapacity) {
		array = new T[initialArrayCapacity];
	}

	// Initialize count copies of data
	DynamicArray(int count, const T& data) : array(nullptr), size(count), capacity(initialArrayCapacity) {

		// The number of bits in an int - the number of bits required to represent initialArrayCapacity = 8;
		const unsigned int shiftLimit = std::numeric_limits<unsigned int>::digits - 4;

		// Find next power of two that is >= count
		unsigned int n = capacity;
		unsigned int shifts = 0;

		// The shift limit is used to avoid overflow
		while (n < count && shifts < shiftLimit) {
			n = n << 1;	// Left shift 1 in order to multiply by 2
			shifts++;	// Keep track of how many times we have shifted
		}

		// Allocate n T with default constructor
		array = new T[n];

		 // Copy data to newly allocated objects (object T's copy assignment operator is used)
		for(int i = 0; i < count; i++) {
			array[i] = data;
		}
	}

	// Range counstructor

	// Copy constructor
	DynamicArray(const DynamicArray& from) {

	}

	// Assignment operator
	DynamicArray& operator=(const DynamicArray& from) {
		// Case 1: from.size < this.size
		// Case 2: from.size == this.size
		// Case 3: from.size > this.size
	}

	virtual ~DynamicArray() {
		delete array;
	}

    DynamicArray<T>::iterator begin(void)
    {
        return DynamicArray<T>::iterator(0);
    }

    DynamicArray<T>::iterator end(void)
    {
        return DynamicArray<T>::iterator(size-1);
    }

	// FIXME: return copy by value, or copy by reference?
	T& operator[](unsigned int i) {
		return array[i];
	}

	void append(T data) {

		if (size + 1 > capacity) {

			// Expand the array if necessary
			capacity *= 2;
			T* oldArray = array;
			array = new T[capacity];
			for (int i = 0; i < size; i++) {
				array[i] = oldArray[i];
			}
			delete[] oldArray;
		}

		array[size] = data;
		size++;
	}

	// FIXME: Understand the point of separate const operator[]
	//const int& operator[] const() ...



private:
	T* array;
	unsigned int size;
	unsigned int capacity;
	const int initialArrayCapacity = 8;

	// Constructors:
	// 1. Empty array
	// 2. Intialized to N copies of object
	// 3. Copy constructor
	// 4. iterator begin, iterator end

	// operator[] - for read acess
	// operator[] - for write access
	// operator=

	// size() - how many elements are present
	// capacity() - how much memory is currently reserved

	// clear() - delete everything

	// iterators:
	// .begin
	// .end
	// ++

};

} // end namespace Homebrew
} // end namespace Mjl

#endif // DYNAMIC_ARRAY_H
