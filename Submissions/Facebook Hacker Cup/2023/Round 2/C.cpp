#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> p(n + 1);
  vector adj(n + 1, vector<int>());
  for (int i = 2; i <= n; i++) {
    cin >> p[i];
    adj[p[i]].push_back(i);
  }

  vector s(n + 1, vector<string>());
  for (int i = 1; i <= n; i++) {
    int sz;
    cin >> sz;
    s[i].resize(sz);
    for (string &str : s[i]) cin >> str;
  }

  vector dp(n + 1, map<string, int>());
  map<string, int> last_found;
  map<string, bool> impossible;

  function<int(int)> dfs =
    [&](int at) {
      int leaves = 0;

      queue<int> temp;
      for (auto str : s[at]) {
        temp.push(last_found[str]);
        last_found[str] = at;
      }

      for (int to : adj[at]) {
        leaves += dfs(to);
      }

      leaves = max(leaves, 1);

      for (string str : s[at]) {
        dp[at][str] = min(leaves, dp[at][str] + 1);
        if (dp[at][str] < leaves) {
          impossible[str] = true;
        }
      }

      for (auto str : s[at]) {
        last_found[str] = temp.front();
        temp.pop();
      }

      for (auto [str, leaves_removed] : dp[at]) {
        dp[last_found[str]][str] += leaves_removed;
      }

      return leaves;
    };

  int leaves = dfs(1);

  int ans = 0;
  for (auto [str, leaves_removed] : dp[0]) {
    ans += leaves_removed == leaves and !impossible[str];
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}