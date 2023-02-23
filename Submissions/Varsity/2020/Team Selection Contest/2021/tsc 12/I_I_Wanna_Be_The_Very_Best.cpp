#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

int main() {
  int n, k;
  cin >> n >> k;

  vector<vector<pair<ull, ull>>> v(3, vector<pair<ull, ull>>(n));
  vector<int> took;

  for (int j = 0; j < n; j++) {
    for (int i = 0; i < 3; i++) {
      v[i][j].second = j;
      scanf("%llu", &v[i][j].first);
    }
  }
  for (int i = 0; i < 3; i++) {
    sort(v[i].begin(), v[i].end());
    for (int j = 0; j < n; j++) {
      for (int j = n - 1; j >= n - k; j--)
        took.push_back(v[i][j].second);
    }
  }

  sort(took.begin(), took.end());
  took.resize(unique(took.begin(), took.end()) - took.begin());

  cout << took.size() << endl;

  return 0;
}