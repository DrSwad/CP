#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n;
  cin >> n;

  vector<vector<int>> e(n);
  for (int i = 1; i <= n - 1; i++) {
    int p;
    cin >> p;
    p--;
    e[p].push_back(i);
  }

  vector<int> l(n), r(n);
  for (int i = 0; i < n; i++) {
    cin >> l[i] >> r[i];
  }

  function<pair<ll, int>(int)> dfs = [&](int at) {
    ll vsum = 0;
    int msum = 0;
    for (int to : e[at]) {
      pair<ll, int> res = dfs(to);
      vsum += res.first;
      msum += res.second;
    }

    if (vsum < l[at]) {
      vsum = r[at];
      msum++;
    }
    else {
      vsum = min(vsum, (ll)r[at]);
    }

    return make_pair(vsum, msum);
  };

  auto [sum, moves] = dfs(0);
  cout << moves << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}