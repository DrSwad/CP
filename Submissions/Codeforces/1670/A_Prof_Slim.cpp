#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  const int mx = 1e9 + 1;
  a.insert(a.begin(), -mx);
  a.push_back(mx);
  n += 2;

  vector<int> pos_pref(n);
  a[0] = abs(a[0]);
  for (int i = 1; i < n; i++) {
    pos_pref[i] = pos_pref[i - 1] + (a[i] > 0);
    a[i] = abs(a[i]);
  }

  vector<bool> is_dec(n), is_inc(n);
  is_dec[0] = true;
  for (int i = 1; i < n; i++) {
    is_dec[i] = is_dec[i - 1] and a[i] <= a[i - 1];
  }
  is_inc[n - 1] = true;
  for (int i = n - 2; i >= 0; i--) {
    is_inc[i] = is_inc[i + 1] and a[i] <= a[i + 1];
  }

  for (int i = 0; i < n - 1; i++) {
    if (
      is_dec[i] and
      is_inc[i + 1] and
      pos_pref[i] == (n - 1 - i) - (pos_pref[n - 1] - pos_pref[i])
      ) {
      cout << "YES\n";
      return;
    }
  }

  cout << "NO\n";
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