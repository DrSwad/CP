template <typename T>
class segmentTree {
	vector<int> dims;
	vector<int> rest_dims;
	int tot_dims = 0;
	int curr_dim = 0;
	int rest_dim = 0;

	vector<T> a;
	vector<segmentTree<T>> st;
	vector<T> ans;
	T (*merge)(T, T);

	void mergeSegmentTrees(segmentTree &st1, segmentTree &st2) {
		dims = st1.dims;
		rest_dims = st1.rest_dims;
		tot_dims = st1.tot_dims;
		curr_dim = st1.curr_dim;
		rest_dim = st1.rest_dim;
		merge = st1.merge;

		if (tot_dims == 1) {
			ans.resize(st1.ans.size());
			for (int i = 0; i < ans.size(); i++) {
				ans[i] = merge(st1.ans[i], st2.ans[i]);
			}
		}
		else {
			st.resize(st1.st.size());
			for (int i = 0; i < st.size(); i++) {
				st[i].mergeSegmentTrees(st1.st[i], st2.st[i]);
			}
		}
	}

	void build(int stI, int L, int R) {
		if (L == R) {
			if (tot_dims == 1) ans[stI] = a[L];
			else {
				vector<T> _a(a.begin() + L * rest_dim, a.begin() + (L + 1) * rest_dim);
				st[stI] = segmentTree(rest_dims, _a, merge);
			}
			return;
		}

		int mid = (L + R) / 2;
		build((stI << 1), L, mid);
		build((stI << 1) + 1, mid + 1, R);

		if (tot_dims == 1) {
			ans[stI] = merge(ans[(stI << 1)], ans[(stI << 1) + 1]);
		}
		else {
			st[stI].mergeSegmentTrees(st[(stI << 1)], st[(stI << 1) + 1]);
		}
	}

	void mergeSegmentTrees(segmentTree &st1, segmentTree &st2, vector<int> &at) {
		int stI = 1, L = 0, R = curr_dim - 1;
		int curr_at = at[0];
		vector<int> rest_at(at.begin() + 1, at.end());

		while (true) {
			if (tot_dims == 1) {
				ans[stI] = merge(ans[(stI << 1)], ans[(stI << 1) + 1]);
			}
			else {
				st[stI].mergeSegmentTrees(st1.st[stI], st2.st[stI], rest_at);
			}

			if (L == R) break;

			int mid = (L + R) / 2;
			if (curr_at <= mid) {
				R = mid;
				stI = (stI << 1);
			}
			else {
				L = mid + 1;
				stI = (stI << 1) + 1;
			}
		}
	}

	void update(int stI, int L, int R, vector<int> &at, T val) {
		if (L == R) {
			if (tot_dims == 1) {
				ans[stI] = val;
			}
			else {
				vector<int> _at(at.begin() + 1, at.end());
				st[stI].update(_at, val);
			}
			return;
		}

		int mid = (L + R) / 2;
		if (at[0] <= mid) update((stI << 1), L, mid, at, val);
		else update((stI << 1) + 1, mid + 1, R, at, val);

		if (tot_dims == 1) ans[stI] = merge(ans[(stI << 1)], ans[(stI << 1) + 1]);
		else {
			vector<int> _at(at.begin() + 1, at.end());
			st[stI].mergeSegmentTrees(st[(stI << 1)], st[(stI << 1) + 1], _at);
		}
	}
	T query(int stI, int L, int R, vector<pii> &at) {
		if (at[0].x <= L && R <= at[0].y) {
			if (tot_dims == 1) return ans[stI];
			else {
				vector<pii> _at(at.begin() + 1, at.end());
				return st[stI].query(_at);
			}
		}

		int mid = (L + R) / 2;
		if (at[0].y <= mid) return query((stI << 1), L, mid, at);
		if (mid + 1 <= at[0].x) return query((stI << 1) + 1, mid + 1, R, at);

		return merge(
				query((stI << 1), L, mid, at),
				query((stI << 1) + 1, mid + 1, R, at)
			);
	}
public:
	segmentTree() {}
	segmentTree(vector<int> _dims, vector<T> &_a, T (*_merge)(T, T)) {
		dims = _dims;
		rest_dims = vector<int>(_dims.begin() + 1, _dims.end());
		tot_dims = _dims.size();
		curr_dim = _dims[0];
		rest_dim = 1;
		for (int i = 1; i < _dims.size(); i++) rest_dim *= _dims[i];

		a = _a;
		if (tot_dims == 1) ans.resize(4 * curr_dim + 1);
		else st.resize(4 * curr_dim + 1);
		merge = _merge;
		build(1, 0, curr_dim - 1);
	}
	T query(vector<pii> &at) { // vector of ranges [l, r], 0-based index
		return query(1, 0, curr_dim - 1, at);
	}
	void update(vector<int> &at, T val) { // vector of position integers, 0-based index
		update(1, 0, curr_dim - 1, at, val);
	}
};