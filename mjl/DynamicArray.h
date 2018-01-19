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

        iterator() : currentIndex(0) {

        }

        T& operator*()
        {
            //return node->data;
            return array[currentIndex];
        }

        void operator++(int)
        {
            //if (this->node != nullptr)
            //    this->node = this->node->next;
        }

        bool operator!=(const iterator& it)
        {
            //return it.node != this->node;
        }

        int currentIndex;
    };

    DynamicArray<T>::iterator begin(void)
    {
        return DynamicArray<T>::iterator(head);
    }

    DynamicArray<T>::iterator end(void)
    {
        return DynamicArray<T>::iterator(tail->next);
    }


	DynamicArray() : size(0), capacity(initialArrayCapacity) {
		array = new T[initialArrayCapacity];
	}

	// Initialize count copies of data
	DynamicArray(int count, const T& data) {

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

	// FIXME: return copy by value, or copy by reference?
	int& operator[](unsigned int i) {
		return array[i];
	}

	// FIXME: Understand the point of separate const operator[]
	//const int& operator[] const() ...

	virtual ~DynamicArray() {
		delete array;
	}

private:
	T* array;
	int size;
	int capacity;
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
