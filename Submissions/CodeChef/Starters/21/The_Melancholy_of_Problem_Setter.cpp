#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n;
string colors;
vector<int> e[N];
bool ans;

bool dfs(int at = 0, int from = -1) {
  // DB();
  // debug(at, from);
  bool found = false;

  for (int to : e[at]) {
    if (to != from) {
      if (dfs(to, at)) {
        // debug(to, at);
        if (colors[at] == 'B') {
          // debug(colors[at]);
          ans = false;
        }
        else {
          if (colors[to] == 'B' or colors[at] == colors[to]) {
            // debug(colors[at], colors[to]);
            if (found) ans = false;
            else found = true;
          }
        }
      }
    }
  }

  // debug(colors[at] == 'B' or found);
  return colors[at] == 'B' or found;
}

void reset() {
  for (int i = 0; i < n; i++) {
    e[i].clear();
  }
}

void test_case() {
  // DB();
  cin >> n;
  cin >> colors;

  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    e[u].push_back(v);
    e[v].push_back(u);
  }

  ans = true;
  dfs();
  cout << (ans ? "Yes" : "No") << "\n";

  reset();
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