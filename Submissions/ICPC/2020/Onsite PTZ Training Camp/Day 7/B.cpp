#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt") // use avx for older judges

#include <bits/stdc++.h>

using ll = long long;
using namespace std;
const int MOD = 1e9 + 7;

const int N = 1e2 + 5;
const int V = 1e6 + 5;

vector<int> v[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, k;
  cin >> n >> k;

  map<int, int> num;
  for (int i = 0; i <  n; i++) {
    v[i].resize(k);
    for (int j = 0; j < k; j++) {
      cin >> v[i][j];
      num[v[i][j]] = 0;
    }
  }

  int cnt = 0;
  for (auto entry : num) {
    num[entry.first] = cnt++;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) {
      v[i][j] = num[v[i][j]];
    }
  }

  vector<ll> dp(V, 1);
  for (int i = 0; i < n; i++) {
    vector<ll> ndp(V, 0LL);
    for (int j = 0; j < k; j++) {
      ndp[v[i][j]] += dp[v[i][j]];
      ndp[v[i][j]] %= MOD;
    }
    for (int j = 1; j < V; j++) {
      ndp[j] += ndp[j - 1];
      ndp[j] %= MOD;
    }
    dp = ndp;
  }
  cout << dp[V - 1] << '\n';
}