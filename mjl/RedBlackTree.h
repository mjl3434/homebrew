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
#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>

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
	static const int LEFT = 0;
	static const int RIGHT = 1;

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
	virtual ~RedBlackTree() {

	}

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

	Node* singleRotation(Node* root, int direction) {

		Node* newRoot = nullptr;

        if (direction == LEFT) {

        	newRoot = root->right;
        	root->right = newRoot->left;
        	newRoot->left = root;

        } else { // direction == RIGHT

        	newRoot = root->left;
        	root->left = newRoot->right;
        	newRoot->right = root;

        }

        root->color = RED;
        newRoot->color = BLACK;

        return newRoot;
	}

	Node* doubleRotation(Node* root, int direction) {

		Node* temp = nullptr;

		if (direction == LEFT) {
			root->right = singleRotation(root->right, RIGHT);
			temp = singleRotation(root, LEFT);
		}
		else { // direction == RIGHT
			root->left = singleRotation(root->left, LEFT);
			temp = singleRotation(root, RIGHT);
		}

		return temp;
	}

	bool redBlackAssert(Node* root) {

		int leftHeight = -1;
		int rightHeight = -1;

        if (root == nullptr) {
            return 1;
        }

        Node* leftNode = root->left;
        Node* rightNode = root->right;

        // Check for consecutive red links
        if (isRed(root)) {
            if (isRed(leftNode) || isRed(rightNode)) {
            	std::cerr << "Red violation!\n";
                return 0;
            }
        }

        leftHeight = redBlackAssert(leftNode);
        rightHeight = redBlackAssert(rightNode);

        // Verify binary tree properties (left < root && right > root)
        if ((leftNode != nullptr && leftNode->data >= root->data) || (rightNode != nullptr && rightNode->data <= root->data)) {
        	std::cerr << "Binary tree violation!\n";
        	return 0;
        }

        // Verify black height of both subtrees is equal
        if (leftHeight != 0 && rightHeight != 0 && leftHeight != rightHeight) {
        	std::cerr << "Black violation!\n";
        	return 0;
        }

        // Recursively count the black height
        if (leftHeight != 0 && rightHeight != 0) {

        	if (isRed(root) == true) {
        		return leftHeight;
        	}
        	else {
        		return leftHeight + 1;
        	}
        }
        else {
        	return 0;
        }
	}

	Node* root;
};

} /* namespace homebrew */
} /* namespace mjl */

#endif /* REDBLACKTREE_H */
