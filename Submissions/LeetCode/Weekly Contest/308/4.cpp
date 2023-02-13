#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  vector<vector<int>> buildMatrix(int k, vector<vector<int>> rowConditions, vector<vector<int>> colConditions) {
    for (auto &v : rowConditions) v[0]--, v[1]--;
    for (auto &v : colConditions) v[0]--, v[1]--;

    vector<int> rows = topsort(k, rowConditions);
    vector<int> cols = topsort(k, colConditions);
    if (rows.empty() or cols.empty()) return {};

    vector<vector<int>> ret(k, vector<int>(k, 0));
    vector<int> row(k), col(k);
    for (int i = 0; i < k; i++) row[rows[i]] = i, col[cols[i]] = i;
    for (int i = 0; i < k; i++) ret[row[i]][col[i]] = i + 1;
    return ret;
  }
  vector<int> topsort(int k, vector<vector<int>> conditions) {
    vector<int> degree(k, 0);
    vector<vector<int>> ein(k);
    for (auto &v : conditions) {
      ein[v[1]].push_back((v[0]));
      degree[v[0]]++;
    }

    vector<int> order;
    for (int i = 0; i < k; i++) {
      int j;
      for (j = 0; j < k; j++) {
        if (degree[j] == 0) break;
      }
      if (j == k) return {};
      degree[j] = -1;
      order.push_back(j);
      for (int v : ein[j]) degree[v]--;
    }

    reverse(order.begin(), order.end());
    return order;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  debug(Solution().buildMatrix(3, {{1, 2}, {3, 2}}, {{2, 1}, {3, 2}}));

  return 0;
}