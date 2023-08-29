#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  set<pair<int, int>> st;
  for (int i = 0; i < n; i++) {
    st.emplace(a[i], i);
  }

  multiset<int> diffs;
  int last = -1;
  ll add = 0;

  for (auto [val, at] : st) {
    if (last != -1) {
      int diff = val - last;
      diffs.insert(diff);
      add += diff;
    }
    last = val;
  }

  function<void(int, int)> remove =
    [&](int val, int at) {
      // assert(a[at] == val);
      int nxt = -1, prv = -1;

      auto it = st.upper_bound(make_pair(val, at));
      if (it != st.end()) nxt = it->first;
      it--;
      if (it != st.begin()) {
        it--;
        prv = it->first;
      }

      if (nxt != -1) add -= nxt - val, diffs.erase(diffs.find(nxt - val));
      if (prv != -1) add -= val - prv, diffs.erase(diffs.find(val - prv));
      if (nxt != -1 and prv != -1) add += nxt - prv, diffs.insert(nxt - prv);

      st.erase(make_pair(val, at));
    };

  function<void(int, int)> insert =
    [&](int val, int at) {
      int nxt = -1, prv = -1;

      auto it = st.upper_bound(make_pair(val, at));
      if (it != st.end()) nxt = it->first;
      if (it != st.begin()) {
        it--;
        prv = it->first;
      }

      if (nxt != -1 and prv != -1) add -= nxt - prv, diffs.erase(diffs.find(nxt - prv));
      if (nxt != -1) add += nxt - val, diffs.insert(nxt - val);
      if (prv != -1) add += val - prv, diffs.insert(val - prv);

      st.insert(make_pair(val, at));
    };

  int q;
  cin >> q;

  for (int iq = 0; iq < q; iq++) {
    int at, val;
    cin >> at >> val;
    at--;

    remove(a[at], at);
    a[at] = val;
    insert(a[at], at);

    if (iq) cout << " ";
    cout << add + st.begin()->first + (diffs.empty() ? 0 : *diffs.rbegin());
  }
  cout << "\n";
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