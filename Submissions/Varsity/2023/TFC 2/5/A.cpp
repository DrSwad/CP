#include <bits/stdc++.h>
using namespace std;



int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<int> n(2), y(2);
  vector<vector<int>> x(2);

  for (int it = 0; it < 2; it++) {
    cin >> n[it] >> y[it];
    x[it].resize(n[it]);
    for (int &i : x[it]) {
      cin >> i;
    }
  }

  int ans = 2;

  for (int p2 = 2; p2 <= int(1e9); p2 *= 2) {
    vector<map<int, int>> freq(2);
    for (int it = 0; it < 2; it++) {
      for (int i : x[it]) {
        freq[it][i % p2]++;
      }
    }

    for (int it = 0; it < 2; it++) {
      for (auto [rem0, cnt0] : freq[it]) {
        int rem1 = (rem0 + p2 / 2) % p2;
        int cur = cnt0;
        if (freq[it ^ 1].find(rem1) != freq[it ^ 1].end()) {
          cur += freq[it ^ 1][rem1];
        }
        ans = max(ans, cur);
      }
    }
  }

  cout << ans << "\n";

  return 0;
}