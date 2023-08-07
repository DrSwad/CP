#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
typedef long long ll;

void test_case() {
  int n, m;
  ll v;
  cin >> n >> m >> v;

  vector<ld> gain(n, -1);
  {
    string s;
    cin >> s;
    for (int i = 0; i < n; i++) {
      if (s[i] == '1') {
        gain[i] = v;
      }
    }
  }

  vector<tuple<int, int, int, int, int>> edges(m);
  for (auto & [a, x, b, y, z] : edges) {
    int c;
    cin >> a >> x >> b >> y >> c >> z;
    x--, y--, z--;
  }

  while (true) {
    ld max_gain = -1;
    int max_node = -1;

    for (auto [a, x, b, y, z] : edges) {
      if (gain[x] >= 0 and gain[y] >= 0 and gain[z] < 0) {
        ld cur_gain = 1.0 / (a / gain[x] + b / gain[y]);
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