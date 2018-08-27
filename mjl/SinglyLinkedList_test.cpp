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
#include "SinglyLinkedList.h"
#include <iostream>

using namespace std;
using namespace mjl::homebrew;

bool runSinglyLinkedListTests()
{
	bool testResult = false;

	SinglyLinkedList<int> aaa;
	SinglyLinkedList<int> longList;
	SinglyLinkedList<int> shortList;
	SinglyLinkedList<int>::iterator itr;

	cout << "Adding 1, 2, 3 to aaa.\n";

	aaa.pushBack(1);
	aaa.pushBack(2);
	aaa.pushBack(3);

	cout << "Size of aaa: " << aaa.size() << "\n";

	cout << "Adding 1, 2, 3, 5, 8, 13, 21 to longList.\n";

	longList.pushBack(1);
	longList.pushBack(2);
	longList.pushBack(3);
	longList.pushBack(5);
	longList.pushBack(8);
	longList.pushBack(13);
	longList.pushBack(21);

	cout << "Size of longList: " << longList.size() << "\n";

	cout << "Adding 53 to shortList.\n";

	shortList.pushBack(53);

	cout << "Size of shortList: " << shortList.size() << "\n";

	// FIXME: Learn C++11 iteration
	cout << "Iterating over aaa.\n";
	for (itr = aaa.begin(); itr != aaa.end(); itr++) {
		cout << *itr << " ";
	}
	cout << endl;
	cout << "Adding 2 to every item in aaa\n";
	for (itr = aaa.begin(); itr != aaa.end(); itr++) {
		*itr += 2;
	}
	cout << "Iterating over aaa.\n";
	for (itr = aaa.begin(); itr != aaa.end(); itr++) {
		cout << *itr << " ";
	}
	cout << endl;

	// Call copy constructor
	cout << "Constructing bbb as a copy of aaa.\n";
	mjl::homebrew::SinglyLinkedList<int> bbb(aaa);
	for (itr = bbb.begin(); itr != bbb.end(); itr++) {
		cout << *itr << " ";
	}
	cout << endl;

	cout << "Size of bbb: " << bbb.size() << "\n";

	// Call assignment operator
	cout << "Assigning longList to aaa, then iterating over aaa.\n";
	aaa = longList;
	for (itr = aaa.begin(); itr != aaa.end(); itr++) {
		cout << *itr << " ";
	}
	cout << endl;
	cout << "Size of aaa: " << aaa.size() << "\n";

	cout << "Assigning shortList to aaa, then iterating over aaa.\n";
	aaa = shortList;
	for (itr = aaa.begin(); itr != aaa.end(); itr++) {
		cout << *itr << " ";
	}
	cout << endl;
	cout << "Size of aaa: " << aaa.size() << "\n";

	cout << "Assigning bbb (";
	for (itr = bbb.begin(); itr != bbb.end(); itr++) {
	    cout << *itr << " ";
    }
	cout << ") to aaa (";
	for (itr = aaa.begin(); itr != aaa.end(); itr++) {
        cout << *itr << " ";
    }
    cout << "), then iterating over aaa.\n";

	aaa = bbb;
	for (itr = aaa.begin(); itr != aaa.end(); itr++) {
		cout << *itr << " ";
	}
	cout << endl;
	cout << "Size of aaa: " << aaa.size() << "\n";

	cout << "Font of aaa: " << aaa.front() << "\n";

	cout << "Back of aaa: " << aaa.back() << "\n";

	cout << "Adding 17 to front of aaa.\n";
	aaa.pushFront(17);
	cout << "Front of aaa is: " << aaa.front() << "\n";

	cout << "Adding 379 to back of aaa\n";
	aaa.pushBack(379);
	cout << "Back of aaa is: " << aaa.back() << "\n";

	cout << "Popping from aaa.\n";
	int temp = aaa.front();
	aaa.popFront();
	cout << "Value popped from aaa: " << to_string(temp) << "\n";
	cout << "Value at front of aaa: " << aaa.front() << "\n";

	// Tested:
	//iterator() : node(nullptr) { }
	//iterator(Node* theNode) : node(theNode) { }
    //bool operator!=(const iterator& it)
	//SinglyLinkedList() : head(nullptr), tail(nullptr) { }
	//void pushBack(const T& dataPassed)
	//SinglyLinkedList<T>::iterator begin(void)
	//SinglyLinkedList<T>::iterator end(void)
    //void operator++(int)
	//SinglyLinkedList(const SinglyLinkedList& toCopy)
	//const T& operator*()
	//SinglyLinkedList& operator=(const SinglyLinkedList& source)
	//Node(T dataPassedByValue) : data(dataPassedByValue), next(nullptr) { }
	//virtual ~SinglyLinkedList()
	// size()
	// front()
	// back()
	// pushFront()
	// pushBack()
	// popFront()

	// Not yet tested:

	//SinglyLinkedList(SinglyLinkedList&&);
	//SinglyLinkedList& operator=(SinglyLinkedList&&);

	testResult = true;

	return testResult;
};

