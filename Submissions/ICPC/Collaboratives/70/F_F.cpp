#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string a, b, c;
  cin >> a >> b >> b >> c >> c;

  if (count(a.begin(), a.end(), '?') > count(b.begin(), b.end(), '?')) swap(a, b);
  if (count(b.begin(), b.end(), '?') > count(c.begin(), c.end(), '?')) swap(b, c);
  if (count(a.begin(), a.end(), '?') > count(b.begin(), b.end(), '?')) swap(a, b);

  int val_a = 0, val_b = 0;
  int sz_a = a.length(), sz_b = b.length(), sz_c = c.length();

  int ans = 0;

  function<void(int)> consider =
    [&](int val_c) {
      for (int i = sz_c - 1; i >= 0; i--) {
        int d = val_c % 10;
        if (c[i] != '?' and d != c[i] - '0') return;
        if (i == 0 and sz_c > 1 and d == 0) return;
        val_c /= 10;
      }
      if (val_c) return;
      ans++;
    };

  function<void(int, int)> go =
    [&](int at_a, int at_b) {
      if (at_a == sz_a and at_b == sz_b) {
        int val_c = val_a ^ val_b;
        consider(val_c);
        return;
      }

      if (at_a < sz_a) {
        int min_d = at_a == 0 and sz_a > 1 ? 1 : 0, max_d = 9;
        if (a[at_a] != '?') min_d = max_d = a[at_a] - '0';
        for (int d = min_d; d <= max_d; d++) {
          val_a = val_a * 10 + d;
          go(at_a + 1, at_b);
          val_a /= 10;
        }
      }
      else {
        assert(at_b < sz_b);
        int min_d = at_b == 0 and sz_b > 1 ? 1 : 0, max_d = 9;
        if (b[at_b] != '?') min_d = max_d = b[at_b] - '0';
        for (int d = min_d; d <= max_d; d++) {
          val_b = val_b * 10 + d;
          go(at_a, at_b + 1);
          val_b /= 10;
        }
      }
    };

  go(0, 0);

  cout << ans << "\n";

  return 0;
}