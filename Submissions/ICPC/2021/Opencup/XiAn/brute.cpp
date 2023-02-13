#include <bits/stdc++.h>
using namespace std;

vector<int> a;
vector<int> b;
vector<vector<int>> p;
bool possible;

void reset() {
  a.clear();
  b.clear();
  p.clear();
  possible = false;
}

void dfs(int at) {
  int na = a.size();
  int nb = b.size();
  if (at >= nb) {
    bool flag = true;
    for (int i = 0; i < na; i++) {
      vector<int> v = p[i];
      sort(v.begin(), v.end());
      if (v[((int)v.size() - 1) / 2] != a[i]) {
        flag = false;
        break;
      }
    }
    if (flag) possible = true;
    return;
  }

  for (int i = 0; i < na; i++) {
    p[i].push_back(b[at]);
    dfs(at + 1);
    p[i].pop_back();
  }
}

void test_case() {
  int n;
  cin >> n;

  int bs = 0;
  for (int i = 1; i <= n; i++) {
    int aa, bb;
    cin >> aa >> bb;
    bb -= aa;
    if (aa == 0) bs += (bb > 0);
    while (aa--) a.push_back(i);
    while (bb--) b.push_back(i);
  }

  if (bs == 0) possible = true;
  else {
    for (int aa : a) p.push_back({aa});
    dfs(0);
  }

  cout << (possible ? "YES\n" : "NO\n");

  reset();
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