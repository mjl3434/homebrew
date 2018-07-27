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

using namespace std;
using namespace mjl::homebrew;


bool runHashTableTests()
{
	bool testResult = false;

	unordered_map<int, int> stdHash;
	HashTable<int, int> myHash;
	list<pair<int, int> > testData;

	testData.push_back(std::make_pair(1, 1));
	testData.push_back(std::make_pair(2, 2));
	testData.push_back(std::make_pair(3, 3));
	testData.push_back(std::make_pair(4, 4));
	testData.push_back(std::make_pair(5, 5));
	testData.push_back(std::make_pair(33, 33));
	testData.push_back(std::make_pair(34, 34));
	testData.push_back(std::make_pair(35, 35));
	testData.push_back(std::make_pair(36, 36));
	testData.push_back(std::make_pair(37, 37));
	testData.push_back(std::make_pair(65, 65));
	testData.push_back(std::make_pair(66, 66));
	testData.push_back(std::make_pair(67, 67));
	testData.push_back(std::make_pair(68, 68));
	testData.push_back(std::make_pair(69, 69));


	cout << "Inserting 1, 2, 3, 4, 5 in unordered_map and HashTable\n";
	for (list<pair<int, int> >::iterator it = testData.begin();
	     it != testData.end();
	     it++) {
		stdHash[it->first] = it->second;
		myHash.insert(it->first, it->second);

	}



	int stdInt1 = stdHash[1];
	int stdInt2 = stdHash[2];
	int stdInt3 = stdHash[3];
	int stdInt4 = stdHash[4];
	int stdInt5 = stdHash[5];
	cout << "Extracted " << stdInt1 << " "
			             << stdInt2 << " "
			             << stdInt3 << " "
			             << stdInt4 << " "
			             << stdInt5 << " \n";

	int myInt1 = myHash.get(1);
	int myInt2 = myHash.get(2);
	int myInt3 = myHash.get(3);
	int myInt4 = myHash.get(4);
	int myInt5 = myHash.get(5);
	cout << "Extracted " << myInt1 << " "
			             << myInt2 << " "
			             << myInt3 << " "
			             << myInt4 << " "
			             << myInt5 << " \n";



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

