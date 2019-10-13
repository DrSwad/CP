template <typename T>
class segmentTree {
	int n;
	vector<T> a;
	vector<T> st;
	T (*merge)(T, T);
	void build(int stI, int L, int R) {
		if (L == R) {
			st[stI] = a[L];
			return;
		}

		int mid = (L + R) / 2;
		build((stI << 1), L, mid);
		build((stI << 1) + 1, mid + 1, R);

		st[stI] = merge(st[(stI << 1)], st[(stI << 1) + 1]);
	}
	void update(int stI, int L, int R, int at, T val) {
		if (L == R) {
			st[stI] = val;
			return;
		}

		int mid = (L + R) / 2;
		if (at <= mid) update((stI << 1), L, mid, at, val);
		else update((stI << 1) + 1, mid + 1, R, at, val);

		st[stI] = merge(st[(stI << 1)], st[(stI << 1) + 1]);
	}
	T query(int stI, int L, int R, int l, int r) {
		if (l <= L && R <= r) return st[stI];

		int mid = (L + R) / 2;
		if (r <= mid) return query((stI << 1), L, mid, l, r);
		if (mid + 1 <= l) return query((stI << 1) + 1, mid + 1, R, l, r);

		return merge(
				query((stI << 1), L, mid, l, mid),
				query((stI << 1) + 1, mid + 1, R, mid + 1, r)
			);
	}
public:
	segmentTree(vector<T> _a, T (*_merge)(T, T)) {
		n = _a.size();
		a = _a;
		st.resize(4 * n + 1);
		merge = _merge;
		build(1, 0, n - 1);
	}
	T query(int l, int r) { // range [l, r], 0-based index
		return query(1, 0, n - 1, l, r);
	}
	void update(int at, T val) { // at is 0-based index
		update(1, 0, n - 1, at, val);
	}
};