#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  map<int, int> f;
  for (int &i : a) cin >> i, f[i]++;

  if (n == 1) cout << "-1\n";
  else if (f.size() > 2) cout << "-1\n";
  else if (f.size() == 1) {
    if (f.begin()->first == 0) cout << n << "\n";
    else if (f.begin()->first == n - 1) cout << "0\n";
    else cout << "-1\n";
  }
  else if (f.begin()->first == f.rbegin()->first - 1 and f.begin()->second == f.rbegin()->first) {
    cout << n - f.rbegin()->first << "\n";
  }
  else cout << "-1\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}