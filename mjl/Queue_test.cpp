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
#include "Queue_test.h"
#include <iostream>
#include "Queue.h"

using namespace std;
using namespace mjl::homebrew;

bool runQueueTests(void) {
    int i = 1;

    Queue<int> queue;

    while (i <= 10) {
        queue.enqueue(i);
        cout << "Enqueuing " << i << "\n";
        i++;
    }

    cout << "Size of queue: " << queue.size() << "\n";
    cout << "Front of queue: " << queue.front() << "\n";
    cout << "Back of queue: " << queue.back() << "\n";

    cout << "Enqueuing two other elements.\n";
    queue.enqueue(i++);
    queue.enqueue(i++);
    cout << "Size of queue: " << queue.size() << "\n";

    cout << "Dequeuing one element.\n";
    queue.dequeue();
    cout << "Size of queue: " << queue.size() << "\n";

    while (queue.size() > 0) {
        cout << "Dequeuing " << queue.front() << "\n";
        queue.dequeue();
    }

    // Tested:
    //void enqueue(const T& data)
    //void dequeue(void)
    //T front(void)
    //T back(void)
    //unsigned int size(void)

    return true;
}

