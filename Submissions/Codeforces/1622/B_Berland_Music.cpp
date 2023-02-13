#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> p(n);
  for (int &i : p) cin >> i;

  string s;
  cin >> s;

  vector<vector<int>> ids(2);
  for (int i = 0; i < n; i++) {
    ids[s[i] - '0'].push_back(i);
  }

  for (int it = 0; it < 2; it++) {
    sort(
      ids[it].begin(),
      ids[it].end(),
      [&](int i1, int i2) {
      return p[i1] < p[i2];
    }
      );
  }

  vector<int> q(n);

  for (int i = 0; i < ids[0].size(); i++) {
    q[ids[0][i]] = i;
  }
  for (int i = 0; i < ids[1].size(); i++) {
    q[ids[1][i]] = ids[0].size() + i;
  }

  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << q[i] + 1;
  }
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}