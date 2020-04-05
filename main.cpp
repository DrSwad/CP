#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "/Users/swad/Desktop/CP/debug.h"
#endif

// const int N = 5;

vector<vector<int>> brute_ans[6][21];

void go(vector<vector<int>> &v, int at, int n) {
	if (at == n) {
		int sum = 0;
		for (int i = 0; i < n; i++) sum += v[i][i];
		brute_ans[n][sum] = v;

		return;
	}

	iota(v[at].begin(), v[at].end(), 0);
	do {
		bool flag = false;
		for (int i = 0; i < at && !flag; i++)
			for (int j = 0; j < n && !flag; j++)
				if (v[at][j] == v[i][j]) flag = true;
		if (!flag) go(v, at + 1, n);
	} while (next_permutation(v[at].begin(), v[at].end()));
}

void brute() {
	for (int n = 2; n <= 5; n++) {
		vector<vector<int>> v(n, vector<int>(n));
		go(v, 0, n);
	}
}

vector<vector<int>> construct(int a, int b) {
	return {};
}
vector<vector<int>> construct(int a, int b, int c) {
	return {};
}

vector<vector<int>> solve(int n, int k) {
	k -= n;

	if (n <= 5) return brute_ans[n][k];

	if (k == 1 || k == n * (n - 1) - 1) return {};

	if (k % n == 0) {
		vector<vector<int>> v(n, vector<int>(n));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				v[i][j] = (i - j + n) % n;
		int r = k / n;
		for (int i = 0; i < n; i++)
			swap(v[i][i], v[i][(i - r + n) % n]);
		return v;
	}

	int q = min(n - 1, k / (n - 2));
	int r = k - q * (n - 2);
	if (r < 2) q--, r += n - 2;

	int r1 = min(n - 1, r), r2 = r - r1;
	if (r1 == q || r2 == q) r1--, r2++;

	if (r1 == r2) return construct(q, r1);
	else return construct(q, r1, r2);
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	brute();

	int t;
	cin >> t;

	for (int cs = 1; cs <= t; cs++) {
		int n, k;
		scanf("%d %d", &n, &k);

		vector<vector<int>> ans = solve(n, k);

		printf("Case #%d: ", cs);
		if (ans.empty()) puts("IMPOSSIBLE");
		else {
			puts("POSSIBLE");

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (j > 0) printf(" ");
					printf("%d", ans[i][j] + 1);
				}
				puts("");
			}
		}
	}

	return 0;
}