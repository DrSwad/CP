#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> ans;

void go(int cell1, int n, int &k) {
  if (n == 1) return;

  for (int i = 0; i < 4; i++) {
    int diff = (4 * n - 6) - 2 * i;
    if (diff > 0 and k >= diff) {
      k -= diff;
      int st = cell1 + (n - 1) * i + 1;
      int en = st + diff + 1;
      ans.push_back({st, en});
      break;
    }
  }

  go(cell1 + (4 * n - 4), n - 2, k);
}

void test_case() {
  ans.clear();

  int n, k;
  cin >> n >> k;

  k = (n * n - 1) - k;

  go(1, n, k);

  if (k > 0) {
    cout << "IMPOSSIBLE\n";
  }
  else {
    cout << ans.size() << "\n";
    for (auto [st, en] : ans) {
      cout << st << " " << en << "\n";
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}