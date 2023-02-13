#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, q;
  cin >> n >> q;

  string s;
  cin >> s;

  int msb = 31 - __builtin_clz(n);
  int m = msb + 1;
  vector jump(n, vector(m, make_pair(0, 0ll)));

  for (int i = n - 1; i >= 0; i--) {
    if (s[i] == ')') {
      for (int j = 0; j < m; j++) {
        jump[i][j] = {n, 0ll};
      }
    }
    else {
      {
        auto & [at, val] = jump[i][0];
        at = i + 1;
        val = 0;

        for (int len = 0; at < n and s[at] != ')'; ) {
          val += jump[at][0].second;
          at = jump[at][0].first + 1;
          len++;
          val += len;
        }
      }

      for (int j = 1; j < m; j++) {
        int k = jump[i][j - 1].first + 1;
        if (k >= n) jump[i][j] = {n, 0};
        else {
          jump[i][j] = {jump[k][j - 1].first, jump[i][j - 1].second + jump[k][j - 1].second};
        }
      }
    }
  }

  while (q--) {
    int t, l, r;
    cin >> t >> l >> r;
    l--, r--;

    int len = 0;
    long long ans = 0;

    for (int j = msb; j >= 0; j--) {
      if (l < r and jump[l][j].first <= r) {
        ans += jump[l][j].second;
        l = jump[l][j].first + 1;
        len += 1 << j;
      }
    }

    assert(l == r + 1);
    ans += (long long)len * (len + 1) / 2;
    cout << ans << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}