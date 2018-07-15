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
#ifndef REDBLACKTREE_H_
#define REDBLACKTREE_H_

namespace mjl {
namespace homebrew {

/**
 * Red-Black trees maintain the following rules:
 * 1. A red node can only have black nodes as children
 * 2. The number of black nodes along any path in a red-black tree must be the same.
 * 3. The root node must be black, and leaves are black
 */
template <typename K, typename V> class RedBlackTree
{
public:

	static const int RED = 0;
	static const int BLACK = 1;

	class Node
	{
	public:
		Node(V dataPassedByValue) : color(BLACK), data(dataPassedByValue), left(nullptr), right(nullptr) { }
		int color;
		V data;
		Node* left;
		Node* right;
	};

	// Constructor
	RedBlackTree() : root(nullptr) { }

	// Copy Constructor
	RedBlackTree(const RedBlackTree& from);

	// Move Constructor
	RedBlackTree(RedBlackTree&& from);

	// Assignment Operator
	RedBlackTree& operator=(const RedBlackTree& from);

	// Move Assignment Operator
	RedBlackTree& operator=(RedBlackTree&& from);

	// Destructor
	virtual ~RedBlackTree();

	// By design do not support the operator[]. While the syntax is cool, the
	// usage here is not intuitive which makes it prone to developer error.
	// -- Is this fundamentally a search, or an insert function? Both?
	// -- What is returned if noting is stored under that key?
	// -- What happens if there is something already there?
	//
	// V& operator[](const K& key);

	V& find(const K& key);

	// will delete any element that is already there and insert new one
	void insert(const K& key, const V& value) {

	}

	V& remove(const K& key);

private:

	bool isRed(Node* node) {
		if (node != nullptr && node->color == RED)
			return true;
		else
			return false;
	}

	bool isBlack(Node* node) {
		if (node != nullptr && node->color == BLACK)
			return true;
		else
			return false;
	}

	//Node* singleRotation(Node* )

	Node* root;
};

} /* namespace homebrew */
} /* namespace mjl */

#endif /* REDBLACKTREE_H_ */
