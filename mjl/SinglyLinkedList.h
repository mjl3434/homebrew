#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

namespace Mjl {
namespace Homebrew {

	// SinglyLinkedList container must support:
	// .begin - return reference to beginning
	// .end - return reference to end
	// .empty() - return true if empty
	// .size() - returns number of elements in list

	// SinglyLinkedList<T>::iterator must support:

	//std::vector<T>::iterator
	//isEmpty
	//append
	//prepend

	// List
	// Stack (LIFO Queue)
	// Queue (FIFO)



template <typename T> class SinglyLinkedList
{
public:

	class Node
	{
	public:
		Node(T dataPassedByValue) : data(dataPassedByValue), next(nullptr) { }
		T data;
		Node* next;
	};

	class iterator
	{
	public:

		iterator() : node(nullptr) { }
		iterator(Node* theNode) : node(theNode) { }

	    T& operator*()
		{
			return node->data;
		}

	    void operator++(int)
	    {
	    	if (this->node != nullptr)
	    		this->node = this->node->next;
	    }

	    bool operator!=(const iterator& it)
		{
	    	return it.node != this->node;
		}

	    Node* node;
	};



	//
	// The Rule of Five Functions
	//

	// Constructor
	SinglyLinkedList() : head(nullptr), tail(nullptr) { }

	// Copy constructor (1/5)
	SinglyLinkedList(const SinglyLinkedList& toCopy)
	{
		Node* current = toCopy.head;

		// While there is data in the list we are copying
		while (current != nullptr) {

			// This allocates memory to create a copy of the node
			append(current->data);

			current = current->next;
		}
	}

	// Assignment operator (2/5)
	SinglyLinkedList& operator=(const SinglyLinkedList& source)
	{
		Node* srcPtr = source.head;
		Node* dstPtr = head;
		Node* dstPtrPrev = nullptr;
		Node* temp = nullptr;

		// Case 1: The length of source > destination. Copy elements by value
		//         until destination is out of nodes, then append new nodes.
		//
		// Case 2: The length of source == destination. Simply copy each node
		//         by value.
		//
		// Case 3: The length of source < destination. Copy elements by value,
		//         and once done free memory from rest of source list.

		while (srcPtr != nullptr) {

			if (dstPtr != nullptr) {
				dstPtr->data = srcPtr->data;
				dstPtrPrev = dstPtr;
				dstPtr = dstPtr->next;
			}
			else {
				append(srcPtr->data);
			}
			srcPtr = srcPtr->next;
		}
		if (dstPtr != nullptr) {

			// Terminate the list
			dstPtrPrev->next = nullptr;

			// Now free the remaining items
			while (dstPtr != nullptr) {
				temp = dstPtr;
				dstPtr = dstPtr->next;
				delete temp;
			}
		}

		return *this;
	}

	// Move constructor (3/5)
	SinglyLinkedList(SinglyLinkedList&&);

	// Move assignment operator (4/5)
	SinglyLinkedList& operator=(SinglyLinkedList&&);

	// Destructor (5/5)
	virtual ~SinglyLinkedList()
	{
		Node* markedForDestruction = nullptr;
		Node* current = head;

		while(current != nullptr) {
			markedForDestruction = current;
			delete markedForDestruction;
			current = current->next;
		}
	}

	//
	// Public methods
	//

	void append(const T& dataPassed)
	{
		// Create a new Node
		Node* temp = new Node(dataPassed);

		if (tail != nullptr) {
			tail->next = temp;
			temp->next = nullptr;
			tail = temp;
		}
		else {
			head = temp;
			tail = temp;
			tail->next = nullptr;
		}
	}

	SinglyLinkedList<T>::iterator begin(void)
	{
		return SinglyLinkedList<T>::iterator(head);
	}

	SinglyLinkedList<T>::iterator end(void)
	{
		return SinglyLinkedList<T>::iterator(tail->next);
	}


private:

	Node* head;
	Node* tail;

}; // end class SinglyLinkedList


}	// end namespace Homebrew
}	// end namespace Mjl

#endif // SINGLYLINKEDLIST_H
