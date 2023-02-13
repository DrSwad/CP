#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<pair<int, int>> items(n);
  vector<int> stool_ids, pencil_ids;
  for (int id = 0; id < n; id++) {
    auto & [c, t] = items[id];
    cin >> c >> t;
    if (t == 1) stool_ids.push_back(id);
    else pencil_ids.push_back(id);
  }

  sort(
    stool_ids.begin(),
    stool_ids.end(),
    [&](int id1, int id2) {
    return items[id1] < items[id2];
  }
    );

  long long price = 0, discount = 0;

  vector<vector<int>> carts;
  while (carts.size() < k - 1) {
    if (stool_ids.empty()) break;

    int stool_id = stool_ids.back();
    carts.push_back({});
    carts.back().push_back(stool_id);
    price += items[stool_id].first;
    discount += items[stool_id].first;
    stool_ids.pop_back();
  }

  if (carts.size() < k - 1) {
    while (!pencil_ids.empty()) {
      if (carts.size() < k) carts.push_back({});
      int pencil_id = pencil_ids.back();
      carts.back().push_back(pencil_id);
      price += items[pencil_id].first;
      pencil_ids.pop_back();
    }
  }
  else {
    carts.push_back({});
    while (!stool_ids.empty()) {
      int stool_id = stool_ids.back();
      carts.back().push_back(stool_id);
      price += items[stool_id].first;
      stool_ids.pop_back();
    }
    while (!pencil_ids.empty()) {
      int pencil_id = pencil_ids.back();
      carts.back().push_back(pencil_id);
      price += items[pencil_id].first;
      pencil_ids.pop_back();
    }
    {
      bool has_discount = false;
      int min_price = INT_MAX;
      for (int id : carts.back()) {
        has_discount = has_discount or items[id].second == 1;
        min_price = min(min_price, items[id].first);
      }
      if (has_discount) {
        discount += min_price;
      }
    }
  }

  cout << fixed << setprecision(1) << (double)price - discount / 2.0 << "\n";
  for (auto &cart : carts) {
    cout << cart.size();
    for (int id : cart) {
      cout << " " << id + 1;
    }
    cout << "\n";
  }

  return 0;
}