#include <bits/stdc++.h>
using namespace std;

int solve(vector<pair<int, int>> x) {
  map<int, int> xf;
  for (auto [l, r] : x) {
    xf[l]--;
    xf[r]--;
  }

  int px = -1e9, cf = x.size();
  long long d = 0;
  for (auto [l, r] : x) {
    d += l - px;
  }

  long long mnd = d;
  int ans = px;

  for (auto [cx, f] : xf) {
    d -= 1ll * (cx - px) * cf;
    if (abs(d) < mnd) {
      mnd = abs(d);
      ans = cx;
    }
    cf += f;
    px = cx;
  }

  return ans;
}

void test_case() {
  int n;
  cin >> n;

  vector<pair<int, int>> x(n), y(n);
  for (int i = 0; i < n; i++) {
    auto & [x1, x2] = x[i];
    auto & [y1, y2] = y[i];
    cin >> x1 >> y1 >> x2 >> y2;
  }

  cout << solve(x) << " " << solve(y) << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}