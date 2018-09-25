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
#include "RedBlackTree_test.h"
#include "RedBlackTree.h"
#include <iostream>
#include <cstdlib>

using namespace mjl::homebrew;
using std::cout;

bool runRedBlackTreeTests(void) {

	bool retval = false;

	RedBlackTree<int, int> redBlackTree;

	/*
	for (unsigned int i = 0; i < 200; i++) {
		cout << rand() % 200 << " ";
	}
	cout << "\n";
	exit(0);
	 */

	unsigned int index = 0;
	int testData[] = {
			183,  86, 177, 115, 193, 135, 186,  92,  49,  21,
			162,  27,  90,  59, 163, 126, 140,  26, 172, 136,
			 11, 168, 167,  29, 182, 130,  62, 123,  67, 135,
			129,   2,  22,  58,  69, 167, 193,  56,  11,  42,
			 29, 173,  21, 119, 184, 137, 198, 124, 115, 170,
			 13, 126,  91, 180, 156,  73,  62, 170, 196,  81,
			105, 125,  84, 127, 136, 105,  46, 129, 113,  57,
			124,  95, 182, 145,  14, 167,  34, 164,  43, 150,
			 87,   8,  76, 178, 188, 184,   3,  51, 154, 199,
		    132,  60,  76, 168, 139,  12,  26, 186,  94, 139,
			195, 170,  34, 178,  67,   1,  97, 102, 117,  92,
			 52, 156, 101,  80,  86,  41,  65,  89,  44,  19,
			 40, 129,  31, 117,  97, 171,  81,  75, 109, 127,
	        167,  56,  97, 153, 186, 165, 106,  83,  19,  24
	};



	for (index = 0; index < sizeof(testData)/sizeof(testData[0]); index++) {
		cout << "----------------------------------------------------\n";
		cout << "Test " << index+1 << ", inserting: " << testData[index] << " into Red-Black Tree.\n";
		redBlackTree.insert(testData[index], testData[index]);
		redBlackTree.verifyTree();
		redBlackTree.printLevelOrder();
		cout << "\n\n";
	}


	for (index = 0; index < (sizeof(testData)/sizeof(testData[0])/4); index++) {
		cout << "----------------------------------------------------\n";
		cout << "Test " << index+1 << ", removing: " << testData[index] << " from Red-Black Tree.\n";
		bool success = false;
		redBlackTree.remove(testData[index], success);
		if (success == true) {
		    cout << "Removal returned success.\n";
		}
		else {
		    cout << "Removal returned failure.\n";
		}
		redBlackTree.verifyTree();
		redBlackTree.printLevelOrder();
		cout << "\n\n";
	}

	retval = true;

	return retval;
}
