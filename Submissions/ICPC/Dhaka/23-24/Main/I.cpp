#include <bits/stdc++.h>

using namespace std;

int t, n, a[696969];

int main() {
  cin >> t;
  while (t--) {
    scanf("%d", &n);
    for (int i = 1; i <= n + n; ++i) scanf("%d", a + i);
    vector<pair<int, int>> ans;
    int half_ceil = (n + 1) / 2, half_floor = n / 2;
    ans.emplace_back(1, n);
    ans.emplace_back(n + 1, n + n);
    ans.emplace_back(half_floor + 1, half_floor + n);
    ans.emplace_back(half_ceil + 1, half_ceil + n);
    ans.emplace_back(1, n);
    ans.emplace_back(n + 1, n + n);
    ans.emplace_back(half_floor + 1, half_floor + n);
    ans.emplace_back(half_ceil + 1, half_ceil + n);
    ans.emplace_back(1, n);
    ans.emplace_back(n + 1, n + n);
    printf("%d\n", (int) ans.size());
    for (auto & [l, r] : ans) printf("%d %d\n", l, r);
    // for (int i = 1; i <= n + n; ++i) cerr << a[i] << " "; cerr << '\n';
    // for (auto [l, r] : ans) assert(l >= 1 and r <= n + n and l <= r and r - l + 1 == n), sort(a + l, a + r + 1);
    // for (int i = 1; i < n + n; ++i) assert(a[i] < a[i + 1]);
  }
  return 0;
}