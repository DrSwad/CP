#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  function<bool(int)> check = [&](int d) {
    int rk = k;
    vector<int> na = a;

    for (int i = 0; i < n; i++) {
      if (2 * a[i] < d) {
        if (!rk) return false;
        na[i] = INF;
        rk--;
      }
    }

    if (rk >= 2) return true;

    for (int i = 0; i < n - 1; i++) {
      if (min(na[i], na[i + 1]) >= d) return true;
      if (rk >= 1 and max(na[i], na[i + 1]) >= d) return true;
    }

    return false;
  };

  int l = 0, r = INF + 1;
  while (r - l > 1) {
    int m = (l + r) / 2;
    if (check(m)) l = m;
    else r = m;
  }

  cout << l << "\n";
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