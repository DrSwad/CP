#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  long long ans = 0;
  vector<pair<int, int>> v(n);
  for (int i = 0; i < n; i++) {
    int k, l, r;
    cin >> k >> l >> r;
    v[i] = {r - l, k};
    ans += min(l, r);
  }

  sort(v.begin(), v.end());

  int L = 0, R = 0;
  for (auto [d, k] : v) {
    if (d <= 0) L++;
    else R++;
  }

  assert(L + R == n);

  for (int i = 0; i < L; i++) {
    v[i].second = min(v[i].second - 1, L - 1);
  }
  for (int i = L; i < n; i++) {
    v[i].second = max(v[i].second, n - R);
  }

  set<int> rem_pos;
  for (int i = 0; i < n; i++) {
    rem_pos.insert(i);
  }

  for (int i = 0; i < L; i++) {
    auto [d, k] = v[i];
    auto it = rem_pos.upper_bound(k);
    if (it != rem_pos.begin()) {
      ans += -d;
    }
    else {
      it = rem_pos.upper_bound(L - 1);
      assert(it != rem_pos.begin());
    }
    it--;
    rem_pos.erase(it);
  }
  for (int i = n - 1; i >= L; i--) {
    auto [d, k] = v[i];
    auto it = rem_pos.lower_bound(k);
    if (it != rem_pos.end()) {
      ans += d;
    }
    else {
      it = rem_pos.lower_bound(n - R);
      assert(it != rem_pos.end());
    }
    rem_pos.erase(it);
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