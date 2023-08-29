#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n;
  cin >> n;

  string s;
  cin >> s;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<ll> pref(n + 1);
  pref[0] = 0;
  for (int i = 0; i < n; i++) {
    pref[i + 1] = pref[i] + a[i];
  }

  vector<int> prv(n);
  vector<ll> dp(n);

  function<bool(int, int)> is_pair =
    [&](int i, int j) {
      return (s[i] == '(' and s[j] == ')') or
             (s[i] == '{' and s[j] == '}') or
             (s[i] == '[' and s[j] == ']') or
             (s[i] == '<' and s[j] == '>');
    };

  for (int i = 0; i < n; i++) {
    prv[i] = i - 1;
    while (prv[i] >= 0) {
      if (is_pair(prv[i], i)) break;
      prv[i] = prv[prv[i]] - 1;
    }
    if (prv[i] < 0) dp[i] = -1;
    else {
      ll sum = pref[i + 1] - pref[prv[i]];
      dp[i] = sum;
      if (prv[i] - 1 >= 0 and dp[prv[i] - 1] >= 0) {
        dp[i] = max(dp[i], sum + dp[prv[i] - 1]);
      }
    }
  }

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    ans = max(ans, dp[i]);
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