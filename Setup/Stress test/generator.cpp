#include <bits/stdc++.h>
using namespace std;
#define debug(a) cout << #a << ": " << (a) << "\n"

typedef long long ll;
typedef pair<int, int> pii;

#define x first
#define y second

static random_device rd;
static mt19937 rng(rd());

int random(int a, int b) {
	if (a > b) swap(a, b);
	return a + abs((int)rng()) % (b - a + 1);
}

int N = int(100), M = int(100), A = int(20), K = int(8);

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	srand((unsigned)time(0));

	cout << fixed;

	int n = random(N, N), m = random(M, M);

	cout << n << " " << m << endl;

	for (int i = 1; i <= n; i++) printf("%d ", random(1, A)); puts("");
	for (int i = 1; i <= m; i++) {
		int type = random(1, 2);
		if (type == 1) {
			int l = random(1, n), r = random(l, n), k = random(1, K);
			printf("%d %d %d %d\n", type, l, r, k);
		} else {
			int p = random(1, n), x = random(1, A);
			printf("%d %d %d\n", type, p, x);
		}
	}

	return 0;
}