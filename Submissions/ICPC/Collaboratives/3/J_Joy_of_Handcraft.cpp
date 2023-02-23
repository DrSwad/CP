#include <bits/stdc++.h> // baaal
using namespace std;

int main() {
  int T;
  cin >> T;

  for (int cs = 1; cs <= T; cs++) {
    int n, m;
    scanf("%d %d", &n, &m);

    map<int, int> maxX;
    for (int i = 0; i < n; i++) {
      int t, x;
      scanf("%d %d", &t, &x);
      maxX[t] = max(maxX[t], x);
    }

    vector<vector<int>> inAt(m + 1), outAt(m + 1);
    for (auto [t, x] : maxX) {
      for (int i = 0, at = 1; at <= m; at += t, i++) {
        if (i & 1) outAt[at].push_back(x);
        else
          inAt[at].push_back(x);
      }
    }

    map<int, int> freqX;
    vector<int> ans(m + 1);

    for (int at = 1; at <= m; at++) {
      for (int x : inAt[at]) freqX[x]++;
      for (int x : outAt[at]) {
        freqX[x]--;
        if (freqX[x] == 0) freqX.erase(x);
      }

      if (freqX.empty()) ans[at] = 0;
      else
        ans[at] = freqX.rbegin()->first;
    }

    printf("Case #%d:", cs);
    for (int i = 1; i <= m; i++) { printf(" %d", ans[i]); }
    puts("");
  }

  return 0;
}