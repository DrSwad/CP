#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
const int inv2 = (mod + 1) / 2;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

int sum(int from, int to) {
  return add(mul(to, mul(to + 1, inv2)), mod - mul(from, mul(from - 1, inv2)));
}

void test_case() {
  int n;
  cin >> n;

  vector<int> s(n);
  for (int &i : s) cin >> i;

  vector<pair<int, int>> floors;
  for (int xl = 1; xl <= s[n - 1]; ) {
    int y = s[n - 1] / xl;
    int xr = s[n - 1] / y;
    floors.emplace_back(y, sum(xl, xr));
    xl = xr + 1;
  }

  vector<int> pref(s[n - 1] + 1, 0);
  for (int i : s) pref[i]++;
  for (int i = 1; i <= s[n - 1]; i++) {
    pref[i] += pref[i - 1];
  }

  int ans = 0;
  for (auto [y, x_sum] : floors) {
    int f = 0, fd = 0;
    for (int l = y, q = 1; l <= s[n - 1]; l += y, q++) {
      int r = min(s[n - 1], min(l + y - 1, l + q));
      f += pref[r] - pref[l - 1];
      fd += pref[l] - pref[l - 1];
    }

    if (s[n - 1] % y == 0) {
      ans = add(ans, mul(fd, s[n - 1] / y));
      x_sum = add(x_sum, mod - s[n - 1] / y);
    }

    ans = add(ans, mul(f, x_sum));
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
