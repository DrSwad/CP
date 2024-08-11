#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n, x;
  cin >> n >> x;

  assert(x == n);

  vector<int> a(n);
  for (int &i : a) cin >> i;

  a.insert(a.begin(), INT_MAX);
  a.push_back(INT_MAX);
  n += 2;

  vector streak(2, vector(n, 0));
  for (int it = 0; it < 2; it++) {
    vector<ll> pref(1, 0);
    for (int i : a) pref.push_back(pref.back() + i);
    pref.erase(pref.begin());

    for (int i = 0; i < n; i++) {
      int L = i, R = n;
      while (R - L > 1) {
        int M = (L + R) / 2;
        if (pref[M] - pref[i] < a[i]) L = M;
        else R = M;
      }
      streak[it][i] = L - i;
    }

    reverse(a.begin(), a.end());
  }

  reverse(streak[1].begin(), streak[1].end());

  set<int> active_l;
  vector<vector<int>> remove_at(n);
  vector<int> farthest_l(n);

  for (int r = 0; r < n; r++) {
    if (r + streak[0][r] + 1 < n) {
      remove_at[r + streak[0][r] + 1].push_back(r);
    }
    active_l.insert(r);

    farthest_l[r] =
      r < n - 1
      ? *active_l.lower_bound(r - streak[1][r] - 1)
      : *next(active_l.lower_bound(r - streak[1][r] - 1));

    for (int l : remove_at[r]) active_l.erase(l);
  }

  vector<int> freq(n, 0);
  for (int r = 1; r < n; r++) {
    if (farthest_l[r] >= r) continue;
    freq[farthest_l[r] + 1]++;
    freq[r]--;
  }
  for (int i = 1; i < n; i++) freq[i] += freq[i - 1];

  int ans = count(freq.begin() + 1, freq.end() - 1, 0);
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}