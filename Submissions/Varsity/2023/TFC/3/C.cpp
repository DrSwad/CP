#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<int> a(n);
  for (int &i : a) cin >> i, i--;

  vector<int> freq(m, 0);
  for (int i : a) freq[i]++;

  vector c_cost(m, vector(n, 0));
  for (int c = 0; c < m; c++) {
    int cur_cost = 0;
    for (int i = 0; i < freq[c]; i++) {
      cur_cost += a[i] != c;
    }
    c_cost[c][0] = cur_cost;

    for (int i = 1; i + freq[c] <= n; i++) {
      c_cost[c][i] = c_cost[c][i - 1];
      c_cost[c][i] -= a[i - 1] != c;
      c_cost[c][i] += a[i + freq[c] - 1] != c;
    }
  }

  vector<int> freq_sum(1 << m, 0);
  for (int mask = 1; mask < 1 << m; mask++) {
    int lsb = __builtin_ctz(mask);
    freq_sum[mask] = freq_sum[mask - (1 << lsb)] + freq[lsb];
  }

  vector<int> mask_cost(1 << m, INT_MAX);
  mask_cost[0] = 0;
  for (int mask = 1; mask < 1 << m; mask++) {
    for (int i = 0; i < m; i++) {
      if (mask >> i & 1) {
        int submask = mask - (1 << i);
        mask_cost[mask] = min(mask_cost[mask], mask_cost[submask] + c_cost[i][freq_sum[submask]]);
      }
    }
  }

  cout << mask_cost[(1 << m) - 1] << "\n";

  return 0;
}