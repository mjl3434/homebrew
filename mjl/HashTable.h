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
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdexcept>
#include <iostream>

namespace mjl {
namespace homebrew {

template <typename K, typename V> struct Bucket {
public:
	Bucket(void) : key(nullptr), value(nullptr), next(nullptr) {}
	Bucket(const K& theKey, const V& theValue)
	    : key(new K(theKey)), value(new V(theValue)), next(nullptr) {}
	K* key;
	V* value;
	struct Bucket<K, V>* next;
};

// This is a generic implementation of a hash function
template <typename K> class DefaultHashGenerator
{
	static const unsigned int THRESHOLD = 32;

	/**
	 * This is a generic hashing function used to generate an index into a hash
	 * table. It is designed to work with any object type and to treat the
	 * object as an opaque stream of bytes.
	 *
	 * Note that since we have no knowledge of what the object is made of, it
	 * is somewhat a matter of luck as to whether or not the function has the
	 * properties of a good hashing function. Obviously this is not good, so
	 * what a user should do instead is to supply their own hashing function
	 * appropriate for their user-defined type (class).
	 *
	 * A user can supply their own hash function by implementing a template
	 * class just like this one, that takes their user-defined type (class) as
	 * a template parameter, and provides their own implementation of the
	 * chooseBucket function. Within the HashTable itself, the value returned
	 * from the chooseBucket function will be divided by the hash table size,
	 * and the reminder will be used as an index into the table.
	 */
	static unsigned int chooseBucket(const K& k)
	{
		unsigned int sum = 0;
		unsigned char* data = &k;
		unsigned int objectSize = sizeof(k);

		if (objectSize < THRESHOLD) {

			// If object size is small enough do a simple sum
			for (unsigned int i = 0; i < objectSize; i++)
				sum += data[i];
		}
		else {

			// Otherwise sample data evenly distributed across object
			unsigned int fractionSize = objectSize/THRESHOLD;

			for (unsigned int i = 0; i < THRESHOLD; i++) {
				sum += data[i*fractionSize];
			}
		}

		return sum;
	}

};

/*

template <> class DefaultHashGenerator<short>
{
	static unsigned int chooseBucket(const short& k) {
		return (unsigned int)k;
	}
};

template <> class DefaultHashGenerator<unsigned short>
{
	static unsigned int chooseBucket(const unsigned short& k) {
		return (unsigned int)k;
	}
};

etc...

// and the others
//short a;
//int b;
//long c;
//long long d;
//float e;
//double f;
//long double g;

*/

template <> class DefaultHashGenerator<int>
{
public:
	static unsigned int chooseBucket(const int& k) {
		return (unsigned int)k;
	}
};


/* Note: C++ initialization of static constant arrays in template classes sucks
 * so using the preprocessor is perhaps the best way.
 */
#define HASH_TABLE_SIZES 37, 79, 163, 331, 673, 1361, 2729, 5471, 10949, 21893, 43787, 87583
#define INITIAL_HASH_TABLE_SIZE 37
#define NUMBER_OF_SIZES 12

template <typename K, typename V, typename HashGenerator = DefaultHashGenerator<K>> class HashTable {
public:

	// Default constructor
	HashTable()
        : rehashThreshold(0.5f),
          hashTableSizesIndex(0),
		  hashTableSize(INITIAL_HASH_TABLE_SIZE),
		  size(0),
		  table(new Bucket<K, V>[INITIAL_HASH_TABLE_SIZE]),
          hashTableSizes { HASH_TABLE_SIZES } { }

	// Copy constructor
	HashTable(const HashTable& from)
		: rehashThreshold(0.5f),
	      hashTableSizesIndex(0),
		  hashTableSize(from.hashTableSize),
		  size(from.size),
		  table(new Bucket<K, V>[from.hashTableSize]),
          hashTableSizes { HASH_TABLE_SIZES } {
	    commonCopy(this, from);
	}

	// Move constructor
	HashTable(HashTable&& from) noexcept
		: rehashThreshold(0.5f),
          hashTableSizes { HASH_TABLE_SIZES } {
		hashTableSizesIndex = from.hashTableSizesIndex;
	    hashTableSize = from.hashTableSize;
	    size = from.size;
	    table = from.table;
	    from.table = nullptr;
	}

	// Assignment operator
	HashTable& operator=(const HashTable& from) {
	    commonDelete();
	    table = new Bucket<K, V>[from.hashTableSize];
	    commonCopy(this, from);
	    return *this;
	}

	// Move assignment operator
	HashTable& operator=(HashTable&& from) noexcept {

	    commonDelete();

	    hashTableSize = from.hashTableSize;
	    size = from.size;
	    table = from.table;

	    from.table = nullptr;

	    return *this;
	}

	// Destructor
	virtual ~HashTable() {
	    commonDelete();
	}

	V& get(const K& key) {

	    unsigned int index = selectBucket(key);
	    Bucket<K, V>* current = nullptr;

	    for (current = &table[index]; current != nullptr; current = current->next) {
	        if (*current->key == key) {
	            return *current->value;
	        }
	    }

        throw std::out_of_range("Tried to get entry that does not exist.");
	}

	// Will delete any element that is already there and insert new one
	void insert(const K& key, const V& value) {

	    unsigned int index = selectBucket(key);
	    unsigned int collisions = 0;
	    Bucket<K, V>* current = nullptr;
	    Bucket<K, V>* prev = nullptr;
	    bool inserted = false;

	    // Traverse the hash table list beginning to end
	    current = &table[index];
	    do {
	        if (current->key == nullptr) {
	            // If the current bucket is empty simply insert a new copy of the value
	            current->key = new K(key);
	            current->value = new V(value);
	            inserted = true;
	            size++;
	            break;
	        }
	        else if (*current->key == key) {
	            // Otherwise if the bucket is full and we have a matching key. Delete
	            // the value there and replace it with a copy of the new value.
	            delete current->key;
	            delete current->value;
	            current->key = new K(key);
	            current->value = new V(value);
	            inserted = true;
	            size++;
	            break;
	        } else {
	        	// We have a collision (handle this case below)
		    	collisions++;
	        }
	        prev = current;
	    	current = current->next;
	    } while (current != nullptr);

        // We have traversed the whole list but did not find a matching key, so insert
        // at the end of the list.
	    if (inserted == false) {

	    	float newLoadFactor = (size+1.0)/hashTableSize;

	        if (newLoadFactor < rehashThreshold) {
	            Bucket<K, V>* additionalBucket = new Bucket<K, V>;
	            additionalBucket->key = new K(key);
	            additionalBucket->value = new V(value);
	            prev->next = additionalBucket;
	            size++;
	        }
	        else {
	            rehash();
	            insert(key, value);
	        }
	    }
	}

	// FIXME: Is it better to return bool (success/failure) or void?
	V remove(const K& key) {

	    // Walk down the list from the front, searching for a matching key. When we find a match
	    // delete the data and update the list. Save temporary copy of the next pointer before
	    // traversing it so we can patch the list together properly.

        unsigned int index = selectBucket(key);
        Bucket<K, V>* current = nullptr;
        Bucket<K, V>* prev = nullptr;
        V retval;

        current = table[index];
        prev = table[index];

        while (current != nullptr) {

            // We found the value we were looking for
            if (current->key == key) {

                // Save a copy to return
                retval = current->value;

                // Delete the data
                delete current->key;
                delete current->value;

                // If we are not at the front of the list delete the Bucket too
                if (current != prev) {
                    Bucket<K, V>* temp = current;
                    prev->next = current->next;
                    delete temp;
                }
            }

            // Advance to next bucket in list
            prev = current;
            current = current->next;
        }

	    // Keep track of how many elements are stored
        size--;

        // Construct and return a copy of the element removed
        return retval;
	}

private:

	void commonCopy(HashTable& to, const HashTable& from) {

	    for (unsigned int i = 0; i < from.hashTableSize; i++) {

	        Bucket<K, V>* fromCurrent = from.table[i];

	        while (fromCurrent != nullptr) {

	            // If the bucket is full copy the data over
	            if (fromCurrent->key != nullptr) {

	                if (to.table[i]->key == nullptr) {
	                    // If the current bucket is empty simply copy the data
	                    to.table[i]->key = new K(fromCurrent->key);
	                    to.table[i]->value = new V(fromCurrent->value);
	                }
	                else {
	                    // Otherwise go to the end of the list, allocate and append another bucket
	                    // then fill the bucket.
	                    Bucket<K, V>* toCurrent = nullptr;
	                    for (toCurrent = to.table[i]; toCurrent->next != nullptr; toCurrent = toCurrent->next) {
	                        // Do nothing, simply advancing to the end of the list.
	                    }

	                    toCurrent->next = new Bucket<K, V>(from->key, from->value);
	                }
	            }
	            fromCurrent = fromCurrent->next;
	        }
	    }

	    to.size = from.size;
	}

	void commonDelete(void) {

	    for (unsigned int i = 0; i < hashTableSize; i++) {

	        Bucket<K, V>* temp = nullptr;
	        Bucket<K, V>* current = &table[i];

	        while (current != nullptr) {

	            temp = current->next;

	            if (current->key != nullptr) {

	            	// Delete the data inside the bucket
	            	delete current->key;
	            	delete current->value;

	            	// Then delete the bucket itself, unless it's the first bucket which must be
	            	// deleted using delete[]
	            	if (current != &table[i])
	            		delete current;
	            }

	            current = temp;
	        }
	    }

	    if (table != nullptr)
	        delete[] table;
	}

	/**
	 * Use the default hashing function, or the user-defined version.
	 */
	unsigned int selectBucket(const K& k) {
		return HashGenerator::chooseBucket(k) % hashTableSize;
	}

	void rehash(void) {

		unsigned int newSize = 0;

		// Calculate new larger hash table size
		if (hashTableSizesIndex+1 < NUMBER_OF_SIZES) {
			// If there is an existing prime number in our list left use that
			hashTableSizesIndex++;
			newSize = hashTableSizes[hashTableSizesIndex];
		}
		else {
			// Otherwise we are out of prime numbers, simply begin doubling hash table size
			newSize = 2 * hashTableSize;
		}

		// Allocate the larger hash table
		Bucket<K, V>* newTable = new Bucket<K, V>[newSize];

		// Iterate over all of the items in the current hash table and copy them to the new larger
		// hash table, using the new hash index
		for (unsigned int i = 0; i < hashTableSize; i++) {

			Bucket<K, V>* fromCurrent = &table[i];
			Bucket<K, V>* fromPrev = &table[i];
			Bucket<K, V>* temp = nullptr;

			// Iterate over all of the items in one linked list
			while (fromCurrent != nullptr) {

            	// Get the new index into the hash table
            	unsigned int newIndex = HashGenerator::chooseBucket(*fromCurrent->key) % newSize;

            	if (newTable[newIndex].key == nullptr) {

            		if (fromPrev == fromCurrent) {
                		// Case 1: Copying from the first bucket, to the first bucket
                		newTable[newIndex].key = fromCurrent->key;
                		newTable[newIndex].value = fromCurrent->value;
            		}
            		else {
            			// Case 2: Copying from 2nd+ item in list, to the first bucket

            			// Save pointer to bucket
            			temp = fromCurrent;

            			// Copy data
            			newTable[newIndex].key = fromCurrent->key;
            			newTable[newIndex].value = fromCurrent->value;

                		// Remove bucket from the "from" list
                		fromPrev->next = fromCurrent->next;

                		// Delete the unneeded bucket
                		delete temp;
            		}
            	}
            	else {

            		// Traverse to the end of the new list
            		Bucket<K, V>* toCurrent = &newTable[newIndex];
            		while (toCurrent->next != nullptr) {
            			toCurrent = toCurrent->next;
            		}

            		if (fromPrev == fromCurrent) {
                		// Case 3: Copying from the first bucket, to the 2nd+ item in the list
            			toCurrent->key = fromCurrent->key;
            			toCurrent->value = fromCurrent->value;
            		}
            		else {
            			// Case 4: Copying from the 2nd+ item in the list, to the 2nd+ item in the list

            			// Save a pointer to the bucket
            			temp = fromCurrent;

            			// Allocate and append a new bucket
            			toCurrent->next = new Bucket<K, V>();

            			// Copy the data over
            			toCurrent->key = fromCurrent->key;
            			toCurrent->value = fromCurrent->value;

            			// Remove bucket from the "from" list
            			fromPrev->next = fromCurrent->next;

            			// Delete the unneeded bucket
            			delete temp;
            		}
            	}

				// Update the current and next pointers for the next loop iteration
				fromPrev = fromCurrent;
				fromCurrent = fromCurrent->next;
			}
		}

		// Now that we have copied all of our data over to the new hash table,
		// cleanup the old table, and set the new size.
		hashTableSize = newSize;
		Bucket<K, V>* temp = table;
		table = newTable;
		delete temp;

	}


	const float rehashThreshold;
	unsigned int hashTableSizesIndex;
	unsigned int hashTableSize;
	unsigned int size;
	Bucket<K, V>* table;
	const int hashTableSizes[NUMBER_OF_SIZES];


	// collisions

	// Mathematically speaking, at what point is it cheaper to re-key/index
	// the entire list in order to avoid collisions, compared to the cost of
	// another operation at the collision? (It seems like fixing the hash table
	// might always be more expensive, so maybe you have to think about what
	// you're trying to optimize for? Average operation?
};



} /* namespace homebrew */
} /* namespace mjl */

#endif /* HASHTABLE_H */
