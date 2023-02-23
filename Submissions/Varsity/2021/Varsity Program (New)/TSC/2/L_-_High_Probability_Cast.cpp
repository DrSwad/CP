#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<tuple<int, int, int>> ranges(n);
  for (int i = 0; i < n; i++) {
    auto & [l, r, id] = ranges[i];
    cin >> l >> r;
    id = i;
  }

  sort(ranges.begin(), ranges.end());

  vector<int> order;
  {
    int mx_r = 0;
    for (int i = n - 1; i >= 0; i--) {
      auto [l, r, id] = ranges[i];
      if (r > mx_r) order.push_back(i);
      mx_r = max(mx_r, r);
    }
  }

  function<bool(int, int, int)> cmp = [&](int big_i, int small_i, int x) {
    auto [sl, sr, sid] = ranges[small_i];
    auto [bl, br, bid] = ranges[big_i];
    if (x <= sl) return false;
    if (x >= sr) return true;
    // (br - x) / (br - bl) > (sr - x) / (sr - sl)
    // <=> (br - x) * (sr - sl) > (sr - x) * (br - bl)
    return 1ll * (br - x) * (sr - sl) > 1ll * (sr - x) * (br - bl);
  };

  int sz = order.size();
  vector<pair<int, int>> st(1, {1, order[0]});

  for (int i = 1; i < sz; i++) {
    int big_i = order[i];
    auto [l, r, id] = ranges[big_i];
    while (cmp(big_i, st.back().second, st.back().first)) {
      st.pop_back();
    }

    int small_i = st.back().second;
    int L = st.back().first, R = r;
    while (R - L > 1) {
      int x = (L + R) / 2;
      if (cmp(big_i, small_i, x)) R = x;
      else L = x;
    }

    st.push_back({R, big_i});
  }

  int q;
  cin >> q;
  while (q--) {
    int x;
    cin >> x;
    int i = prev(upper_bound(st.begin(), st.end(), make_pair(x, n)))->second;
    int id = get<2>(ranges[i]);
    cout << id + 1;
    if (q) cout << " ";
  }
  cout << "\n";

  return 0;
}