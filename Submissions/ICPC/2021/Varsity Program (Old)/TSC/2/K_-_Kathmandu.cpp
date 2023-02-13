#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t, d, m;
  cin >> t >> d >> m;

  vector<int> y(m);
  for (int &i : y) cin >> i;
  y.insert(y.begin(), 0);
  y.push_back(d);

  for (int i = 1; i < y.size(); i++) {
    if (y[i] - y[i - 1] >= t) {
      cout << "Y\n";
      return 0;
    }
  }

  cout << "N\n";

  return 0;
}