#include "SinglyLinkedList.h"
#include <iostream>

using namespace std;
using namespace Mjl::Homebrew;

void runSinglyLinkedListTests()
{
	SinglyLinkedList<int> intList1;
	SinglyLinkedList<int> longList;
	SinglyLinkedList<int> shortList;
	SinglyLinkedList<int>::iterator intListItr;

	cout << "Adding 1, 2, 3 to intList1.\n";

	intList1.append(1);
	intList1.append(2);
	intList1.append(3);

	cout << "Adding 1, 2, 3, 5, 8, 13, 21 to longList.\n";

	longList.append(1);
	longList.append(2);
	longList.append(3);
	longList.append(5);
	longList.append(8);
	longList.append(13);
	longList.append(21);

	cout << "Adding 53 to shortList.\n";

	shortList.append(53);

	// FIXME: Learn C++11 iteration
	cout << "Iterating over intList1.\n";
	for (intListItr = intList1.begin(); intListItr != intList1.end(); intListItr++) {
		cout << *intListItr << " ";
	}
	cout << endl;
	cout << "Adding 2 to every item in intList1\n";
	for (intListItr = intList1.begin(); intListItr != intList1.end(); intListItr++) {
		*intListItr += 2;
	}
	cout << "Iterating over intList1.\n";
	for (intListItr = intList1.begin(); intListItr != intList1.end(); intListItr++) {
		cout << *intListItr << " ";
	}
	cout << endl;

	// Call copy constructor
	cout << "Constructing intList2 as a copy of intList1.\n";
	Mjl::Homebrew::SinglyLinkedList<int> intList2(intList1);
	for (intListItr = intList2.begin(); intListItr != intList2.end(); intListItr++) {
		cout << *intListItr << " ";
	}
	cout << endl;
	// Call assignment operator
	cout << "Assigning longList to intList1, then iterating over intList1.\n";
	intList1 = longList;
	for (intListItr = intList1.begin(); intListItr != intList1.end(); intListItr++) {
		cout << *intListItr << " ";
	}
	cout << endl;
	cout << "Assigning shortList to intList1, then iterating over intList1.\n";
	intList1 = shortList;
	for (intListItr = intList1.begin(); intListItr != intList1.end(); intListItr++) {
		cout << *intListItr << " ";
	}
	cout << endl;
	cout << "Assigning intList2 to intList1, then iterating over intList1.\n";
	intList1 = intList2;
	for (intListItr = intList1.begin(); intListItr != intList1.end(); intListItr++) {
		cout << *intListItr << " ";
	}
	cout << endl;

	// Tested:
	//iterator() : node(nullptr) { }
	//iterator(Node* theNode) : node(theNode) { }
    //bool operator!=(const iterator& it)
	//SinglyLinkedList() : head(nullptr), tail(nullptr) { }
	//void append(const T& dataPassed)
	//SinglyLinkedList<T>::iterator begin(void)
	//SinglyLinkedList<T>::iterator end(void)
    //void operator++(int)
	//SinglyLinkedList(const SinglyLinkedList& toCopy)
	//const T& operator*()
	//SinglyLinkedList& operator=(const SinglyLinkedList& source)

	// Not tested:
	//Node(T dataPassedByValue) : data(dataPassedByValue), next(nullptr) { }
	//SinglyLinkedList(SinglyLinkedList&&);
	//SinglyLinkedList& operator=(SinglyLinkedList&&);
	//virtual ~SinglyLinkedList()





};

