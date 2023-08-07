#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int mx_a = *max_element(a.begin(), a.end());

  function<bool(int)> check =
    [&](int target_a) {
      if (mx_a >= target_a) return true;
      for (int i = 0; i < n - 1; i++) {
        long long need_moves = 0;
        int cur_target = target_a;
        bool possible = true;
        for (int j = i; j < n; j++, cur_target--) {
          if (a[j] >= cur_target) break;
          if (j == n - 1) possible = false;
          need_moves += cur_target - a[j];
        }
        if (possible and need_moves <= k) return true;
      }
      return false;
    };

  int L = 0, R = mx_a + k + 1;
  while (R - L > 1) {
    int mid = (L + R) / 2;
    if (check(mid)) L = mid;
    else R = mid;
  }

  cout << L << "\n";
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