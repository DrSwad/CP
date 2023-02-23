#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, d;
  scanf("%d %d", &n, &d);

  vector<int> a(n);
  for (int &i : a) scanf("%d", &i);

  vector<pair<int, int>> bestAt(10, {-1, -1});
  vector<vector<double>> logs(n + 1, vector<double>(10, 0));
  vector<vector<pair<int, int>>> from(n + 1, vector<pair<int, int>>(10, {-1, -1}));

  bestAt[1] = {0, 1};
  from[0][1] = {-1, -1};

  for (int i = 1; i <= n; i++) {
    vector<pair<int, int>> nBestAt = bestAt;
    for (int d = 0; d < 10; d++) {
      auto [pat, pd] = bestAt[d];
      if (pat == -1) continue;
      double nlog = logs[pat][pd] + log(a[i - 1]);
      int nat = i;
      int nd = pd * a[i - 1] % 10;

      auto [qat, qd] = nBestAt[nd];
      if (qat == -1 or logs[qat][qd] < nlog) {
        nBestAt[nd] = {nat, nd};
        logs[nat][nd] = nlog;
        from[nat][nd] = {pat, pd};
      }
    }
    bestAt = nBestAt;
  }

  auto [at, D] = bestAt[d];
  vector<int> ans;
  while (at > 0) {
    ans.push_back(a[at - 1]);
    auto nxt = from[at][d];
    at = nxt.first;
    d = nxt.second;
  }

  if (!ans.size()) puts("-1");
  else {
    printf("%d\n", (int)ans.size());
    for (int i = 0; i < ans.size(); i++) {
      if (i) printf(" ");
      printf("%d", ans[i]);
    }
  }

  return 0;
}