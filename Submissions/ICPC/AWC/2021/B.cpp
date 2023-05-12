#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<int> n(2);
  array<vector<int>, 2> iq, adapt;

  for (int it = 0; it < 2; it++) {
    cin >> n[it];
    iq[it].resize(n[it]);
    adapt[it].resize(n[it]);
    for (int &i : iq[it]) cin >> i;
    for (int &i : adapt[it]) cin >> i;
  }

  for (int it = 0; it < 2; it++) {
    for (int &i : adapt[it]) {
      i = min(i, n[it ^ 1]);
    }
  }

  array<vector<vector<ll>>, 2> dp;

  for (int it = 0; it < 2; it++) {
    dp[it].resize(n[it ^ 1] + 1, vector<ll>(n[it] + 1, 0));
    multiset<int> st;

    for (int took = n[it ^ 1]; took >= 0; took--) {
      for (int i = 0; i < n[it]; i++) { // n
        if (adapt[it][i] == took) {
          st.insert(iq[it][i]); // n
        }
      }

      // took fixed
      // take = 0 ... n

      int take = 0;
      auto st_it = st.rbegin();
      while (++take <= n[it]) {
        dp[it][took][take] = dp[it][took][take - 1];
        if (st_it != st.rend()) {
          dp[it][took][take] += *st_it;
          st_it++;
        }
      }
    }
  }

  ll ans = 0;

  for (int take0 = 0; take0 <= n[0]; take0++) {
    for (int take1 = 0; take1 <= n[1]; take1++) {
      ll cur = dp[0][take1][take0] + dp[1][take0][take1];
      ans = max(ans, cur);
    }
  }

  cout << ans << "\n";

  return 0;
}