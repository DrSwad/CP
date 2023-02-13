#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 5;

int n;
ll k;
int init[N];
int updates[N][3];

void reset() {
  for (int i = 1; i <= n; i++) {
    updates[i][0] = updates[i][1] = updates[i][2] = 0;
  }
}

bool check(int m) {
  vector<int> u(n + 1, 0);
  ll ans = 0;

  int at = 1;
  while (at <= n and init[at] <= m) at++;
  ans += at - 1;

  for (int i = 2; i <= n; i++) {
    at = max(at, i);

    int l = updates[i][0];
    int r = updates[i][1];
    int v = updates[i][2];
    if (at <= r and v <= m) {
      l = max(l, at);
      u[l] = max(u[l], r);
    }

    if (at <= n) {
      int mx = u[at];
      while (at <= n and at <= mx) {
        at++;
        if (at <= n) mx = max(mx, u[at]);
      }
    }

    ans += at - i;
  }

  return ans >= k;
}

void test_case() {
  cin >> n >> k;

  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) cin >> a[i];

  vector<int> freq(n + 1, 0);
  int mex = 0;
  for (int i = 1; i <= n; i++) {
    freq[a[i]]++;
    while (freq[mex]) mex++;
    init[i] = mex;
  }

  set<pair<int, int>> ranges;
  for (int l = 1, r; l <= n; l = r) {
    r = l + 1;
    while (r <= n and init[r] == init[l]) r++;
    ranges.insert({init[l], l});
  }

  vector<int> nxt(n + 1);
  vector<int> pos(n + 1, n + 1);
  for (int i = n; i >= 1; i--) {
    nxt[i] = pos[a[i]];
    pos[a[i]] = i;
  }

  for (int i = 2; i <= n; i++) {
    // removing a[i], adjust the `range` set accordingly
    auto ss = ranges.begin();
    ss++; // iterator to the second interval
    if (ss == ranges.end() or ss->second > i) { // first interval spans across the (i+1)'th element
      pair<int, int> p = *ranges.begin();
      p.second++;
      ranges.erase(ranges.begin());
      ranges.insert(p);
    }
    else { // first interval consists only of the i'th element
      ranges.erase(ranges.begin());
    }

    int v = a[i - 1];
    auto it = ranges.lower_bound({v, i});
    if (it == ranges.end() or it->second >= nxt[i - 1]) continue;

    pair<int, int> st = *it, en;

    while (it != ranges.end() and it->second < nxt[i - 1]) {
      en = *it;
      it = ranges.erase(it);
    }

    ranges.insert({v, st.second});
    updates[i][0] = st.second, updates[i][1] = nxt[i - 1] - 1, updates[i][2] = v;
    if (nxt[i - 1] <= n and (it == ranges.end() or it->second > nxt[i - 1])) {
      ranges.insert({en.first, nxt[i - 1]});
    }
  }

  int L = 0, R = n;
  while (L != R) {
    int mid = (L + R) / 2;
    if (check(mid)) R = mid;
    else L = mid + 1;
  }

  cout << L << "\n";

  reset();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}