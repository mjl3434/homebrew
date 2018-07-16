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

template <typename K, typename V> struct Bucket {
public:
	Bucket(void) : key(nullptr), value(nullptr), next(nullptr) { }
	K* key;
	V* value;
	struct Bucket<K, V>* next;
};

// This is a generic implementation of a hash function
template <typename KK> class DefaultHashGenerator
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
	static unsigned int chooseBucket(const KK& k)
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

	    // FIXME: Copy data over from each bucket.
	}

	// Move constructor
	HashTable(HashTable&& from) noexcept {

	}

	// Assignment operator
	HashTable& operator=(const HashTable& from) {

	}

	// Move assignment operator
	HashTable& operator=(HashTable&& from) noexcept {

	}

	// Destructor
	virtual ~HashTable();

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
	            current->value = new V(value);
	            inserted = true;
	            break;
	        }
	        else if (current->key == key) {
	            // Otherwise if the bucket is full and we have a matching key. Delete
	            // the value there and replace it with a copy of the new value.
	            delete current->value;
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
	}

	V& remove(const K& key) {

	    // FIXME: Implement this:

	    /*
        unsigned int index = selectBucket(key);
        Bucket<K, V>* current = nullptr;

        for (current = table[index]; current != nullptr; current = current->next) {
            if (current->key == key) {
                return current->value;
            }
        }
        *?
	}

private:

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
