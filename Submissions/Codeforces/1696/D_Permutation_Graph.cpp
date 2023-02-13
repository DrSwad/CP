#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  if (n == 1) {
    cout << "0\n";
    return;
  }

  vector<vector<int>> nxt(n, vector<int>(2));
  nxt[n - 1][0] = nxt[n - 1][1] = n;
  for (int it = 0; it < 2; it++) {
    for (int i = n - 2; i >= 0; i--) {
      int &j = nxt[i][it];
      j = i + 1;
      while (j < n and (a[j] > a[i]) != it) j = nxt[j][it];
    }
  }

  int dist = 0, at = 0, dir = -1;
  while (at < n - 1) {
    debug(at, dist, dir);
    if (dir != -1 and nxt[at][dir] < n) at = nxt[at][dir];
    else {
      dir = a[at + 1] > a[at];
      dist++;
      at++;
    }
  }

  cout << dist << "\n";
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