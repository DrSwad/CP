#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int w, f;
  cin >> w >> f;

  int n;
  cin >> n;

  vector<int> s(n);
  for (int &i : s) cin >> i;

  int tot_s = accumulate(s.begin(), s.end(), 0);
  vector<bool> possible(tot_s + 1, false);
  possible[0] = true;
  for (int i = 0; i < n; i++) {
    for (int sum = tot_s; sum >= s[i]; sum--) {
      if (!possible[sum] and possible[sum - s[i]]) {
        possible[sum] = true;
      }
    }
  }

  set<int> st;
  for (int i = 0; i <= tot_s; i++) {
    if (possible[i]) {
      st.insert(i);
    }
  }

  function<bool(int)> check =
    [&](int seconds) {
      ll W = 1ll * w * seconds;
      ll F = 1ll * f * seconds;

      if (W >= tot_s or F >= tot_s) return true;
      ll water_takes = *prev(st.upper_bound((int)W));
      return F >= tot_s - water_takes;
    };

  int L = 0, R = 1e6;
  while (R - L > 1) {
    int mid = (L + R) / 2;
    if (check(mid)) R = mid;
    else L = mid;
  }

  cout << R << "\n";
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