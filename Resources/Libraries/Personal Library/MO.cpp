struct MO {
  int n, q;
  int blk_sz;
  vector<tuple<int, int, int>> qv;
  vector<int> ans; // Modify ans type

  // Additional ds as needed

  // qv is 1-indexed
  MO(int n, vector<pair<int, int>> qv) : n(n) {
    q = qv.size();
    for (int i = 0; i < q; i++) {
      auto [l, r] = qv[i];
      this->qv.emplace_back(l - 1, r - 1, i + 1);
    }
    blk_sz = ceil(sqrt(n));
    sort(
      this->qv.begin(),
      this->qv.end(),
      [&blk_sz = blk_sz](const auto &q1, const auto &q2) {
        int l1 = get<0>(q1) / blk_sz, r1 = get<1>(q1);
        int l2 = get<0>(q2) / blk_sz, r2 = get<1>(q2);
        return make_pair(l1, r1) < make_pair(l2, r2);
      }
    );
  }

  // Modify (id is 1-indexed)
  void include(int id) {}

  // Modify (id is 1-indexed)
  void remove(int id) {}

  // Modify
  void reset() {}

  // Modify
  int answer() {}

  // Modify ans type
  vector<int> solve() {
    ans.resize(q);
    int L, R = n;
    for (int i = 0; i < q; i++) {
      auto [l, r, qi] = qv[i];
      if (R > r) {
        reset();
        R = r;
        L = r + 1;
      }
      while (R < r) include(++R + 1);
      while (L > l) include(--L + 1);
      while (L < l) remove(L++ + 1);

      ans[qi - 1] = answer();
    }

    return ans;
  }
};