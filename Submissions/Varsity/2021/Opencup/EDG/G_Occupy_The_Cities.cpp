#include <bits/stdc++.h>
using namespace std;

vector<int> f[2];

bool check(int rounds) {
  int n = f[0].size();
  bool left_available = false;

  for (int i = 0; i < n; i++) {
    int max_take;
    if (i == 0) max_take = rounds;
    else if (i == n - 1) max_take = rounds - (left_available ^ 1);
    else max_take = 2 * rounds - (left_available ^ 1);

    if (max_take < f[0][i]) return false;
    else if (i < n - 1 and max_take == f[0][i] and f[1][i] == 1) {
      left_available = false;
    }
    else left_available = true;
  }

  return true;
}

void test_case() {
  int n;
  cin >> n;

  string s;
  cin >> s;

  for (int l = 0; l < n; ) {
    int r = l;
    while (r < n and s[r] == s[l]) r++;
    f[s[l] - '0'].push_back(r - l);
    l = r;
  }

  if (s[0] == '1') f[0].insert(f[0].begin(), 0);
  if (s.back() == '1') f[0].push_back(0);

  assert(f[0].size() >= f[1].size() and (int)f[0].size() - (int)f[1].size() <= 1);

  int L = 0, R = n;
  while (L != R) {
    int m = (L + R) / 2;
    if (check(m)) R = m;
    else L = m + 1;
  }

  cout << L << "\n";

  f[0].clear(), f[1].clear();
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