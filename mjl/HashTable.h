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
#ifndef HASHTABLE_H_
#define HASHTABLE_H_

namespace mjl {
namespace homebrew {

class HashTable {
public:
	HashTable();
	//T& operator[]( const T& key );
	virtual ~HashTable();


	// insert value indexed by key
	// lookup the value indexed by key
	// remove the value indexed by key

	// colisions

	// Mathematically speaking, at what point is it cheaper to re-key/index
	// the entire list in order to avoid colissions, compared to the cost of
	// another operation at the colission? (It seems like fixing the hash table
	// might always be more expensive, so maybe you have to think about what
	// you're trying to optimize for? Average operation?
};

} /* namespace homebrew */
} /* namespace mjl */

#endif /* HASHTABLE_H_ */
