#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, w;
  cin >> n >> w;

  vector<vector<int>> point_at_week(n);
  vector<vector<pair<int, int>>> point_weeks(w + 1);
  vector<vector<ll>> pref(w + 1);

  for (int i = 0; i < n; i++) {
    int p = point_at_week[i].size();
    point_at_week[i].push_back(0);
    point_weeks[p].push_back(make_pair(0, i));
  }
  for (int i = 1; i <= w; i++) {
    int k;
    cin >> k;
    for (int j = 0; j < k; j++) {
      int c;
      cin >> c;
      c--;
      int p = point_at_week[c].size();
      point_at_week[c].push_back(i);
      point_weeks[p].push_back(make_pair(i, c));
    }
  }

  vector<ll> ans(n, w);
  for (int p = w; p >= 0; p--) {
    vector<pair<int, int>> &v = point_weeks[p];

    if (p < w) {
      vector<pair<int, int>> &v2 = point_weeks[p + 1];
      int sz = v2.size();
      for (auto [cw, i] : v) {
        int nw = (p + 1) < point_at_week[i].size() ? point_at_week[i][p + 1] : w + 1;

        int st = lower_bound(v2.begin(), v2.end(), make_pair(cw, 0)) - v2.begin();
        int en = lower_bound(v2.begin(), v2.end(), make_pair(nw, 0)) - v2.begin();

        ll low = st;
        ll middle = en - st;

        ans[i] += (ll)(low + middle) * nw - low * cw - (pref[p + 1][en] - pref[p + 1][st]);
      }
    }

    sort(v.begin(), v.end());
    int sz = v.size();
    pref[p].resize(sz + 1);
    pref[p][0] = 0;
    for (int i = 0; i < sz; i++) {
      pref[p][i + 1] = pref[p][i] + v[i].first;
    }
  }

  cout << fixed << setprecision(10);
  for (int i = 0; i < n; i++) {
    cout << (long double)ans[i] / w << "\n";
  }

  return 0;
}