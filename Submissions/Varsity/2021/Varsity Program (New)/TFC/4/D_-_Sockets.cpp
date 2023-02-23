#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<int> p(n);
  for (int &i : p) cin >> i;

  vector<int> s(m);
  for (int &i : s) cin >> i;

  map<int, vector<pair<int, int>>> ps;
  vector<int> order(m);
  iota(order.begin(), order.end(), 0);
  sort(
    order.begin(),
    order.end(),
    [&](int i, int j) {
    return s[i] > s[j];
  }
    );

  for (int si : order) {
    int ss = s[si];
    int cnt = 0;
    while (true) {
      ps[ss].push_back({si, cnt});
      if (ss == 1) break;
      ss = (ss + 1) / 2;
      cnt++;
    }
  }

  vector<int> a(m, 0);
  vector<int> b(n, -1);
  vector<bool> svis(m, true);
  order.resize(n);
  iota(order.begin(), order.end(), 0);
  sort(
    order.begin(),
    order.end(),
    [&](int i, int j) {
    return p[i] > p[j];
  }
    );

  for (int pi : order) {
    int pv = p[pi];
    if (ps.find(pv) == ps.end()) continue;

    while (!ps[pv].empty() and !svis[ps[pv].back().first]) ps[pv].pop_back();
    if (ps[pv].empty()) continue;
    auto [si, cnt] = ps[pv].back();
    svis[si] = false;

    a[si] = cnt;
    b[pi] = si;
  }

  cout << n - count(b.begin(), b.end(), -1) << " " << accumulate(a.begin(), a.end(), 0) << "\n";
  for (int i = 0; i < m; i++) {
    if (i) cout << " ";
    cout << a[i];
  }
  cout << "\n";
  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << b[i] + 1;
  }
  cout << "\n";

  return 0;
}