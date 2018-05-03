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
#include "DynamicArray.h"
#include "DynamicArray_test.h"

#include <iostream>

using namespace std;
using namespace Mjl::Homebrew;

void runArrayTests(void)
{
    int i = 0;

    // Test constructor
    DynamicArray<int> da;

    // Test append()
    da.append(i++);
    da.append(i++);
    da.append(i++);
    da.append(i++);
    da.append(i);     // 0, 1, 2, 3, 4

    DynamicArray<int>::iterator daItr = da.begin();
    for (daItr = da.begin(); daItr != da.end(); daItr++) {
        cout << *daItr << "\n";
    }

    // Test copy constructor
    DynamicArray<int> db(da);
    DynamicArray<int>::iterator dbItr = db.begin();
    for (dbItr = db.begin(); dbItr != db.end(); dbItr++) {
    	cout << *dbItr << "\n";
    }

    // Test copy assignment operator
    DynamicArray<int> dc = da;
    DynamicArray<int>::iterator dcItr = dc.begin();
    for (dcItr = dc.begin(); dcItr != dc.end(); dcItr++) {
    	cout << *dcItr << "\n";
    }


}
