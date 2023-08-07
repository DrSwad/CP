#include <bits/stdc++.h>
using namespace std;

int cost(int n) {
  if (n == 1) return 0;
  int left = n / 2;
  int right = n - left;
  return cost(left) + cost(right) + (n - 1) * (n - 1) + (n - 2) * (n - 2);
}

void test_case() {
  int n;
  cin >> n;

  function<int(int, int)> query =
    [&](int l, int r) {
      if (l >= r) return 0;
      cout << "? " << l << " " << r << endl;
      int res;
      cin >> res;
      return res;
    };

  function<void(int)> answer =
    [&](int ans) {
      cout << "! " << ans << endl;
    };

  function<int(int, int)> solve =
    [&](int l, int r) {
      assert(l <= r);
      int len = r - l + 1;
      if (len == 1) return l;

      int left = len / 2;
      int l_ans = solve(l, l + (left - 1));
      int r_ans = solve(l + left, r);

      int tot = query(l_ans, r_ans);
      int rem = query(l_ans, r_ans - 1);

      return tot == rem ? r_ans : l_ans;
    };

  answer(solve(1, n));
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