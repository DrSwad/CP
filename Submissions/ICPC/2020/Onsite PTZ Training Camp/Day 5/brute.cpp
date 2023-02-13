#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;

ll solve(int n, ll pos_i, ll pos_j, ll val, ll a, ll b) {
  if (pos_i > pos_j) swap(pos_i, pos_j);
  ll ret = 0;
  for (ll m = 0; pos_j <= b; m++, pos_i += n, pos_j += n, val += n) {
    if (a <= pos_i and pos_j <= b) {
      ret += val * (pos_i - a + 1) * (b - pos_j + 1);
    }
  }
  return ret;
}

void test_case() {
  int n;
  ll a, b;
  cin >> n >> a >> b;

  vector<int> s(n);
  for (int &i : s) cin >> i;

  ll ans = 0;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (s[i] % n != s[j] % n) continue;

      ll pos_i = i, pos_j = j;
      ll val_i = s[i], val_j = s[j];
      if (val_i < val_j) pos_i += val_j - val_i, val_i = val_j;
      if (val_j < val_i) pos_j += val_i - val_j, val_j = val_i;
      assert(val_i == val_j);

      ans += solve(n, pos_i, pos_j, val_i, a, b);
    }
  }

  cout << ans << "\n";
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    test_case();
  }

  return 0;
}