#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  ll c_cost, r_cost;
  cin >> n >> c_cost >> r_cost;

  vector<int> a(n + 2);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  ll ans;
  {
    int rn = 0, prv = -1;
    for (int i = 1; i <= n; i++) {
      if (a[i] == 0) rn++;
      else {
        if ((a[i] > 0) == prv) rn++;
        else prv = a[i] > 0;
      }
    }
    ans = r_cost * rn;
  }

  ll curr_ans = 0;
  set<pair<int, int>> segs;
  {
    vector<int> pos0;
    for (int i = 1; i <= n; i++) {
      if (a[i] == 0) {
        a[i] = 1;
        pos0.push_back(i);
      }
    }

    for (int st = 0, i = 1, prv = -1; i <= n + 1; i++) {
      if (i == n + 1 or (a[i] > 0) != prv) {
        segs.insert(make_pair(st, i - 1));
        st = i;
        prv = a[i] > 0;
      }
    }
    segs.insert(make_pair(n + 1, n + 1));

    curr_ans = r_cost * (n + 2 - segs.size());

    for (int i : pos0) a[i] = 0;
  }

  vector<pair<int, int>> sa;
  for (int i = 1; i <= n; i++) {
    sa.push_back(make_pair(abs(a[i]), i));
    if (a[i] == 0) a[i] = 1;
  }
  sort(sa.begin(), sa.end());

  auto fill_range = [&](int l, int r) {
    assert(0 <= l);
    assert(r <= n + 1);
    assert(l < r);
    int len = (r - 1) - l;
    if (l == 0 or r == n + 1) return len;
    return len - ((len & 1) == ((a[l] > 0) != (a[r] > 0)));
  };

  for (int i = 0, j; i < n; i = j) {
    int nc = sa[i].first + 1;
    j = i;
    vector<int> rpos;
    while (j < n and sa[j].first == sa[i].first) {
      rpos.push_back(sa[j].second);
      j++;
    }

    for (int pos : rpos) {
      auto it = segs.upper_bound(make_pair(pos, n + 1));
      assert(it != segs.begin());
      it--;
      auto [l, r] = *it;

      assert(it != segs.begin());
      int rp = prev(it)->second;
      assert(next(it) != segs.end());
      int ln = next(it)->first;

      segs.erase(it);
      if (l != pos) segs.insert(make_pair(l, pos - 1));
      if (pos != r) segs.insert(make_pair(pos + 1, r));

      if (l == r) {
        curr_ans += r_cost * fill_range(rp, pos);
        curr_ans += r_cost * fill_range(pos, ln);
        curr_ans += r_cost;
        curr_ans -= r_cost * fill_range(rp, ln);
      }
      else {
        if (pos == l) {
          curr_ans += r_cost * fill_range(rp, pos);
          curr_ans -= r_cost * fill_range(rp, pos + 1);
        }
        else if (pos == r) {
          curr_ans += r_cost * fill_range(pos, ln);
          curr_ans -= r_cost * fill_range(pos - 1, ln);
        }
        else {
          curr_ans -= r_cost;
          curr_ans -= r_cost * fill_range(pos - 1, pos + 1);
        }
      }
    }

    ans = min(ans, curr_ans + c_cost * nc);
  }

  cout << ans << "\n";

  return 0;
}