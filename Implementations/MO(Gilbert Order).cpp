#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <climits>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;
using namespace chrono;

#ifdef DEBUG
	//#define LOCAL_INPUT_FILE
#else
	//#define USE_FILE_IO
#endif

#ifdef USE_FILE_IO
	#define INPUT_FILE "input.txt"
	#define OUTPUT_FILE "output.txt"
	#define cin ____cin
	#define cout ____cout
	ifstream cin(INPUT_FILE);
	ofstream cout(OUTPUT_FILE);
#else
	#ifdef LOCAL_INPUT_FILE
		#define cin ____cin
		ifstream cin("input.txt");
	#endif
#endif

const int infinity = (int)1e9 + 42;
const int64_t llInfinity = (int64_t)1e18 + 256;
const int module = (int)1e9 + 7; 
const long double eps = 1e-8;

mt19937_64 randGen(system_clock().now().time_since_epoch().count());

inline void raiseError(string errorCode) {
	cerr << "Error : " << errorCode << endl;
	exit(42);
}

inline int64_t gilbertOrder(int x, int y, int pow, int rotate) {
	if (pow == 0) {
		return 0;
	}
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2*pow - 2);
	int64_t ans = seg * subSquareSize;
	int64_t add = gilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}

struct Query {
	int l, r, idx;
	int64_t ord;
	
	inline void calcOrder() {
		ord = gilbertOrder(l, r, 21, 0);
	}
};

inline bool operator<(const Query &a, const Query &b) {
	return a.ord < b.ord;
}

signed main() {
	#ifndef USE_FILE_IO
		ios_base::sync_with_stdio(false);
	#endif
	
	mt19937 rnd(42);
	
	int n, m, k; cin >> n >> m; k = rnd() % 1048576;
	vector<int> p(n+1);
	for (int i = 0; i < n; i++) {
		int val = rnd() % 1048576;
		p[i+1] = p[i] ^ val;
	}
	
	vector<Query> qry(m);
	for (int i = 0; i < m; i++) {
		int l = rnd() % n + 1, r = rnd() % n + 1;
		if (l > r) {
			swap(l, r);
		}
		qry[i].l = l; qry[i].r = r;
		qry[i].idx = i;
		qry[i].calcOrder();
	}
	
	int64_t ans = 0;
	vector<int64_t> res(m);
	vector<int64_t> cnt((int)2e6, 0);
	sort(qry.begin(), qry.end());
	int l = 0, r = 1;
	ans = (p[1] == k);
	cnt[p[0]]++; cnt[p[1]]++;
	
	for (Query q: qry) {
		q.l--;
		while (l > q.l) {
			l--;
			ans += cnt[p[l] ^ k];
			cnt[p[l]]++;
		}
		while (r < q.r) {
			r++;
			ans += cnt[p[r] ^ k];
			cnt[p[r]]++;
		}
		while (l < q.l) {
			cnt[p[l]]--;
			ans -= cnt[p[l] ^ k];
			l++;
		}
		while (r > q.r) {
			cnt[p[r]]--;
			ans -= cnt[p[r] ^ k];
			r--;
		}
		res[q.idx] = ans;
	}
	
	uint64_t rhsh = 0;
	for (int i = 0; i < m; i++) {
		rhsh *= (uint64_t)1e9 + 7;
		rhsh += (uint64_t)res[i];
	}
	cout << rhsh << "\n";
	
	return 0;
}
