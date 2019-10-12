#include<bits/stdc++.h>

using namespace std;

static random_device rd;
static mt19937 rng(rd());

int main() {
	int a = 1, b = 1000;
	uniform_int_distribution<int> uid(a, b);
	cout << uid(rng) << endl;

	vector<int> v(10);
	iota(v.begin(), v.end(), 1);
	shuffle(v.begin(), v.end(), rng);
	for (int i : v) cout << i << " "; cout << endl;

	return 0;
}
