#include <bits/stdc++.h>
using namespace std;

vector<int> test_case() {
  vector<vector<int>> items;
  vector<int> queries;

  int n = items.size();
  sort(items.begin(), items.end());

  int nq = queries.size();
  vector<pair<int, int>> nqueries(nq);
  for (int i = 0; i < nq; i++) {
    nqueries[i] = {queries[i], i};
  }
  sort(nqueries.begin(), nqueries.end());

  vector<int> ans(nq);

  for (int i = 0, iq = 0, mx = 0; iq < nq; iq++) {
    while (i < n and items[i][0] <= nqueries[iq].first) {
      mx = max(mx, items[i][1]);
      i++;
    }
    ans[nqueries[iq].second] = mx;
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}