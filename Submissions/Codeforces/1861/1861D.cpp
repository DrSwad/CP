#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<int> pref_inc(n + 1), suff_dec(n + 1);
  pref_inc[0] = pref_inc[1] = 0;
  for (int i = 2; i <= n; i++) {
    pref_inc[i] = pref_inc[i - 1] + (a[i - 1] >= a[i - 2]);
  }
  suff_dec[0] = suff_dec[1] = 0;
  for (int i = 2; i <= n; i++) {
    suff_dec[i] = suff_dec[i - 1] + (a[n - i] >= a[n - i + 1]);
  }

  int ans = INT_MAX;
  for (int neg = 0; neg <= n; neg++) {
    int pos = n - neg;
    ans = min(ans, pref_inc[neg] + suff_dec[pos] + (neg != 0));
  }

  cout << ans << "\n";
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