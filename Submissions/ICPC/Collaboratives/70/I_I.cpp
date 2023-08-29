#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector sorted(n, vector(n, false));
  for (int l = 0; l < n; l++) {
    sorted[l][l] = true;
    for (int r = l + 1; r < n; r++) {
      sorted[l][r] = sorted[l][r - 1] and a[r] > a[r - 1];
    }
  }

  vector C(m + 1, vector(m + 1, 0));
  for (int up = 0; up <= m; up++) {
    for (int down = 0; down <= up; down++) {
      if (down == 0 or down == up) C[up][down] = 1;
      else C[up][down] = add(C[up - 1][down], C[up - 1][down - 1]);
    }
  }

  vector group_ways(m + 1, 0);
  for (int i = 1; i <= m; i++) {
    int i_pow_m = 1;
    for (int j = 0; j < m; j++) i_pow_m = mul(i_pow_m, i);

    group_ways[i] = i_pow_m;
    for (int j = 1; j < i; j++) {
      group_ways[i] = add(group_ways[i], mod - mul(group_ways[j], C[i][j]));
    }
  }

  vector p2(m + 1, 0);
  p2[0] = 1;
  for (int i = 1; i <= m; i++) p2[i] = mul(p2[i - 1], 2);

  vector<int> fact(m + 1), inv(m + 1), ifact(m + 1);
  inv[1] = fact[0] = ifact[0] = 1;
  for (int i = 2; i <= m; i++) inv[i] = mul(inv[mod % i], (mod - mod / i));
  for (int i = 1; i <= m; i++) fact[i] = mul(fact[i - 1], i);
  for (int i = 1; i <= m; i++) ifact[i] = mul(ifact[i - 1], inv[i]);

  int ans = 0;

  for (int left = 0; left <= n; left++) {
    for (int right = 0; right <= n - left; right++) {
      int l = left;
      int r = n - 1 - right;
      if (r < l or sorted[l][r]) {
        int left = l;
        int right = n - 1 - r;
        int groups = left + right;
        if (groups > m) continue;
        ans = add(ans, mul(mul(group_ways[groups], mul(ifact[left], ifact[right])), p2[m - groups]));
      }
    }
  }

  cout << ans << "\n";

  return 0;
}