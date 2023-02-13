#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n, c, q;
  cin >> n >> c >> q;

  string s;
  cin >> s;

  vector<tuple<ll, ll, ll>> states(c + 1);
  states[0] = {n, -1, -1};
  for (int i = 1; i <= c; i++) {
    ll l, r;
    cin >> l >> r;
    l--;
    states[i] = {get<0>(states[i - 1]) + (r - l), l, r};
  }

  while (q--) {
    ll k;
    cin >> k;
    k--;

    for (int i = c; i > 0; i--) {
      auto [curr_len, l, r] = states[i];
      ll prev_len = curr_len - (r - l);
      if (k >= prev_len) k = l + (k - prev_len);
    }

    cout << s[k] << "\n";
  }
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