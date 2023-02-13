#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
#define x first
#define y second

#ifdef LOCAL
#include "/Users/swad/Desktop/CP/debug.h"
#endif

const int N = 1e5 + 5;
// const int MOD = int(1e9) + 7;

bool go(vector<long long>& a, int p) {
	p--;
    int n = a.size();
    vector<long long> _a = a;
    for (int i = 0; i < n; i++) {
        a[i] = (_a[(i - 1 + n) % n] + 1) / 2 + _a[(i + 1) % n] / 2;
        if (i == (p + 1) % n) a[i] += _a[(i - 1 + n) % n] / 2;
        if (i == (p - 1 + n) % n) a[i] -= _a[(i + 1) % n] / 2;
    }
    return a == _a;
}

int main() {
	int n = 4;
	int k = 2;
	int p = 2;
	int times = 5;
	int term = 3;

	vector<long long> a(n, k);

	while (times--) go(a, p);

	printf("%lld\n", a[term - 1]);

    return 0;
}