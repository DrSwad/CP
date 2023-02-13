#include <bits/stdc++.h>
using namespace std;

int sx[] = {0, 1, 0, -1};
int sy[] = {1, 0, -1, 0};

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<int> nonzero;
  for (int i = 0; i < n; i++) {
    if (a[i]) {
      nonzero.push_back(i);
    }
  }

  if (nonzero.size() > 4) cout << "NO\n";
  else {
    cout << "YES\n";

    vector<pair<int, int>> p(n, make_pair(0, 0));
    for (int i = 0; i < (int)nonzero.size(); i++) {
      int id = nonzero[i];
      p[id].first = a[id] * sx[i];
      p[id].second = a[id] * sy[i];
    }

    for (int i = 0; i < n; i++) {
      cout << p[i].first << " " << p[i].second << "\n";
    }
  }
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