#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> x(n), y(n);
  for (int i = 0; i < n; i++) {
    cin >> x[i] >> y[i];
  }

  map<pair<int, int>, int> freq;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j) {
        freq[make_pair(x[i] - x[j], y[i] - y[j])]++;
      }
    }
  }

  int mx = 0;
  for (auto [d, cnt] : freq) mx = max(mx, cnt);

  cout << n - mx << endl;

  return 0;
}