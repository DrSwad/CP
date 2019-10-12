#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct BIT {
	vector<T> tree;
	
	void upd(int i, T v) {
		++i;
		while (i < (int) tree.size()) {
			tree[i] += v;
			i += i & -i;
		}
	}

	BIT(const vector<T> &a) {
		tree.resize(a.size() + 1, 0);
		for (int i = 0; i < (int) a.size(); i++) {
			upd(i, a[i]);
		}
	}

	BIT(T *a, int n) {
		tree.resize(n + 1, 0);
		for (int i = 0; i < n; i++) {
			upd(i, a[i]);
		}
	}

	T prefSum(int i) {
		++i;
		T ret = 0;
		while (i > 0) {
			ret += tree[i];
			i -= i & -i;
		}
		return ret;
	}

	T rangeSum(int l, int r) {
		return prefSum(r) - prefSum(l - 1);
	}

	T pos(int i) {
		return rangeSum(i, i);
	}

	void change(int i, int v) {
		upd(i, v - pos(i));
	}
};

int main() {
	vector<int> v(5);
	v = {1, 3, 2, 3, 4};

	BIT<int> bit(v);

	cerr << bit.rangeSum(0, 4) << endl;

	cerr << bit.pos(3) << endl;

	bit.change(0, 3);
	cerr << bit.rangeSum(0, 4) << endl;

	return 0;
}