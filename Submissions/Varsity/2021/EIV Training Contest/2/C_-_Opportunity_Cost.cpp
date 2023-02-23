#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<vector<int>> v(n, vector<int>(3));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 3; j++) {
      cin >> v[i][j];
    }
  }

  vector<ll> mx(8);
  for (int mask = 0; mask < 8; mask++) {
    mx[mask] = 0;
    for (int i = 0; i < n; i++) {
      ll curr = 0;
      for (int j = 0; j < 3; j++) {
        if (mask >> j & 1) {
          curr += v[i][j];
        }
      }
      mx[mask] = max(mx[mask], curr);
    }
  }

  ll mn_cost = LLONG_MAX, mn_i;
  for (int i = 0; i < n; i++) {
    ll curr_cost = 0;
    for (int mask = 0; mask < 8; mask++) {
      ll curr = 0;
      for (int j = 0; j < 3; j++) {
        if (mask >> j & 1) {
          curr += v[i][j];
        }
      }
      curr_cost = max(curr_cost, mx[mask] - curr);
    }
    if (curr_cost < mn_cost) {
      mn_cost = curr_cost;
      mn_i = i;
    }
  }

  cout << mn_cost << " " << mn_i + 1 << "\n";

  return 0;
}