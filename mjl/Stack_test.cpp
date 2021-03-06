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
#include "Stack_test.h"
#include <iostream>
#include "Stack.h"

using namespace std;
using namespace mjl::homebrew;

bool runStackTests(void) {
    int i = 1;

    Stack<int> intStack;

    cout << "Size of intStack is " << intStack.size() << "\n";

    while (i <= 10) {
        intStack.push(i);
        cout << "Pushing " << i << "\n";
        i++;
    }

    cout << "Size of intStack is " << intStack.size() << "\n";

    while (intStack.size() > 0) {
        cout << "Popping " << intStack.top() << "\n";
        intStack.pop();
    }

    // Tested:
    //void push(const T& data)
    //void pop()
    //T top()
    //unsigned int size()

    return true;
}
