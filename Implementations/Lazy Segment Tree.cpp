#include <bits/stdc++.h>

using namespace std;

template <typename T>
class LazyST {
private:
	int n;
	vector<T> a;
	vector<T> st, lz;
	T lz_default;
	T (*st_merge)(T, T);
	T (*lz_merge)(T, T);

	void build(int stI, int L, int R) {
		if (L == R) {
			st[stI] = a[L - 1];
			return;
		}

		int mid = (L + R) >> 1;
		build(stI << 1, L, mid);
		build(stI << 1 | 1, mid + 1, R);

		st[stI] = st_merge(st[stI << 1], st[stI << 1 | 1]);
	}

	void update(int stI, int L, int R, int l, int r, T val) {
		if (l <= L && R <= r) lz[stI] = lz_merge(lz[stI], val);
		else {
			int mid = (L + R) >> 1;
			if (l <= mid) update(stI << 1, L, mid, l, min(r, mid), val);
			if (mid + 1 <= r) update(stI << 1 | 1, mid + 1, R, max(l, mid + 1), r, val);
		}


		if (L == R) st[stI] = lz_merge(a[L - 1], lz[stI]);
		else st[stI] = lz_merge(st_merge(st[stI << 1], st[stI << 1 | 1]), lz[stI]);
	}

	T query(int stI, int L, int R, int l, int r) {
		if (l <= L && R <= r) return st[stI];

		int mid = (L + R) >> 1;
		if (r <= mid) return lz_merge(query(stI << 1, L, mid, l, r), lz[stI]);
		else if (mid + 1 <= l) return lz_merge(query(stI << 1 | 1, mid + 1, R, l, r), lz[stI]);
		else return st_merge(
				lz_merge(query(stI << 1, L, mid, l, mid), lz[stI]),
				lz_merge(query(stI << 1 | 1, mid + 1, R, mid + 1, r), lz[stI])
			);
	}

public:
	LazyST(vector<T> a, T (*st_merge)(T, T), T (*lz_merge)(T, T), T lz_default, bool build_init) {
		n = a.size();
		this->a = a;
		st.resize(4 * n + 1);
		lz.resize(4 * n + 1, lz_default);
		this->lz_default = lz_default;
		this->st_merge = st_merge;
		this->lz_merge = lz_merge;
		if (build_init) build(1, 1, n);
	}
	T query(int l, int r) { // range [l, r], 1-based index
		return query(1, 1, n, l, r);
	}
	void update(int l, int r, T val) { // range [l, r], 1-based index
		update(1, 1, n, l, r, val);
	}
};

int main() {
	LazyST<int> lzst = LazyST<int>({1, 2, 3},
		[](int i, int j) {return i + j;}, // queries sum of the numbers in the range
		[](int i, int j) {return i * j;}, // multiplies range by a number in updates
		1, // default value of lazy should be 1
		true); // needs to build the tree on initialization, since provided vector has non-default values

	cout << lzst.query(2, 3) << endl;
	lzst.update(1, 2, 4);
	cout << lzst.query(1, 3) << endl;

	return 0;
}