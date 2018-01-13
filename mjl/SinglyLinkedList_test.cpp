#include "SinglyLinkedList.h"
#include <iostream>

using namespace std;
using namespace Mjl::Homebrew;

void runSinglyLinkedListTests()
{
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
	Mjl::Homebrew::SinglyLinkedList<int> bbb(aaa);
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

	// Not implemented:

	//SinglyLinkedList(SinglyLinkedList&&);
	//SinglyLinkedList& operator=(SinglyLinkedList&&);











};

