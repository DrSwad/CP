#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<int> p(n);
  for (int &i : p) cin >> i;
  sort(p.begin(), p.end());

  vector<int> l(m), d(m);
  for (int &i : l) cin >> i;
  for (int &i : d) cin >> i;

  vector<int> order(m);
  iota(order.begin(), order.end(), 0);
  sort(
    order.begin(),
    order.end(),
    [&](int i, int j) {
      return l[i] < l[j];
    }
  );

  long long ans = 0;
  multiset<int> ds;
  for (int i = 0, j = 0; i < n; i++) {
    while (j < m and l[order[j]] <= p[i]) {
      ds.insert(d[order[j]]);
      j++;
    }
    ans += p[i];
    if (!ds.empty()) {
      auto it = prev(ds.end());
      ans -= *it;
      ds.erase(it);
    }
  }

  cout << ans << "\n";

  return 0;
}