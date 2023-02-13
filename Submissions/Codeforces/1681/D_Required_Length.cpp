#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n;
ll x;
unordered_map<ll, int> dp;

int go(ll x) {
  if (dp.find(x) != dp.end()) return dp[x];
  dp[x] = -1;

  vector<bool> vis(10, false);
  int tot_d = 0;
  ll xx = x;
  while (xx > 0) {
    int d = xx % 10;
    vis[d] = true;
    xx /= 10;
    tot_d++;
  }

  if (tot_d >= n) return dp[x] = 0;
  else {
    int ret = -1;
    for (int d = 1; d < 10; d++) {
      if (vis[d]) {
        int curr = go(x * d);
        if (curr != -1) {
          ret = ret == -1 ? curr : min(ret, curr);
        }
      }
    }
    if (ret != -1) ret++;
    return dp[x] = ret;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> x;

  cout << go(x) << "\n";

  return 0;
}