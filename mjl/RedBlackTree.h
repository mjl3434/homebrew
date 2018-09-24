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
/*
 * A large portion of this code was influenced by an article on Red-Black trees
 * found on the website eternallyconfuzzled.com circa September 2018. The
 * licensing terms shown here below were found on that site. I believe they are
 * fully compatible with the MIT license used throughout this library.
 */
/*
 * Licensing and fair usage
 * ------------------------
 * What license does Eternally Confuzzled use? Can you copypasta my stuff? Yes!
 * The content on this site is public domain, and I couldn't care less what you
 * use or how you use it. Anything else would defeat the purpose of the site,
 * which is to facilitate knowledge transfer and make life easier for
 * programmers. I don't even care if you copy entire articles verbatim and place
 * them elseweb. They wouldn't be updated to match the latest site, but that's
 * your problem, not mine. :)
 *
 * All that said, I can't make it clear enough that I accept no responsibility
 * at all for damages caused by direct use of content or modified content. I
 * don't anticipate any such damages, but public domain means you're on your
 * own. Do what you will, and don't come crying to me if something breaks. If
 * any of my published content is wrong or broken somehow, I'd love to hear
 * about it so I can fix it here, of course. Feedback is always welcome; that
 * hasn't changed. Further, I'll be happy to respond with my thoughts and
 * suggested fixes for your problems, and those are public domain as well.
 *
 * Long story short, help yourself. Though in legal terms I'm completely off the
 * hook for what you choose to do. Keep that in mind.
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
template<typename K, typename V> class RedBlackTree {
 public:

    static const int RED = 0;
    static const int BLACK = 1;
    static const int LEFT = 0;
    static const int RIGHT = 1;

    class Node {
     public:
        Node(const K theKey, const V theValue)
                        : link{ nullptr, nullptr },
                          color(RED),
                          key(theKey),
                          value(theValue) {
        }
        Node(void) : link{ nullptr, nullptr }, color(RED) { }
        Node* link[2];
        int color;
        K key;
        V value;
    };

    // Constructor
    RedBlackTree() : treeRoot(nullptr) { }

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

// BEGIN DEBUGGING HELPER FUNCTIONS
    int findHeight(Node* node) {
        if (node == nullptr) {
            return -1;
        }

        int leftHeight = findHeight(node->link[LEFT]);
        int rightHeight = findHeight(node->link[RIGHT]);

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
            printGivenLevel(node->link[LEFT], level - 1);
            printGivenLevel(node->link[RIGHT], level - 1);
        }
    }

    int verifyTree(void) {
        return redBlackAssert(treeRoot);
    }

    int redBlackAssert(Node* root) {

        int leftHeight = -1;
        int rightHeight = -1;

        if (root == nullptr) {
            return 1;
        }

        Node* leftNode = root->link[LEFT];
        Node* rightNode = root->link[RIGHT];

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
// END DEBUGGING HELPER FUNCTIONS


    // By design do not support the operator[]. While the syntax is cool, the
    // usage here is not intuitive which makes it prone to developer error.
    // -- Is this fundamentally a search, or an insert function? Both?
    // -- What is returned if noting is stored under that key?
    // -- What happens if there is something already there?
    //
    // V& operator[](const K& key);

    V& find(const K& key);

    // Inserts a new element with the given key, if the same key is already
    // present the value will be overwritten.
    void insert(const K& key, const V& value) {
        topDownInsert(key, value);
    }

    V remove(const K& key) {
        return topDownRemove(key);
    }

 private:

    void topDownInsert(const K& key, const V& value) {

        if (treeRoot == nullptr) {
            treeRoot = new Node(key, value);
            treeRoot->color = BLACK;
            return;
        }

        // FIXME: Rename to "falseTreeRoot"
        Node head;   // False tree root
        Node* g = nullptr;  // Grandparent & parent
        Node* t = nullptr;
        Node* p = nullptr;  // Iterator & parent
        Node* q = nullptr;
        int direction = -1;
        int lastDirection = -1;

        // Set up helpers
        t = &head;
        t->link[RIGHT] = treeRoot;
        q = treeRoot;

        // Search down the tree
        while (true) {

            if (q == nullptr) {
                // Insert new node at the bottom
                q = new Node(key, value);
                p->link[direction] = q;

            } else if (isRed(q->link[LEFT]) && isRed(q->link[RIGHT])) {
                // Color flip
                q->color = RED;
                q->link[LEFT]->color = BLACK;
                q->link[RIGHT]->color = BLACK;
            }

            // Fix red violation
            if (isRed(q) && isRed(p)) {

                int direction2 = t->link[RIGHT] == g;

                if (q == p->link[lastDirection]) {
                    t->link[direction2] = singleRotation(g, !lastDirection);
                } else {
                    t->link[direction2] = doubleRotation(g, !lastDirection);
                }
            }

            // Stop if found
            if (q->value == value) {
                break;
            }

            lastDirection = direction;
            direction = q->value < value;

            // Update helpers
            if (g != NULL) {
                t = g;
            }

            g = p, p = q;
            q = q->link[direction];
        }

        // Update root
        treeRoot = head.link[RIGHT];

        // Make root black
        treeRoot->color = BLACK;
    }

    V topDownRemove(const K& key) {

    }

    /*
    int jsw_remove(struct jsw_tree *tree, int data)
    {
        if (tree->root != NULL)
        {
            struct jsw_node head = { 0 }; // False tree root
            struct jsw_node *q, *p, *g; // Helpers
            struct jsw_node *f = NULL;  // Found item
            int dir = 1;

            // Set up helpers
            q = &head;
            g = p = NULL;
            q->link[1] = tree->root;

            // Search and push a red down
            while (q->link[dir] != NULL)
            {
                int last = dir;

                // Update helpers
                g = p, p = q;
                q = q->link[dir];
                dir = q->data < data;

                // Save found node
                if (q->data == data)
                {
                    f = q;
                }

                // Push the red node down
                if (!is_red(q) && !is_red(q->link[dir]))
                {
                    if (is_red(q->link[!dir]))
                    {
                        p = p->link[last] = jsw_single(q, dir);
                    }
                    else if (!is_red(q->link[!dir]))
                    {
                        struct jsw_node *s = p->link[!last];

                        if (s != NULL)
                        {
                            if (!is_red(s->link[!last]) && !is_red(s->link[last]))
                            {
                                // Color flip
                                p->red = 0;
                                s->red = 1;
                                q->red = 1;
                            }
                            else
                            {
                                int dir2 = g->link[1] == p;

                                if (is_red(s->link[last]))
                                {
                                    g->link[dir2] = jsw_double(p, last);
                                }
                                else if (is_red(s->link[!last]))
                                {
                                    g->link[dir2] = jsw_single(p, last);
                                }

                                // Ensure correct coloring
                                q->red = g->link[dir2]->red = 1;
                                g->link[dir2]->link[0]->red = 0;
                                g->link[dir2]->link[1]->red = 0;
                            }
                        }
                    }
                }
            }

            // Replace and remove if found
            if (f != NULL)
            {
                f->data = q->data;
                p->link[p->link[1] == q] = q->link[q->link[0] == NULL];
                free(q);
            }

            // Update root and make it black
            tree->root = head.link[1];

            if (tree->root != NULL)
            {
                tree->root->red = 0;
            }
        }

        return 1;
    }
    */

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

        Node* temp = root->link[!direction];
        root->link[!direction] = temp->link[direction];
        temp->link[direction] = root;

        root->color = RED;
        temp->color = BLACK;

        return temp;
    }

    Node* doubleRotation(Node* root, int direction) {

        Node* temp = nullptr;

        root->link[!direction] = singleRotation(root->link[!direction], !direction);
        temp = singleRotation(root, direction);

        return temp;
    }

    Node* treeRoot;
};

} /* namespace homebrew */
} /* namespace mjl */

#endif /* REDBLACKTREE_H */
