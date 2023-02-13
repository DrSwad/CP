#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  priority_queue<pair<int, int>> pq;
  for (int i = 1; i <= n; i++) {
    int a;
    cin >> a;
    pq.push(make_pair(a, i));
  }

  vector<pair<int, int>> ans;

  while (true) {
    auto [a1, i1] = pq.top(); pq.pop();
    auto [a2, i2] = pq.top(); pq.pop();
    if (!a1 or !a2) break;
    ans.push_back(make_pair(i1, i2));
    pq.push(make_pair(a1 - 1, i1));
    pq.push(make_pair(a2 - 1, i2));
  }

  cout << ans.size() << "\n";
  for (auto [i1, i2] : ans) cout << i1 << " " << i2 << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}