#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k;
  cin >> n >> k;

  string s;
  cin >> s;

  vector<int> l(k), r(k);
  for (int &i : l) cin >> i, i--;
  for (int &i : r) cin >> i, i--;

  vector<int> with(n);
  vector<int> in_range(n);
  for (int i = 0, ii = 0; i < n; i++) {
    if (i > r[ii]) ii++;
    in_range[i] = ii;
    with[i] = l[ii] + r[ii] - i;
  }

  vector<int> state(n, 0);

  int q;
  cin >> q;

  while (q--) {
    int x;
    cin >> x;
    x--;

    int ll = l[in_range[x]];
    int rr = r[in_range[x]];
    int L = min(x, ll + rr - x);
    int R = max(x, ll + rr - x);

    state[L] ^= 1;
    if (R < n - 1) state[R + 1] ^= 1;
  }

  string ans(n, '.');
  for (int i = 0; i < n; i++) {
    if (i) state[i] ^= state[i - 1];
    if (state[i]) ans[i] = s[with[i]];
    else ans[i] = s[i];
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}