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
#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

namespace Mjl {
namespace Homebrew {

	/*********************
	 * Table of contents *
	 *********************
	 *
	 * SinglyLinkedList<T> class
	 *     - Rule of 3 functions
	 *     - front()
	 *     - back()
	 *     - begin()
	 *     - end()
	 *     - pushFront()
	 *     - pushBack()
	 *     - popFront()
	 *     - size()
	 *
	 * SinglyLinkedList<T>::iterator class
	 *     - operator!=()
	 *     - operator++()
	 *     - operator*()
	 *
	 * Stack<T> class
	 *     - push()
	 *     - pop()
	 *     - top()
	 *     - size()
	 *
	 * Queue<T> class
	 *     - enqueue()
	 *     - dequeue()
	 *     - front()
	 *     - back()
	 *     - size()
	 */

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

	    // Confusingly, the 'int' is used to denote postfix operator in C++
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
	SinglyLinkedList() : head(nullptr), tail(nullptr), theSize(0) { }

	// Copy constructor (1/5)
	SinglyLinkedList(const SinglyLinkedList& toCopy)
	{
		head = nullptr;
		tail = nullptr;

		Node* current = toCopy.head;

		// While there is data in the list we are copying
		while (current != nullptr) {

			// This allocates memory to create a copy of the node
			pushBack(current->data);

			// Keep track of number of elements as we add them
			theSize++;

			current = current->next;
		}

		// List size of new object obviously will be the same size
		theSize = toCopy.size();
	}

	// Move constructor (2/5)
	SinglyLinkedList(SinglyLinkedList&& from) {
		theSize = from.theSize;
		head = from.head;
		from.head = nullptr;
		tail = from.tail;
		from.tail = nullptr;
	}

	// Assignment operator (3/5)
	SinglyLinkedList& operator=(const SinglyLinkedList& source)
	{
		Node* srcPtr = source.head;
		Node* dstPtr = head;
		Node* dstPtrPrev = nullptr;
		Node* temp = nullptr;

		theSize = 0;

		// Case 1: The length of source > destination. Copy elements by value
		//         until destination is out of nodes, then pushBack new nodes.
		//
		// Case 2: The length of source == destination. Simply copy each node
		//         by value.
		//
		// Case 3: The length of source < destination. Copy elements by value,
		//         and once done free memory from rest of source list.

		while (srcPtr != nullptr) {

			if (dstPtr != nullptr) {

				// Case 1 && Case 2:
				dstPtr->data = srcPtr->data;
				dstPtrPrev = dstPtr;
				dstPtr = dstPtr->next;
				theSize++;
			}
			else {

				// Case 1:
				pushBack(srcPtr->data);
			}
			srcPtr = srcPtr->next;
		}
		if (dstPtr != nullptr) {

			// Case 3:

			// Terminate the list
			dstPtrPrev->next = nullptr;

			// Update tail pointer
			this->tail = dstPtrPrev;

			// Now free the remaining items
			while (dstPtr != nullptr) {
				temp = dstPtr;
				dstPtr = dstPtr->next;
				delete temp;
			}
		}

		return *this;
	}

	// Move assignment operator (4/5)
	SinglyLinkedList& operator=(SinglyLinkedList&& from) {

		// Delete old list
		Node* current = head;
		while (current != nullptr) {
			Node* deleteMe = current;
			current = current->next;
			delete deleteMe;
		}

		theSize = from.theSize;
		head = from.head;
		from.head = nullptr;
		tail = from.tail;
		from.tail = nullptr;

		return *this;
	}

	// Destructor (5/5)
	virtual ~SinglyLinkedList()
	{
		Node* current = head;
		Node* temp = nullptr;

		while(current != nullptr) {
			temp = current->next;
			delete current;
			current = temp;
		}
	}

	//
	// Public methods
	//

	unsigned int size(void) const
	{
		return theSize;
	}

	void pushFront(const T& dataPassed)
	{
		Node* newNode = new Node(dataPassed);
		Node* temp = head;

		head = newNode;
		head->next = temp;
		theSize++;
	}

	void pushBack(const T& dataPassed)
	{
		Node* temp = new Node(dataPassed);

		if (this->tail != nullptr) {

			// pushBacking to non-empty list
			this->tail->next = temp;
			this->tail = temp;
			// temp->next == nullptr already at Node::Node()
		}
		else {
			// appending to an empty list
			this->head = temp;
			this->tail = temp;
			// this->tail->next == nullptr already at SinglyLinkedList::SinglyLinkedList()
		}

		// Obviously adding to a list increases it's theSize
		theSize++;
	}

	void popFront(void)
	{
		Node* temp = head;
		head = head->next;
		theSize--;
		delete temp;
	}

	T front(void)
	{
		return head->data;
	}

	T back(void)
	{
		return tail->data;
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
	unsigned int theSize;

}; // end class SinglyLinkedList

/**
 * Stack (LIFO Queue)
 * A stack can be implemented as singly linked list with all operations on the
 * head of the list.
 */
template <typename T> class Stack {
public:

	void push(const T& data)
	{
		list.pushFront(data);
	}

	void pop()
	{
		list.popFront();
	}

	T top()
	{
		return list.front();
	}

	unsigned int size()
	{
		return list.size();
	}

private:

	SinglyLinkedList<T> list;
};

// Queue (FIFO)
//     A queue is just a list where enqueue() maps to pushBack() and
//     dequeue() maps to popFront()
template <typename T> class Queue
{
public:
	void enqueue(const T& data)
	{
		list.pushBack(data);
	}

	void dequeue(void)
	{
		list.popFront();
	}

	T front(void)
	{
		return list.front();
	}

	T back(void)
	{
		return list.back();
	}

	unsigned int size(void)
	{
		return list.size();
	}

private:
	SinglyLinkedList<T> list;
};

}	// end namespace Homebrew
}	// end namespace Mjl

#endif // SINGLYLINKEDLIST_H
