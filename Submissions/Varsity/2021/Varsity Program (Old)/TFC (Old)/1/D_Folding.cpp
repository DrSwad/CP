#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
array<vi, 2> manacher(const string&s) {
  int n = s.length();
  array<vi, 2> p = {vi(n + 1), vi(n)};
  for (int z = 0; z < 2; z++) for (int i = 0, l = 0, r = 0; i < n; i++) {
      int t = r - i + !z;
      if (i < r) p[z][i] = min(t, p[z][l + t]);
      int L = i - p[z][i], R = i + p[z][i] - !z;
      while (L >= 1 && R + 1 < n && s[L - 1] == s[R + 1]) p[z][i]++, L--, R++;
      if (R > r) l = L, r = R;
    }
  return p;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  cin >> s;
  int n = s.length();
  vector<vector<int>> dp(2, vector<int>(n));

  vector<vector<int>> man(2);
  man[0] = manacher(s)[0];
  man[1].resize(n + 1, 0);
  for (int i = 0; i < n; i++) {
    man[1][i] = man[0][n - i];
  }

  for (int it = 0; it < 2; it++) {
    vector<vector<int>> events(n + 1);
    int mx = -1;

    for (int i = 0; i < n; i++) {
      for (int e : events[i]) {
        mx = max(mx, e);
      }
      int rem = i - 1 - mx;
      if (man[it][i] < rem) dp[it][i] = n;
      else dp[it][i] = max(i, i + rem - 1);
      events[dp[it][i]].push_back(i - 1);
    }
  }

  reverse(dp[1].begin(), dp[1].end());
  for (int i = 0; i < n; i++) {
    dp[1][i] = n - 1 - dp[1][i];
  }

  // debug(dp[0]);
  // debug(dp[1]);

  int ans = n;
  for (int i = 0; i < n; i++) {
    if (dp[0][i] < n) ans = min(ans, n - i);
    if (dp[1][i] > -1) ans = min(ans, i + 1);
  }
  // debug(ans);

  vector<vector<int>> events(n + 1);
  set<int> st;
  for (int i = 0; i < n; i++) st.insert(i);

  for (int i = 0; i < n; i++) {
    events[dp[1][i] + 1].push_back(i);
  }

  for (int i = 0; i < n; i++) {
    for (int e : events[i]) st.erase(e);

    auto it = st.lower_bound(dp[0][i]);
    if (it != st.end()) {
      ans = min(ans, *it + 1 - i);
    }

    st.erase(i);
  }

  cout << ans << "\n";

  return 0;
}