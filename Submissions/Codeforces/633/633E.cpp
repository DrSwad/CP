#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<int> v(n);
  for (int &i : v) cin >> i, i *= 100;

  vector<int> c(n);
  for (int &i : c) cin >> i;

  function<int(int, int)> potential =
    [&](int v, int c) {
      return min(v, c);
    };

  map<int, int> ms_v, ms_c;
  vector<int> p(n);

  for (int l = n - 1, r = n - 1; l >= 0; l--) {
    ms_v[v[l]]++;
    ms_c[c[l]]++;

    while (r >= l) {
      assert(!ms_v.empty() and !ms_c.empty());
      if (ms_v.rbegin()->first > ms_c.begin()->first) {
        ms_v[v[r]]--;
        if (ms_v[v[r]] == 0) ms_v.erase(v[r]);
        ms_c[c[r]]--;
        if (ms_c[c[r]] == 0) ms_c.erase(c[r]);
        r--;
      }
      else break;
    }

    if (r >= l) {
      assert(!ms_v.empty() and !ms_c.empty());
      p[l] = potential(ms_v.rbegin()->first, ms_c.begin()->first);
    }
    else {
      assert(ms_v.empty() and ms_c.empty());
      p[l] = 0;
    }

    if (r + 1 < n) {
      int cur_v = v[r + 1];
      if (!ms_v.empty()) cur_v = max(cur_v, ms_v.rbegin()->first);
      int cur_c = c[r + 1];
      if (!ms_c.empty()) cur_c = min(cur_c, ms_c.begin()->first);
      p[l] = max(p[l], potential(cur_v, cur_c));
    }
  }

  sort(p.begin(), p.end());

  double prob = (double)k / n;
  double ans = 0;

  for (int i = 0; i <= n - k; i++) {
    ans += prob * p[i];
    prob *= (double)(n - i - k) / (n - i - 1);
  }

  cout << fixed << setprecision(10) << ans << "\n";

  return 0;
}