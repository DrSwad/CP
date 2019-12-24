#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned int uint;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "debug.h"
#endif

const int N = 205;

int n;
pii x[N], y[N];
map<pii, int> slope_cnt;

int gcd(int a, int b) {
	if (a < b) swap(a, b);
	while (b != 0) {
		int _a = a;
		a = b;
		b = _a % b;
	}
	return a;
}

int trapezoids() {

}

int parallelograms() {

}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int t;
	cin >> t;

	for (int cs = 1; cs <= t; cs++) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d %d", &x[i], &y[i]);

		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				int dx = abs(x[i] - x[j]);
				int dy = abs(y[i] - y[j]);
				int dg = gcd(dx, dy);
				slope_cnt[make_pair(dx / dg, dy / dg)]++;
			}
		}

		printf("Case %d: %d\n", cs, trapezoids() - 2 * parallelograms);
	}

	return 0;
}