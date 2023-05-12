#include <bits/stdc++.h>
using namespace std;

int root(vector<int> &p, int a) { return p[a] == a ? a : (p[a] = root(p, p[a])); }
bool same(vector<int> &p, int a, int b) { return root(p, a) == root(p, b); }
void merge(vector<int> &p, int a, int b, int &comp_cnt) {
  int x = root(p, a), y = root(p, b);
  if (x == y) return;
  comp_cnt--;
  p[y] = x;
}

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<vector<int>> c(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      cin >> c[i][j];
      c[j][i] = c[i][j];
    }
  }

  vector<vector<int>> e(n);
  vector<vector<vector<int>>> p(n, vector<vector<int>>(n));
  vector<vector<int>> comp_cnt(n, vector<int>(n));
  vector<pair<int, int>> extras;

  for (int i = 0; i < n; i++) {
    p[i][i].resize(n);
    p[i][i][i] = i;
    comp_cnt[i][i] = 1;
  }

  for (int l = n - 1; l >= 0; l--) {
    for (int r = l + 1; r < n; r++) {
      p[l][r] = p[l][r - 1];

      p[l][r][r] = r;
      comp_cnt[l][r] = comp_cnt[l][r - 1] + 1;

      for (int k : e[r]) {
        if (l <= k and k <= r) {
          merge(p[l][r], k, r, comp_cnt[l][r]);
        }
      }

      if (comp_cnt[l][r] != c[l][r]) {
        e[l].push_back(r);
        e[r].push_back(l);
        m--;
        merge(p[l][r], l, r, comp_cnt[l][r]);
      }
      else if (same(p[l][r], l, r)) {
        extras.push_back({l, r});
      }

      if (comp_cnt[l][r] != c[l][r]) {
        cout << "-1\n";
        return;
      }
    }
  }

  while (m > 0 and !extras.empty()) {
    auto [i, j] = extras.back();
    extras.pop_back();
    e[i].push_back(j);
    e[j].push_back(i);
    m--;
  }

  if (m != 0) {
    cout << "-1\n";
    return;
  }

  for (int i = 0; i < n; i++) {
    for (int j : e[i]) {
      if (j > i) {
        cout << i + 1 << " " << j + 1 << "\n";
      }
    }
  }
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