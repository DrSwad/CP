#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  string s;
  cin >> s;

  vector<vector<int>> v(2);
  for (int i = 0; i < s.length(); i++) {
    v[s[i] - '1'].push_back(i);
  }

  if (v[1].size() == 1 or v[1].size() == 2) {
    cout << "NO\n";
    return;
  }

  vector<vector<char>> ans(n, vector<char>(n, 0));

  int n1 = v[1].size();
  for (int i = 0; i < n1; i++) {
    int v1 = v[1][i];
    int v2 = v[1][(i + 1) % n1];
    ans[v1][v2] = '+';
    ans[v2][v1] = '-';
  }

  cout << "YES\n";

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (!ans[i][j]) {
        if (i == j) ans[i][j] = 'X';
        else ans[i][j] = '=';
      }

      cout << ans[i][j];
    }
    cout << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t;
  cin >> t;

  while (t--) {
    test_case();
  }

  return 0;
}