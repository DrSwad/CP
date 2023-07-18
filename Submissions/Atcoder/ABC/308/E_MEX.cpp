#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;
  a.insert(a.begin(), -1);

  string s;
  cin >> s;
  s = '*' + s;

  vector pref(n + 2, vector(3, 0)), suff(n + 2, vector(3, 0));
  for (int i = 1; i <= n; i++) {
    for (int val = 0; val < 3; val++) {
      pref[i][val] = pref[i - 1][val] + (a[i] == val and s[i] == 'M');
    }
  }
  for (int i = n; i >= 1; i--) {
    for (int val = 0; val < 3; val++) {
      suff[i][val] = suff[i + 1][val] + (a[i] == val and s[i] == 'X');
    }
  }

  auto mex = [](int i, int j, int k) {
               int ans;
               for (ans = 0; i == ans or j == ans or k == ans; ans++);
               return ans;
             };

  long long ans = 0;
  for (int i = 1; i <= n; i++) {
    if (s[i] == 'E') {
      for (int l_val = 0; l_val < 3; l_val++) {
        for (int r_val = 0; r_val < 3; r_val++) {
          ans += 1ll * pref[i - 1][l_val] * suff[i + 1][r_val] * mex(l_val, a[i], r_val);
        }
      }
    }
  }

  cout << ans << "\n";

  return 0;
}