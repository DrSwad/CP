#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int r, c;
  cin >> r >> c;

  vector<pair<int, int>> mid;
  {
    vector<int> mid_i, mid_j;
    mid_i.push_back(r / 2 + 1);
    mid_j.push_back(c / 2 + 1);
    if (r % 2 == 0) mid_i.push_back(r / 2);
    if (c % 2 == 0) mid_j.push_back(c / 2);
    for (int i : mid_i) {
      for (int j : mid_j) {
        mid.emplace_back(i, j);
      }
    }
  }

  int ans_p = 0, ans_i, ans_j, ans_s;

  auto consider = [&](int p, int i, int j) {
    if (ans_p == 0) {
      ans_p = p, ans_i = i, ans_j = j;
    }
    else {
      int prv_dist = INT_MAX, cur_dist = INT_MAX;
      for (auto [mid_i, mid_j] : mid) {
        prv_dist = min(prv_dist, abs(mid_i - ans_i) + abs(mid_j - ans_j));
        cur_dist = min(cur_dist, abs(mid_i - i) + abs(mid_j - j));
      }
      if (cur_dist < prv_dist) {
        ans_p = p, ans_i = i, ans_j = j;
      }
    }
  };

  auto find_s = [&]() {
    auto nxt_i = [&](int i) { return r + 1 - (int)((1ll * ans_p * r - i + 1 + (c - 1)) / c); };
    vector<int> s(r + 1, -1);
    s[ans_i] = 0;

    function<int(int)> S = [&](int i) {
      if (s[i] != -1) return s[i];
      return 1 + S(nxt_i(i));
    };

    ans_s = 0;
    for (int i = 1; i <= r; i++) {
      ans_s = max(ans_s, 1 + S(i));
    }
  };

  for (int p = 1; p <= c; p++) {
    auto nxt_i = [&](int i) { return r + 1 - (int)((1ll * p * r - i + 1 + (c - 1)) / c); };
    int mn_i = nxt_i(1);
    int mx_i = nxt_i(r);

    bool possible = true;
    int cyc_i = 0;
    for (int i = mn_i; i <= mx_i; i++) {
      if (nxt_i(i) == i) {
        if (cyc_i != 0) possible = false;
        cyc_i = i;
      }
    }
    if (cyc_i == 0) possible = false;
    if (!possible) continue;

    vector<int> state(mx_i - mn_i + 1, 0);
    state[cyc_i - mn_i] = 2;

    function<void(int)> dfs = [&](int i) {
      if (state[i - mn_i] == 1) {
        possible = false;
        return;
      }
      if (state[i - mn_i] == 2) return;
      state[i - mn_i] = 1;
      dfs(nxt_i(i));
      state[i - mn_i] = 2;
    };

    for (int i = mn_i; i <= mx_i; i++) {
      if (state[i - mn_i] == 0) {
        dfs(i);
      }
    }

    if (possible) {
      long long cyc_j = (1ll * p * r - 1ll * c * r + 1) + 1ll * cyc_i * (c - 1);
      if (1 <= cyc_j and cyc_j <= c) consider(p, cyc_i, cyc_j);
    }
  }

  find_s();

  cout << ans_p << " " << (r + 1 - ans_i) << " " << ans_j << " " << ans_s << "\n";

  return 0;
}