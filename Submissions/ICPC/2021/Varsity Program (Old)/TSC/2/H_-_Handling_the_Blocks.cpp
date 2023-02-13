#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<pair<int, int>> values, indices;
  for (int i = 0; i < n; i++) {
    int value, color;
    cin >> value >> color;
    values.push_back({color, value});
    indices.push_back({color, i});
  }

  sort(values.begin(), values.end());
  sort(indices.begin(), indices.end());

  vector<int> final_order(n);
  for (int i = 0; i < n; i++) {
    final_order[indices[i].second] = values[i].second;
  }

  cout << (is_sorted(final_order.begin(), final_order.end()) ? "Y\n" : "N\n");

  return 0;
}