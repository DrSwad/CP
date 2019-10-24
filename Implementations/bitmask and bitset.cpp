#include <bits/stdc++.h>

using namespace std;

int main() {

	/*
		Bitmask
	*/

	// Iterate over all subsets of mask excluding null subset
	int mask = (1 << 10);
	for (int i = mask; i > 0; i = (i - 1) & mask) {
		// do stuff
	}

	// Iterate over all subsets of mask including null subset
	int i = mask;
	do {
		// do stuff

		i = (i - 1) & mask;
	} while (i != mask);

	// Number of set bits in binary represention of n: __builtin_popcount(n)

	// Number of trailing 0 bits in binary represention of n: __builtin_ctz(n)

	// Number of leading 0 bits in binary represention of n: __builtin_clz(n)

	// Toggle lsb of positive n: n & (n - 1)

	// Isolate lsb of n: n & -n

	// Next higher number with same number of set bits
	auto snoob = [](int x) {
		int y = x & -x, z = x + y;
		return z | ((x ^ z) >> 2) / y;
	};

	/*
		Bitset
	*/

	/*
		Useful notes:
		- Bitset optimizes the space such that each bool takes 1 bit space only
		- The size of bitset is fixed at compile time that is, it can’t be
		  changed at runtime.
		- Remember bitset starts its indexing backward that is for 10110, 0 are
		  at 0th and 3rd indices whereas 1 are at 1st 2nd and 4th indices.
		-
	*/

	const int M = 10;
	bitset<M> bset; // Default constructor initializes with all bits 0
	bset = bitset<M>(20); // Initialized with bits of 20
	bset = bitset<M>("1100"); // Initialized with binary representation of 12

	// string constructor using custom zero/one digits
	string alpha_bit_string = "aBaaBBaB";
	bset = bitset<M>(alpha_bit_string, 0, alpha_bit_string.size(),  'a', 'B'); // [0,1,0,0,1,1,0,1]
	bset = bitset<M>("aBaaBBaB", 8,  'a', 'B'); // [0,1,0,0,1,1,0,1]

	bset[1] = 1; // Setting lsb(the one with coefficient 2^1)
	bset.count(); // Number of set bits in bitset
	bset.size(); // Total number of bits in bitset
	bset.size() - bset.count(); // Number of unset bits in bitset
	bset.test(1); // Returns 1 if bit is set else returns 0
	bset.any(); // Returns true, if atleast 1 bit is set
	bset.none(); // Returns true, if none of the bits is set
	bset.all(); // Returns true, if all of the bits are set
	bset.set(); // Sets all bits
	bset.set(4); // Sets bit 4
	bset.set(4, 0); // Alternative for bset[4] = 0
	bset.reset(); // Unsets all bits
	bset.reset(4); // Unsets bit 4
	bset.flip(); // Flips all bits
	bset.flip(4); // Flips bit 4
	cout << bset << endl;

	// All bitwise operators are overloaded
	// But when doing operations on two bitsets, there sizes need to be same
	bitset<M> bset2(bset);
	(bset == bset2);
	(bset != bset2);
	(bset ^= bset2);
	(bset &= bset2);
	(bset |= bset2);
	(bset == 6);
	(bset != 6);
	(bset ^= 6);
	(bset &= 6);
	(bset |= 6);
	(bset <<= 6);
	(bset >>= 6);
	(~bset);

	bset.to_string(); // Converts the contents of the bitset to a string
	bset.to_string('O', 'X'); // Use 'O' for 0 and 'X' for 1
	bset.to_ulong(); // Converts the contents of the bitset to an unsigned long integer
	bset.to_ullong(); // Converts the contents of the bitset to an unsigned long long integer

	return 0;
}