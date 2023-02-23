#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int rn, cn;
  cin >> rn >> cn;

  vector<vector<int>> rv(rn), cv(cn);
  for (int r = 0; r < rn; r++) {
    for (int c = 0; c < cn; c++) {
      int x;
      cin >> x;
      rv[r].push_back(x);
      cv[c].push_back(x);
    }
  }

  for (int r = 0; r < rn; r++) {
    sort(rv[r].begin(), rv[r].end());
  }
  for (int c = 0; c < cn; c++) {
    sort(cv[c].begin(), cv[c].end());
  }

  auto check = [&](int m) {
    for (int c = 0; c < cn; c++) {
      if (cv[c].back() < m) return false;
    }
    for (int r = 0; r < rn; r++) {
      if (rv[r][cn - 1] >= m and rv[r][cn - 2] >= m) {
        return true;
      }
    }
    return false;
  };

  int L = 0, R = 1e9;
  while (L != R) {
    int m = (L + R + 1) / 2;
    if (check(m)) L = m;
    else R = m - 1;
  }

  cout << L << "\n";
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