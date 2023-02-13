#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
typedef long long LL;

LL a[N];
int n;

double solve(int dy) {
  double ans = 0.0;
  vector<pair<LL, int>> x(n + 1);
  vector<LL> t(n + 1);
  for (int i = 0; i <= n; i++) t[i] = a[i] - 1ll * i * dy;
  for (int i = 0; i <= n; i++) x[i] = {t[i], i};
  sort(x.begin(), x.end());
  int l = n, r;
  for (auto i : x) {
    r = i.second;
    if (l <= r) {
      double res = 0;
      double s = t[r] - t[l];
      if (l > 0) res = max(res, s / fabs(t[l] - t[l - 1]));
      if (r < n) res = max(res, s / fabs(t[r + 1] - t[r]));
      if (res > 1.0) res = 1.0;
      ans = max(r - l + res, ans);
    }

    l = min(l, r);
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cout << fixed << setprecision(10);

  cin >> n;
  int k;
  cin >> k;

  LL mm = 0;
  for (int i = 0; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n; i++) mm = max(mm, a[i] - a[i - 1]);
  for (int i = 0; i < k; i++) {
    double p;
    cin >> p;
    LL q = p * 10;
    if (q > mm) cout << "-1\n";
    else cout << solve(q) << "\n";
  }

  return 0;
}