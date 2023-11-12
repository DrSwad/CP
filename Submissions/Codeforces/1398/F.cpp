#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  string s;
  cin >> s;

  vector nxt(2, vector(n, n));
  vector p(2, vector(n + 1, vector<int>()));

  for (int val = 0; val < 2; val++) {
    for (int i = n - 1; i >= 0; i--) {
      if (s[i] - '0' == val) nxt[val][i] = i;
      else nxt[val][i] = i < n - 1 ? nxt[val][i + 1] : n;
    }
    for (int i = 0; i < n - 1; i++) {
      if (i == 0 or s[i - 1] - '0' == val) {
        for (int x = nxt[val][i] - i; x >= 1; x--) {
          p[val][x].push_back(i);
        }
      }
    }
  }

  for (int x = 1; x <= n; x++) {
    int ptr[2] = {0};
    int at = 0;
    int ans = 0;

    while (true) {
      if (at >= n) break;
      if (nxt[0][at] - at >= x or nxt[1][at] - at >= x) {
        at += x;
        ans++;
      }
      else {
        int to = n;
        for (int val = 0; val < 2; val++) {
          while (ptr[val] < p[val][x].size() and p[val][x][ptr[val]] < at) {
            ptr[val]++;
          }
          if (ptr[val] < p[val][x].size()) {
            to = min(to, p[val][x][ptr[val]]);
          }
        }

        if (to < n) ans++;
        at = to + x;
      }
    }

    if (x > 1) cout << " ";
    cout << ans;
  }

  cout << "\n";

  return 0;
}