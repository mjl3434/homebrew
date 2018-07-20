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

#include <exception>

namespace mjl {
namespace homebrew {

class KeyNotPresent : public exception
{
    const char* what() const throw () {
        return "Key not present";
    }
}

template <typename K1, typename VV> struct Bucket {
public:
	Bucket(void) : key(nullptr), value(nullptr), next(nullptr) { }
	K1* key;
	VV* value;
	struct Bucket<K1, VV>* next;
};

// This is a generic implementation of a hash function
template <typename K2> class DefaultHashGenerator
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
	static unsigned int chooseBucket(const K2& k)
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


template <typename K, typename V, typename HashGenerator = DefaultHashGenerator<K>> class HashTable {
public:

	// Default constructor
	HashTable() : hashTableSize(initialHashTableSize), size(0), table(new Bucket<K, V>[initialHashTableSize]) { }

	// Copy constructor
	HashTable(const HashTable& from)
	    : hashTableSize(from.hashTableSize), size(from.size), table(new Bucket<K, V>[from.hashTableSize]) {

	    commonCopy(this, from);
	}

	// Move constructor
	HashTable(HashTable&& from) noexcept {

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

	    for (current = table[index]; current != nullptr; current = current->next) {
	        if (current->key == key) {
	            return current->value;
	        }
	    }

	    if (current == nullptr) {
	        throw new KeyNotPresent();
	    }
	}

	// Will delete any element that is already there and insert new one
	void insert(const K& key, const V& value) {

	    unsigned int index = selectBucket(key);
	    unsigned int collisions = 0;
	    Bucket<K, V>* current = nullptr;
	    bool inserted = false;

	    // Traverse the hash table list beginning to end
	    for (current = table[index]; current->next != nullptr; current = current->next, collisions++) {

	        if (current->key == nullptr) {
	            // If the current bucket is empty simply insert a new copy of the value
	            current->key = new K(key);
	            current->value = new V(value);
	            inserted = true;
	            break;
	        }
	        else if (current->key == key) {
	            // Otherwise if the bucket is full and we have a matching key. Delete
	            // the value there and replace it with a copy of the new value.
	            delete current->key;
	            delete current->value;
	            current->key = new K(key);
	            current->value = new V(value);
	            inserted = true;
	            break;
	        }
	    }

        // We have traversed the whole list but did not find a matching key, so insert
        // at the end of the list.
	    if (inserted == false) {

	        //if (collisions < collisionResizeThreshold) {
	        if (true) {
	            Bucket<K, V>* additionalBucket = new Bucket<K, V>;
	            additionalBucket->key = new K(key);
	            additionalBucket->value = new V(value);
	            current->next = additionalBucket;
	        }
	        else {
	            rehash();
	            insert(key, value);
	        }
	    }

	    // Keep track of how many elements are stored
	    size++;
	}

	// FIXME: Is it better to return bool (success/failure) or void?
	V& remove(const K& key) {

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

	                    // FIXME: Is it better to implement a Bucket constructor?
	                    toCurrent->next = new Bucket<K, V>();
	                    toCurrent->next->key = new K(fromCurrent->key);
	                    toCurrent->next->value = new V(fromCurrent->value);
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
	        Bucket<K, V>* current = table[i];

	        while (current != nullptr) {

	            temp = current->next;

	            // Delete the data inside the bucket
	            delete current->key;
	            delete current->value;

	            // Then delete the bucket itself, unless it's the first bucket which must be
	            // deleted using delete[]
	            if (current != table[i])
	                delete current;

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

	}

	static const unsigned int initialHashTableSize = 32;
	static const unsigned int collisionResizeThreshold = 3;
	unsigned int hashTableSize;
	unsigned int size;
	Bucket<K, V>* table;

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
