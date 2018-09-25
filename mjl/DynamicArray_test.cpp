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
#include "DynamicArray.h"
#include "DynamicArray_test.h"

#include <iostream>
#include <vector>

using namespace std;
using namespace mjl::homebrew;

bool runArrayTests(void) {
    int x = 4;
    int y = 1234;

    // Test constructor
    DynamicArray<int> da;
    vector<int> va;
    if (da.size() != 0) {
        cerr << "Initial size of da is not 0.\n";
        return false;
    }
    if (da.size() != va.size()) {
        cerr << "Initial sizes of da and va do not match.\n";
        return false;
    }

    // Test count copies of data constructor
    DynamicArray<int> db(x, y);
    vector<int> vb(x, y);
    if (db.size() != vb.size()) {
        cerr << "Sizes of db and vb don't match.\n";
        return false;
    }
    if (db.size() != (unsigned int) x) {
        cerr << "db not initialized with " << x << " elements.\n";
        return false;
    }
    for (unsigned int i = 0; i < vb.size(); i++) {
        if (db[i] != vb[i]) {
            cerr << "Element " << i << " in db and vb does not match, but they should all be copies.\n";
            return false;
        }
    }

    // Test iterator functions
    int count1 = 0, count2 = 0;
    for (DynamicArray<int>::iterator it1 = db.begin(); it1 != db.end(); it1++) {
        count1++;
    }
    for (vector<int>::iterator it2 = vb.begin(); it2 != vb.end(); it2++) {
        count2++;
    }
    if (count1 != count2) {
        cerr << "begin() and end() work differently, which is wrong.\n";
        return false;
    }
    count1 = 0;
    for (DynamicArray<int>::iterator it1 = db.begin(); it1 != db.end(); ++it1) {
        count1++;
    }
    if (count1 != count2) {
        cerr << "begin() and end() work differently, which is wrong.\n";
        return false;
    }

    /*

     iterator(DynamicArray<T>& theParent, unsigned int index) : parent(theParent), currentIndex(0)
     // Copy assignment operator
     iterator& operator=(const iterator& rhs)
     // Dereference operator
     T& operator*()

     *Tested* iterator& operator++()    	// Prefix increment operator (++c)
     *Tested* iterator operator++(int)	// Postfix increment operator (c++)
     *Tested* bool operator!=(const iterator& it) const
     bool operator==(const iterator& it) const

     *Tested* DynamicArray() : theSize(0), theCapacity(initialArrayCapacity)
     *Tested* DynamicArray(int count, const T& data) : array(nullptr), theSize(count), theCapacity(initialArrayCapacity)
     DynamicArray(DynamicArray<T>::iterator& start, DynamicArray<T>::iterator& end)
     // Copy constructor
     DynamicArray(const DynamicArray& from)
     // Move constructor
     DynamicArray(DynamicArray&& from) noexcept
     // Copy assignment operator
     DynamicArray& operator=(const DynamicArray& from)
     // Move assignment operator
     DynamicArray& operator=(DynamicArray&& from)
     virtual ~DynamicArray()
     DynamicArray<T>::iterator begin(void)
     DynamicArray<T>::iterator end(void)
     T& operator[](unsigned int i)
     const T& operator[](unsigned int i) const
     void append(T data)
     int size(void)
     int capacity(void)
     void clear(void)

     */

    return true;
}
