#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n), b(n);
  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());
  a.push_back(0);
  b.push_back(0);

  vector<vector<int>> from(2, vector<int>(n + 1, -1));
  from[0][0] = 0;
  set<int> rem;
  for (int i = 1; i <= n; i++) rem.insert(i);
  queue<int> q;
  q.push(0);

  while (!q.empty()) {
    int at = q.front(); q.pop();
    int l = at, r = l + a[at];

    set<int>::iterator it = rem.lower_bound(l);
    while (it != rem.end() and * it <= r) {
      int nat = *it;
      from[1][nat] = at;
      rem.erase(nat);

      int nat2 = nat - b[nat];
      if (from[0][nat2] == -1) {
        from[0][nat2] = nat;
        q.push(nat2);
      }

      it = rem.lower_bound(l);
    }
  }

  if (from[1][n] == -1) {
    cout << "-1\n";
  }
  else {
    vector<int> path;
    for (int at = n; from[1][at] != -1; at = from[0][from[1][at]]) {
      path.push_back(n - at);
    }
    reverse(path.begin(), path.end());

    cout << path.size() << "\n";
    for (int i = 0; i < path.size(); i++) {
      if (i) cout << " ";
      cout << path[i];
    }
    cout << "\n";
  }
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