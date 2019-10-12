#include <bits/stdc++.h>

using namespace std;

const int N = 20;

int A[1 << N], F[1 << N];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	for (int mask = 0; mask < (1 << N); mask++)
		F[mask] = A[mask];

	for (int i = 0; i < N; i++)
		for (int mask = 0; mask < (1 << N); mask++)
			if (mask & 1 << i)
				F[mask] += F[mask ^ 1 << i];

	return 0;
}