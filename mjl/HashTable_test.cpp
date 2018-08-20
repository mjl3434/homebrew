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
#include "HashTable.h"

#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <utility>

#include <stdlib.h>

using namespace std;
using namespace mjl::homebrew;

bool runHashTableTests()
{
	bool testResult = false;
	const int TEST_SIZE = 100;

	unordered_map<int, int> stdHash;
	HashTable<int, int> myHash;
	list<pair<int, int> > testData;

	for (int i = 1; i <= TEST_SIZE; i++) {
		cout << "Adding " << i << ", " << i << " to test data.\n";
		testData.push_back(std::make_pair(i, i));
	}

	cout << "Inserting data in STL unordered_map, and custom hash table.\n";
	for (list<pair<int, int> >::iterator it = testData.begin();
	     it != testData.end();
	     it++) {
		stdHash[it->first] = it->second;
		myHash.insert(it->first, it->second);
	}

	cout << "Extracted from STL unordered_map: ";
	for (int i = 1; i <= TEST_SIZE; i++) {
		int stdInt = stdHash[i];
		cout << stdInt << ", ";
	}
	cout << "\n";

	cout << "Extracted from custom hash table: ";
	for (int i = 1; i <= TEST_SIZE; i++) {
		int myInt = myHash.get(i);
		cout << myInt << ", ";
	}
	cout << "\n";




	/*
	Tested:
	HashTable() : hashTableSize(initialHashTableSize), size(0), table(new Bucket<K, V>[initialHashTableSize])
	void insert(const K& key, const V& value)
	V& get(const K& key)

	Not Tested:

	Bucket(void) : key(nullptr), value(nullptr), next(nullptr)
	Bucket(const K& theKey, const V& theValue)
	static unsigned int chooseBucket(const K& k)
	static unsigned int chooseBucket(const short& k)

	HashTable(const HashTable& from)
	HashTable(HashTable&& from) noexcept
	HashTable& operator=(const HashTable& from)
	HashTable& operator=(HashTable&& from) noexcept
	virtual ~HashTable()


	V& remove(const K& key)
	void commonCopy(HashTable& to, const HashTable& from)
	void commonDelete(void)
	unsigned int selectBucket(const K& k)
	void rehash(void)

	 */

	return testResult;
}

