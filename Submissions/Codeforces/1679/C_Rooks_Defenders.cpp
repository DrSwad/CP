#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, q;
int f[2][N];
void update(int index, int p, int v) {
  while (p <= n) f[index][p] += v, p += p & -p;
}
int pref(int index, int p) {
  int ret = 0;
  while (p) ret += f[index][p], p -= p & -p;
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> q;
  vector<int> frow(n + 1, 0), fcol(n + 1, 0);

  while (q--) {
    int t;
    cin >> t;

    if (t == 1) {
      int x, y;
      cin >> x >> y;
      if (frow[x] == 0) update(0, x, 1);
      if (fcol[y] == 0) update(1, y, 1);
      frow[x]++;
      fcol[y]++;
    }
    else if (t == 2) {
      int x, y;
      cin >> x >> y;
      frow[x]--;
      fcol[y]--;
      if (frow[x] == 0) update(0, x, -1);
      if (fcol[y] == 0) update(1, y, -1);
    }
    else {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      if (pref(0, x2) - pref(0, x1 - 1) == x2 - (x1 - 1) or
          pref(1, y2) - pref(1, y1 - 1) == y2 - (y1 - 1)
          ) {
        cout << "Yes\n";
      }
      else {
        cout << "No\n";
      }
    }
  }

  return 0;
}