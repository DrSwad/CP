/*
	Li Chao Tree Template
	Can be used to solve CHT problems
	Adding line (y = mx + c) : O(logn)
	Query : O(logn)

	To find minima, use f1(x) < f2(x), min in update & query.
	To find maxima, use f1(x) > f2(x), max in update & query.
	The line of tree[node] in range [lo, hi] represents
	that this line gives the best result for point [x, y] range,
	where x <= mid <= y. Here, mid = (lo + hi) / 2.
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 5;
const ll inf = 1e12 + 5;

ll h[N];
struct Line {
	ll m, c;
	Line(ll m = 0, ll c = 0) : m(m), c(c) {};
	ll f(ll x) {
		return h[m] * x - m * h[x] + c;
	}
};

Line lcTree[4 * N];

void insert(int tI, int vL, int vR, Line line) {
	if (vL == vR){
		if (lcTree[tI].f(vL) < line.f(vL)) lcTree[tI] = line;
		return;
	}

	int vM = vL + vR >> 1, tL = tI << 1, tR = tL | 1;
	bool fL = line.f(vL) > lcTree[tI].f(vL);
	bool fM = line.f(vM) > lcTree[tI].f(vM);

	if (fM) swap(lcTree[tI], line);

	if (fL != fM) insert(tL, vL, vM, line);
	else insert(tR, vM + 1, vR, line);
}

ll query(int tI, int vL, int vR, int vQ) {
	if (vL == vR) return lcTree[tI].f(vQ);

	int vM = vL + vR >> 1, tL = tI << 1, tR = tL | 1;
	ll ret = lcTree[tI].f(vQ);

	if (vQ <= vM) return max(ret, query(tL, vL, vM, vQ));
	else return max(ret, query(tR, vM + 1, vR, vQ));

	return ret;
}