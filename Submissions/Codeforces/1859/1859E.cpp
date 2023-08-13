#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = -1e18;

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<int> a(n), b(n);
  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;

  vector<vector<int>> types;
  for (int l_a = 0; l_a < 2; l_a++) {
    for (int l_b = 0; l_b < 2; l_b++) {
      int r_a = l_b ^ 1;
      int r_b = l_a ^ 1;
      types.push_back({});
      types.back().push_back(l_a * 2 - 1);
      types.back().push_back(l_b * 2 - 1);
      types.back().push_back(r_a * 2 - 1);
      types.back().push_back(r_b * 2 - 1);
    }
  }

  ll ans = 0;
  int tsz = types.size();
  vector dp_open(2, vector(tsz, vector(n + 1, INF)));
  vector dp_closed(2, vector(n + 1, INF));
  dp_closed[0][0] = 0;

  for (int i = n - 1; i >= 0; i--) {
    dp_open[1] = dp_open[0];
    dp_closed[1] = dp_closed[0];

    for (int type = 0; type < tsz; type++) {
      for (int took = 0; took <= n; took++) {
        if (took >= i) {
          dp_open[1][type][took] = max(dp_closed[0][took - i] + types[type][2] * a[i] + types[type][3] * b[i], dp_open[1][type][took]);
        }
      }
      for (int took = 0; took <= n; took++) {
        if (0 <= took + i - 1 and took + i - 1 <= n) {
          dp_closed[1][took] = max(dp_open[1][type][took + i - 1] + types[type][0] * a[i] + types[type][1] * b[i], dp_closed[1][took]);
        }
      }
    }

    swap(dp_open[0], dp_open[1]);
    swap(dp_closed[0], dp_closed[1]);

    ans = max(ans, dp_closed[0][k]);
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}