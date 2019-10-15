#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#endif

typedef long long ll;
typedef pair<int, int> pii;

#define x first
#define y second

const int N = 1e4 + 10;

int n;
vector<int> a, d;
vector<vector<int>> dir = {{+1, +1}, {-1, +1}, {-1, -1}, {+1, -1}};
vector<int> ans[2];

vector<int> solve(vector<int> a, vector<int> signs) {
	sort(a.begin(), a.end());
	int n = a.size();
	int h = 0;
	for (int i = 0; i < n;) {
		int r = i, curr_sign = signs[i];
		while (r < n && signs[r] == curr_sign) r++;
	}
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n;
	a.resize(2 * n);
	d.resize(n);
	for (int i = 0; i < 2 * n; i++) scanf("%d", &a[i]);
	for (int i = 0; i < n; i++) scanf("%d", &d[i]);

	for (int i = 0; i < 2; i++) {
		vector<int> _a = vector<int>(a.begin() + n * i, ans.begin() + n * (i + 1));
		vector<int> _d(n);
		for (int j = 0; j < n; j++) _d[j] = dir[d[j] - 1][i];
		ans[i] = solve(_a, _d);
	}

	for (int i = 0; i < n; i++) {
		printf("%c%d %c%d\n",
				ans[0][i] > 0 ? '+' : '-', ans[0][i],
				ans[1][i] > 0 ? '+' : '-', ans[1][i]
			);
	}

	return 0;
}