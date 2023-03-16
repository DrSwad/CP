template<typename T, typename QT, class C = function<bool(const T&, const T&)>, class F = function<QT(const vector<T>&, const T&)>, class M = function<QT(const QT&, const QT&)>>
class MergeSortTree {
  int n;
  vector<vector<T>> st;
  C order;
  QT fail_return;
  F range_query;
  M merge_query;
  void build(const vector<T> &a, int stI, int L, int R) {
    if (L == R) {
      st[stI] = vector<T>(1, a[L - 1]);
      return;
    }

    int mid = (L + R) >> 1;
    build(a, stI << 1, L, mid);
    build(a, stI << 1 | 1, mid + 1, R);

    vector<T> &vL = st[stI << 1];
    vector<T> &vR = st[stI << 1 | 1];
    vector<T> &vC = st[stI];

    for (int iL = 0, iR = 0; iL < vL.size() or iR < vR.size(); ) {
      if (iL == vL.size()) vC.push_back(vR[iR++]);
      else if (iR == vR.size()) vC.push_back(vL[iL++]);
      else if (order(vL[iL], vR[iR])) vC.push_back(vL[iL++]);
      else vC.push_back(vR[iR++]);
    }
  }
  QT query(int stI, int L, int R, int l, int r, T val) {
    if (l <= L && R <= r) return range_query(st[stI], val);

    int mid = (L + R) >> 1;
    if (r <= mid) return query(stI << 1, L, mid, l, r, val);
    else if (mid + 1 <= l) return query(stI << 1 | 1, mid + 1, R, l, r, val);
    else return merge_query(
        query(stI << 1, L, mid, l, mid, val),
        query(stI << 1 | 1, mid + 1, R, mid + 1, r, val)
        );
  }
public:
  /*
     Params:
     a - vector of numbers to build the tree on
     fail_return - value to return if the query range is invalid
     range_query - if the query interval includes the current recursive tree interval, then this function is called
     merge_query - called to merge query values from the two children
     order - comparator function following usual convention, used to build the tree
   */
  MergeSortTree(const vector<T> &a, QT fail_return, const F &range_query, const M &merge_query, const C order = [] (const T&a, const T&b) { return a < b; }) {
    n = static_cast<int>(a.size());
    st.resize(4 * n + 1);
    this->fail_return = fail_return;
    this->range_query = range_query;
    this->merge_query = merge_query;
    this->order = order;
    build(a, 1, 1, n);
  }
  QT query(int l, int r, T val) { // range [l, r], 1-based index
    if (r < 1 || n < l || r < l) return fail_return;
    l = max(l, 1); r = min(r, n);
    return query(1, 1, n, l, r, val);
  }
};
/*
// st.query(l, r, v) returns left-most index in vector a that is equal to v
MergeSortTree<int, int> st(
  indices,
  -1,
  [&](const vector<int> &v, int val) {
    auto it = lower_bound(v.begin(), v.end(), val, [&](int i, int val) {
      return a[i - 1] < val;
    });
    if (it == v.end() or a[*it - 1] != val) return -1;
    return *it;
  },
  [&](int qL, int qR) { return qL == -1 ? qR : qL; },
  [&](int i, int j) { return a[i - 1] != a[j - 1] ? a[i - 1] < a[j - 1] : i < j; }
);
*/