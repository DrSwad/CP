#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;

int main() {

  int t, n;
  cin >> t;

  while (t--) {
    cin >> n;

    map<int, int> xId, yId;
    vector<int> X(n), Y(n), W(n);

    for (int i = 0; i < n; i++) {
      cin >> X[i] >> Y[i] >> W[i];
      xId[X[i]] = 0;
      yId[Y[i]] = 0;
    }

    int xcnt = 0, ycnt = 0;
    for (auto entry : xId) {
      xId[entry.first] = xcnt++;
    }

    for (auto entry : yId) {
      yId[entry.first] = ycnt++;
    }

    vector<vector<int>> grid(xcnt, vector<int>(ycnt, 0));

    for (int i = 0; i < n; i++) {
      grid[xId[X[i]]][yId[Y[i]]] = W[i];
    }

    for (int i = 0; i < xcnt; i++) {
      for (int j = 0; j < ycnt; j++) {
        cout << i << ' ' << j << ' ' << grid[i][j] << '\n';
      }
      cout << '\n';
    }
  }

  return 0;
}