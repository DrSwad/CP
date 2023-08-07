#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
typedef long long ll;

void test_case() {
  int n, m;
  ll v;
  cin >> n >> m >> v;

  vector<ld> cost(n, -1);
  vector<bool> found(n, false);
  {
    string s;
    cin >> s;
    for (int i = 0; i < n; i++) {
      if (s[i] == '1') {
        cost[i] = 1;
        found[i] = true;
      }
    }
  }

  vector<tuple<double, int, double, int, double, int>> edges(m);
  for (auto & [a, x, b, y, c, z] : edges) {
    cin >> a >> x >> b >> y >> c >> z;
    x--, y--, z--;
  }

  while (true) {
    ld min_cost = HUGE_VAL;
    int min_node = -1;

    for (auto [a, x, b, y, c, z] : edges) {
      ll A = a / c;
      ll B = b / c;
      if (found[x] and found[y] and !found[z]) {
        ld cur_cost = A + B;
        if (cur_gain > max_gain) {
          max_gain = cur_gain;
          max_node = z;
        }
      }
    }

    if (max_node == -1) break;
    gain[max_node] = max_gain;
  }

  if (gain[0] < 0) cout << "0\n";
  else {
    printf("%0.10Lf\n", gain[0]);
  }
}

int main() {
  // ios::sync_with_stdio(false);
  // cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}