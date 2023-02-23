#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 5e5 + 5;

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  function<ll(int, int, int, ll)> solve = [&](int at, int took, int k, ll curr_sum) {
    if (at == n) at = 0;
    if (k == 0) return 0ll;
    if (took == n) {
      if (k == 1) return curr_sum;
      else return 0ll;
    }
    // debug(at, took, curr_sum);

    ll ret = 0;
    // break
    ret = max(ret, min(curr_sum, solve(at + 1, took + 1, k - 1, a[at])));
    // don't break
    ret = max(ret, solve(at + 1, took + 1, k, curr_sum + a[at]));
    // debug(at, took, k, curr_sum, ret);
    return ret;
  };

  ll ans = 0;
  for (int start = 0; start < n; start++) {
    ans = max(ans, solve(start, 0, k, 0));
  }

  cout << ans << "\n";
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