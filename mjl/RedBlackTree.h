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
#include <stdlib.h>

using std::cout;

namespace mjl {
namespace homebrew {

/**
 * Red-Black trees maintain the following rules:
 * 1. A red node can only have black nodes as children
 * 2. The number of black nodes along any path in a red-black tree must be the same.
 * 3. The root node must be black, and leaves are black
 */
template<typename V> class RedBlackTree {
 public:

    static const int RED = 0;
    static const int BLACK = 1;
    static const int LEFT = 0;
    static const int RIGHT = 1;

    class Node {
     public:
        Node(const V dataPassedByValue)
                        : color(RED),
                          value(dataPassedByValue),
                          left(nullptr),
                          right(nullptr) {
        }
        Node(void)
                        : color(RED),
                          left(nullptr),
                          right(nullptr) {
        }
        int color;
        V value;
        Node* left;
        Node* right;
    };

    // Constructor
    RedBlackTree()
                    : treeRoot(nullptr) {
    }

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

    V& find(const V& value);

    // Inserts a new element with the given key, if the same key is already
    // present the value will be overwritten.
    int insert(const V value) {

        treeRoot = insertRecursive(treeRoot, value);
        treeRoot->color = BLACK;

        return 1;
    }

    int findHeight(Node* node) {
        if (node == nullptr) {
            return -1;
        }

        int leftHeight = findHeight(node->left);
        int rightHeight = findHeight(node->right);

        if (leftHeight > rightHeight)
            return leftHeight + 1;
        else
            return rightHeight + 1;
    }

    void printLevelOrder(void) {

        int treeHeight = findHeight(treeRoot) + 1;

        if (treeHeight == -1)
            return;

        for (int level = 1; level <= treeHeight; level++) {
            printGivenLevel(treeRoot, level);
            cout << "\n";
        }
    }

    void printGivenLevel(Node* node, int level) {

        if (node == nullptr) {
            cout << "x ";
            return;
        }

        if (level == 1) {
            cout << node->value << " ";
        } else if (level > 1) {
            printGivenLevel(node->left, level - 1);
            printGivenLevel(node->right, level - 1);
        }
    }

    int topDownInsert(const V value) {

        Node fakeRoot;
        Node* grandparent = nullptr;    // g
        Node* greatgrandparent = nullptr;        // t
        Node* parent = nullptr;            // p
        Node* current = nullptr;        // q
        int direction = LEFT;
        int lastDirection = -1;

        if (treeRoot == nullptr) {
            treeRoot = new Node(value);
        } else {

            greatgrandparent = &fakeRoot;
            current = greatgrandparent->right = treeRoot;

            while (true) {    // Search down the tree

                /*
                 std::cout << "New pass through while loop.\n";
                 if (grandparent != nullptr)
                 std::cout << "grandparent = " << grandparent->value << "\n";
                 else
                 std::cout << "grandparent = nullptr\n";
                 if (greatgrandparent != nullptr)
                 std::cout << "greatgrandparent = " << greatgrandparent->value << "\n";
                 else
                 std::cout << "greatgrandparent = nullptr\n";
                 if (parent != nullptr)
                 std::cout << "parent = " << parent->value << "\n";
                 else
                 std::cout << "parent = nullptr\n";
                 if (current != nullptr)
                 std::cout << "current = " << current->value << "\n";
                 else
                 std::cout << "current = nullptr\n";
                 std::cout << "\n\n";
                 */

                if (current == nullptr) {
                    // We have reached a leaf, so insert new node at the bottom
                    if (direction == LEFT) {
                        parent->left = current = new Node(value);
                    } else {    // direction == RIGHT
                        parent->right = current = new Node(value);
                    }
                } else if (isRed(current->left) && isRed(current->right)) {
                    cout << "Color flip of parent " << current->value
                                    << " to RED and left child "
                                    << current->left->value
                                    << " and right child "
                                    << current->right->value << " to BLACK\n";
                    // Color flip
                    current->color = RED;
                    current->left->color = BLACK;
                    current->right->color = BLACK;
                }

                // Fix red violations
                if (isRed(current) && isRed(parent)) {

                    int direction2 =
                                    (greatgrandparent->right == grandparent) ?
                                                    RIGHT : LEFT;

                    if (lastDirection == LEFT) {
                        if (direction2 == LEFT)
                            if (current == parent->left) {
                                std::cout << "Single rotate right around "
                                                << grandparent->value << "\n";
                                greatgrandparent->left = singleRotation(
                                                grandparent, RIGHT);
                            } else {
                                std::cout << "Double rotate right around "
                                                << grandparent->value << "\n";
                                greatgrandparent->left = doubleRotation(
                                                grandparent, RIGHT);
                            }
                        else    // direction2 == RIGHT
                        if (current == parent->left) {
                            std::cout << "Single rotate right around "
                                            << grandparent->value << "\n";
                            greatgrandparent->left = singleRotation(grandparent,
                                                                    RIGHT);
                        } else {
                            std::cout << "Double rotate right around "
                                            << grandparent->value << "\n";
                            greatgrandparent->left = doubleRotation(grandparent,
                                                                    RIGHT);
                        }
                    } else {    // lastDirection == RIGHT
                        if (direction2 == LEFT)
                            if (current == parent->right) {
                                std::cout << "Single rotate left around "
                                                << grandparent->value << "\n";
                                greatgrandparent->right = singleRotation(
                                                grandparent, LEFT);
                            } else {
                                std::cout << "Double rotate left around "
                                                << grandparent->value << "\n";
                                greatgrandparent->right = doubleRotation(
                                                grandparent, LEFT);
                            }
                        else    // direction2 == RIGHT
                        if (current == parent->right) {
                            std::cout << "Single rotate left around "
                                            << grandparent->value << "\n";
                            greatgrandparent->right = singleRotation(
                                            grandparent, LEFT);
                        } else {
                            std::cout << "Double rotate left around "
                                            << grandparent->value << "\n";
                            greatgrandparent->right = doubleRotation(
                                            grandparent, LEFT);
                        }
                    }
                }

                // Stop if found
                if (current->value == value) {
                    break;
                }

                lastDirection = direction;
                direction = (current->value < value) ? RIGHT : LEFT;

                // Update helpers
                if (grandparent != nullptr) {
                    greatgrandparent = grandparent;
                }
                grandparent = parent;
                parent = current;
                current = (direction == LEFT) ? current->left : current->right;
            }

            treeRoot = fakeRoot.right;
        }

        treeRoot->color = BLACK;

        return 1;
    }

    Node* insertRecursive(Node* root, const V value) {

        if (root == nullptr) {
            root = new Node(value);
        } else if (value == root->value) {
            // Keep the tree and key the same, simply overwrite the value
            root->value = value;
            cout << "Inserting duplicate node\n";
        } else {

            int direction = (root->value < value) ? RIGHT : LEFT;

            if (direction == LEFT) {

                cout << "Inserting " << value << " to the left of "
                                << root->value << ".\n";

                root->left = insertRecursive(root->left, value);

                if (isRed(root->left)) {

                    if (isRed(root->right)) {

                        cout << "Both children are red, doing color flip.\n";

                        root->color = RED;
                        root->left->color = BLACK;
                        root->right->color = BLACK;
                    } else {

                        if (isRed(root->left->left)) {

                            cout << "Doing single rotation to the right.\n";
                            root = singleRotation(root, RIGHT);
                        } else if (isRed(root->left->right)) {

                            cout << "Doing double rotation to the right.\n";
                            root = doubleRotation(root, RIGHT);
                        }
                    }
                }

            } else {    // direction == RIGHT

                cout << "Inserting " << value << " to the right of "
                                << root->value << ".\n";

                root->right = insertRecursive(root->right, value);

                if (isRed(root->right)) {

                    if (isRed(root->left)) {

                        cout << "Both children are red, doing color flip.\n";

                        root->color = RED;
                        root->right->color = BLACK;
                        root->left->color = BLACK;
                    } else {

                        if (isRed(root->right->right)) {

                            cout << "Doing double rotation to the left.\n";
                            root = singleRotation(root, LEFT);
                        } else if (isRed(root->right->left)) {

                            cout << "Doing double rotation to the left.\n";
                            root = doubleRotation(root, LEFT);
                        }
                    }
                }
            }
        }

        return root;
    }

    Node* removeRecursive(Node* node, V& value, bool& done) {

        // We have reached the leaf, we are done
        if (node == nullptr) {
            done = true;
            return node;
        }

        int direction = -1;

        // We found the node that must be removed
        if (node->value == value) {

            // If there are zero or one child removal is simple
            if (node->left == nullptr || node->right == nullptr) {

                // Save a pointer to the (possibly) non-null node
                Node* save = nullptr;
                if (node->left == nullptr)
                    save = node->right;
                else
                    save = node->left;

                if (isRed(node)) {
                    // Removing a red node cannot case a violation so we're done
                    done = true;
                } else if (isRed(save)) {
                    // Fix the child's color, to be color of parent (black)
                    save->color = BLACK;
                    done = true;
                }

                delete node;

                return save;

            } else {    // The node has 2 children

                Node* heir = node->left;

                // If the node has two children, we find its in-order
                // predecessor and copy the predecessor's data into the node.
                // Then we recursively delete the predecessor, since it's
                // guaranteed to have at most one child
                while (heir->right != nullptr) {
                    heir = heir->right;
                }

                node->value = heir->value;
                value = heir->value;
            }
        }

        // Go further down the branches to locate the node to remove
        direction = (node->value < value) ? LEFT : RIGHT;
        if (direction == LEFT) {
            node->left = removeRecursive(node->left, value, done);
        } else {
            node->right = removeRecursive(node->right, value, done);
        }

        if (done == false) {
            node = removeBalance(node, value, done);
        }

        return node;
    }

    Node* removeBalance(Node* note, V& value, bool done) {

    }

    int verifyTree(void) {
        return redBlackAssert(treeRoot);
    }

    bool remove(const V& value) {

        bool done = false;

        treeRoot = removeRecursive(value, &done);

        if (treeRoot != nullptr) {
            treeRoot->color = BLACK;
        }

        return true;
    }

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

        } else {    // direction == RIGHT

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
        } else {    // direction == RIGHT
            root->left = singleRotation(root->left, LEFT);
            temp = singleRotation(root, RIGHT);
        }

        return temp;
    }

    int redBlackAssert(Node* root) {

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
        if ((leftNode != nullptr && leftNode->value >= root->value)
                        || (rightNode != nullptr
                                        && rightNode->value <= root->value)) {
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
            } else {
                return leftHeight + 1;
            }
        } else {
            return 0;
        }
    }

    Node* treeRoot;
};

} /* namespace homebrew */
} /* namespace mjl */

#endif /* REDBLACKTREE_H */
