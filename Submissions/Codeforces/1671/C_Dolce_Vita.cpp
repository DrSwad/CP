#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n, x;
  cin >> n >> x;

  vector<int> a(n);
  for (int &i : a) cin >> i;
  sort(a.begin(), a.end());

  int curr_take;
  ll curr_sum = 0;
  for (curr_take = 0; curr_take < n; curr_take++) {
    if (a[curr_take] + curr_sum > x) break;
    curr_sum += a[curr_take];
  }

  ll ans = 0;
  ll days_passed = 0;
  while (curr_take) {
    ll days = (x < curr_sum) ? 0 : (x - curr_sum) / curr_take + 1;
    ans += days * curr_take;

    days_passed += days;
    curr_sum += days * curr_take;
    curr_sum -= a[curr_take - 1] + days_passed;
    curr_take--;
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