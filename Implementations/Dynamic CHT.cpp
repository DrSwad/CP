#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "debug.h"
#endif

struct CHT {
private:
	vector<pii> lines;
public:
	CHT() {}
	void addLine(pii line) {
		lines.push_back(line);
	}
	void build() {
		sort(lines.begin(), lines.end());
		vector<pii> _lines = lines;
		lines.clear();
		for (pii line : _lines) insert(line);
	}
	ll query(int x) {
		if (lines.empty()) return LLONG_MIN;

		int L = 0, R = lines.size() - 1;
		while (L != R) {
			int mid1 = L + (R - L) / 3;
			int mid2 = R - (R - L) / 3;
			if (lines[mid1].x * 1LL * x + lines[mid1].y
				>= lines[mid2].x * 1LL * x + lines[mid2].y) R = mid2 - 1;
			else L = mid1 + 1;
		}
		return lines[L].x * 1LL * x + lines[L].y;
	}
private:
	bool bad(pii line1, pii line2, pii line3) {
		return (line3.y - line1.y) * 1LL * (line1.x - line2.x)
			   <= (line2.y - line1.y) * 1LL * (line1.x - line3.x);
	}
	void insert(pii line) {
		while (lines.size() > 0 && lines.back().x == line.x) lines.pop_back();
		lines.push_back(line);
		int sz = lines.size();
		while (sz >= 3 && bad(lines[sz - 3], lines[sz - 2], lines[sz - 1])) {
			lines.erase(lines.end() - 2);
			sz--;
		}
	}
};

const int N = int(3e5) + 10;

int n;
map<int, pii> line_at_query;
vector<pii> queries;

CHT st[4 * N];
void build(int stI, int L, int R) {
	st[stI].build();

	if (L == R) return;

	int mid = (L + R) / 2;
	build((stI << 1), L, mid);
	build((stI << 1) + 1, mid + 1, R);
}
void build() {
	build(1, 1, n);
}
void insert(int stI, int L, int R, int l, int r, pii val) {
	if (r < L || R < l) return;
	if (l <= L && R <= r) {
		st[stI].addLine(val);
		return;
	}

	int mid = (L + R) / 2;
	insert((stI << 1), L, mid, l, r, val);
	insert((stI << 1) + 1, mid + 1, R, l, r, val);
}
void insert(int l, int r, pii val) {
	insert(1, 1, n, l, r, val);
}
ll query(int stI, int L, int R, int at, int x) {
	if (at < L || R < at) return LLONG_MIN;
	if (L == R) return st[stI].query(x);

	ll ret = st[stI].query(x);
	int mid = (L + R) / 2;
	ret = max(ret, query((stI << 1), L, mid, at, x));
	ret = max(ret, query((stI << 1) + 1, mid + 1, R, at, x));
	return ret;
}
ll query(int at, int x) {
	return query(1, 1, n, at, x);
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int t;
		scanf("%d", &t);

		if (t == 1) { // Add line
			int a, b;
			scanf("%d %d", &a, &b);
			line_at_query[i] = make_pair(a, b);
		}
		else if (t == 2) { // Remove line
			int _i;
			scanf("%d", &_i);
			insert(_i, i, line_at_query[_i]);
			line_at_query.erase(_i);
		}
		else if (t == 3) { // Query
			int q;
			scanf("%d", &q);
			queries.push_back(make_pair(i, q));
		}
	}

	for (auto item : line_at_query) {
		insert(item.x, n, item.y);
	}

	build();

	for (pii p : queries) {
		ll ans = query(p.x, p.y);
		if (ans == LLONG_MIN) puts("EMPTY SET");
		else printf("%lld\n", ans);
	}

	return 0;
}