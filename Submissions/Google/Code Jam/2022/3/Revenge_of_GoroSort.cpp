#include <bits/stdc++.h>
using namespace std;

int n, k;

void test_case() {
  vector<int> a(n);
  for (int &i : a) cin >> i, i--;

  vector<pair<int, int>> splits;
  splits.push_back({0, n});

  while (splits.size() < n) {
    vector<pair<int, int>> nsplits;
    for (auto [st, en] : splits) {
      vector<int> vals(a.begin() + st, a.begin() + en);
      vector<int> misplaced;
      for (int i = st; i < en; i++) {
        if (a[i] != vals[i - st]) {
          misplaced.push_back(i);
        }
      }

    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t >> n >> k;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}