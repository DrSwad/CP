#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int h, w;
  cin >> h >> w;

  set<tuple<int, int, int>> intervals;
  map<int, int> dp_freq;
  for (int c = 0; c < w; c++) {
    intervals.insert({c, c, 0});
    dp_freq[0]++;
  }

  for (int r = 1; r <= h; r++) {
    int a, b;
    cin >> a >> b;
    a--, b--;

    auto it = intervals.lower_bound(make_tuple(a, -1, -1));
    int st, en, dp;
    if (it == intervals.begin()) {
      st = 0, en = b, dp = w;
      if (get<2>(*it) >= w) {
        en = max(get<1>(*it), en);
      }
    }
    else {
      it--;
      st = get<0>(*it);
      assert(get<1>(*it) >= a - 1);
      en = max(get<1>(*it), b);
      dp = get<2>(*it);

      int pdp = get<2>(*it);
      dp_freq[pdp]--;
      if (dp_freq[pdp] == 0) {
        dp_freq.erase(pdp);
      }
      it = intervals.erase(it);
    }

    while (it != intervals.end()) {
      auto [cst, cen, cdp] = *it;
      it = intervals.erase(it);
      dp_freq[cdp]--;
      if (dp_freq[cdp] == 0) {
        dp_freq.erase(cdp);
      }

      if (cen > en) {
        int nst = max(cst, en + 1);
        int ndp = cdp + (nst - cst);
        it = intervals.insert(it, make_tuple(nst, cen, ndp));
        dp_freq[ndp]++;
        break;
      }
    }

    dp_freq[dp]++;
    it = intervals.insert(it, make_tuple(st, en, dp));

    int ans = r + dp_freq.begin()->first;
    if (ans > r + w - 1) {
      ans = -1;
      assert(intervals.size() == 1);
    }
    cout << ans << "\n";
  }

  return 0;
}