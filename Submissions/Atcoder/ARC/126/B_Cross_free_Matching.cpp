#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n, m;
pair<int, int> seg[N];
vector<int> lis;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int a, b;
    cin >> a >> b;
    seg[i] = {a, b};
  }

  sort(seg + 1, seg + m + 1);

  for (int l = 1, r = 1; l <= m; l = r) {
    while (r <= m and seg[l].first == seg[r].first) r++;

    vector<pair<int, int>> to_insert;
    for (int i = l; i < r; i++) {
      auto [a, b] = seg[i];
      int lb = lower_bound(lis.begin(), lis.end(), b) - lis.begin();
      to_insert.push_back({lb, b});
    }

    reverse(to_insert.begin(), to_insert.end());

    for (auto [at, b] : to_insert) {
      if (at == lis.size()) lis.push_back(b);
      else {
        assert(at < lis.size());
        lis[at] = b;
      }
    }
  }

  cout << lis.size() << "\n";

  return 0;
}