#include <bits/stdc++.h>

using namespace std;

int main() {
	// Iterate over all subsets of mask excluding null subset
	int mask = (1 << 10);
	for (int i = mask; i > 0; i = (i - 1) & mask) {
		// do stuff
	}

	cout << "Number of set bits in binary represention of 6: " <<
		__builtin_popcount(6)
		<< endl;

	return 0;
}