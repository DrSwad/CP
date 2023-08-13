#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

vector<int> merge(int n, vector<int> f1, vector<int> f2) {
  assert(f1.size() == 1 << n);
  assert(f2.size() == 1 << n);

  for (int i = 0; i < n; i++) {
    for (int mask = (1 << n) - 1; mask >= 0; mask--) {
      if (mask >> i & 1) {
        f1[mask] = add(f1[mask], f1[mask ^ 1 << i]);
        f2[mask] = add(f2[mask], f2[mask ^ 1 << i]);
      }
    }
  }

  vector<int> res(1 << n);
  vector f3(1 << n, vector(n, 0));
  for (int mask = 0; mask < 1 << n; mask++) {
    for (int i = 0; i < n; i++) {
      if (i) f3[mask][i] = f3[mask][i - 1];
      if (mask >> i & 1) f3[mask][i] = add(f3[mask][i], f3[mask ^ 1 << i][i]);
    }
    int cur_val = add(mul(f1[mask], f2[mask]), mod - f3[mask][n - 1]);
    res[mask] = cur_val;
    for (int i = 0; i < n; i++) {
      f3[mask][i] = add(cur_val, f3[mask][i]);
    }
  }

  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> f1(1 << n), f2(1 << n), f3(1 << n);
  for (int &i : f1) cin >> i;
  for (int &i : f2) cin >> i;
  for (int &i : f3) cin >> i;

  vector<int> f4 = merge(n, f1, merge(n, f2, f3));
  for (int i = 0; i < n; i++) {
    for (int mask = 0; mask < 1 << n; mask++)
      if (!(mask >> i & 1)) f4[mask] = add(f4[mask], f4[mask ^ 1 << i]);

  }

  int ans = 0;
  for (int mask = 0; mask < 1 << n; mask++) {
    ans = add(ans, f4[mask]);
  }

  cout << ans << "\n";

  return 0;
}