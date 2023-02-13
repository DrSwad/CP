#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  int need = n / m;

  vector<int> a(n);
  vector<vector<int>> b(m);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    b[a[i] % m].push_back(i);
  }

  long long ans = 0;
  queue<pair<int, int>> q;

  for (int ii = 0; ii < 2 * m; ii++) {
    int i = ii % m;
    while (b[i].size() > need) {
      q.push({b[i].back(), ii});
      b[i].pop_back();
    }
    while (b[i].size() < need and !q.empty()) {
      auto [j, _ii] = q.front();
      q.pop();
      b[i].push_back(j);
      a[j] += ii - _ii;
    }
    ans += q.size();
  }

  cout << ans << "\n";
  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << a[i];
  }
  cout << "\n";

  return 0;
}