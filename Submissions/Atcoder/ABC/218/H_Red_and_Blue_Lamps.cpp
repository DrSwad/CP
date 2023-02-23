#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, r;
  cin >> n >> r;

  vector<int> a(n - 1);
  for (int &i : a) cin >> i;

  if (r == n - r) {
    long long sum = 0;
    for (int i : a) sum += i;
    cout << sum << "\n";
    return 0;
  }

  r = min(r, n - r);

  priority_queue<tuple<int, int, int>> pq;
  for (int i = 0; i < n - 2; i++) {
    pq.push({a[i] + a[i + 1], i, i + 1});
  }
  set<int> vis;
  for (int i = 0; i < n - 1; i++) {
    vis.insert(i);
  }

  long long ans = 0;
  while (r) {
    assert(!pq.empty());
    auto [sum, x, y] = pq.top(); pq.pop();
    if (!vis.count(x) or !vis.count(y)) continue;

    r--;
    ans += sum;
    vis.erase(x), vis.erase(y);

    auto it = vis.upper_bound(y);
    if (it != vis.end() and it != vis.begin()) {
      int z = *it;
      it--;
      int w = *it;
      pq.push({a[w] + a[z], w, z});
    }
  }

  cout << ans << "\n";

  return 0;
}