#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<vector<int>> pos;
  map<int, int> mp;

  for (int i = 0; i < n; i++) {
    if (mp.find(a[i]) == mp.end()) {
      pos.push_back({});
      mp[a[i]] = pos.size() - 1;
    }
    a[i] = mp[a[i]];
    pos[a[i]].push_back(i);
  }

  int nums = mp.size();
  int MAX_FREQ = 0;
  for (int i = 0; i < nums; i++) {
    reverse(pos[i].begin(), pos[i].end());
    MAX_FREQ = max(MAX_FREQ, (int)pos[i].size());
  }

  vector<int> found(nums, 0);
  vector<pair<int, int>> st(MAX_FREQ, make_pair(-1, -1));

  auto compare = [&](int freq, int a, int b) {
    if (a == -1) return false;
    if (b == -1) return true;
    if (found[a] < freq) return false;
    if (found[b] < freq) return true;
    return pos[a][found[a] - freq] < pos[b][found[b] - freq];
  };

  auto pick_best_two = [&](int freq, int a, int b, int c) {
    if (!compare(freq, a, b)) swap(a, b);
    if (!compare(freq, b, c)) swap(b, c);
    if (!compare(freq, a, b)) swap(a, b);

    if (!compare(freq, a, b) and !compare(freq, b, a)) return make_pair(b, c);
    if (!compare(freq, b, c) and !compare(freq, c, b)) return make_pair(a, b);
    return make_pair(a, b);
  };

  long long ans = 0;

  for (int i = n - 1; i >= 0; i--) {
    found[a[i]]++;
    for (int freq = 1; freq <= found[a[i]]; freq++) {
      auto [a1, a2] = st[freq - 1];
      st[freq - 1] = pick_best_two(freq, a1, a2, a[i]);
    }

    for (int freq = 1; freq <= MAX_FREQ; freq++) {
      auto [a1, a2] = st[freq - 1];
      int i1 = a1 == -1 ? n : pos[a1][found[a1] - freq];
      int i2 = a2 == -1 ? n : pos[a2][found[a2] - freq];

      int a3 = freq == MAX_FREQ ? -1 : st[freq].first;
      int i3 = a3 == -1 ? n : pos[a3][found[a3] - freq - 1];

      ans += min(i2, i3) - i1;
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}