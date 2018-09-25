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
#include "DynamicArray_test.h"
#include "HashTable_test.h"
#include "Queue_test.h"
#include "RedBlackTree_test.h"
#include "SinglyLinkedList_test.h"
#include "Stack_test.h"

int main() {
    bool status = false;

    status = runSinglyLinkedListTests();
    if (status != true) {
        return -1;
    }

    status = runStackTests();
    if (status != true) {
        return -1;
    }

    status = runQueueTests();
    if (status != true) {
        return -1;
    }

    status = runArrayTests();
    if (status != true) {
        return -1;
    }

    status = runHashTableTests();
    if (status != true) {
        return -1;
    }

    status = runRedBlackTreeTests();
    if (status != true) {
        return -1;
    }

    return 0;
}
