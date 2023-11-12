#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<int> a(n), b(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i] >> b[i];
  }

  // a - b
  vector<int> diff_mn(n), diff_mx(n);
  for (int i = 0; i < n; i++) {
    {
      int a_m = min(m, a[i]);
      int b_m = m - a_m;
      diff_mn[i] = (a[i] - a_m) - (b[i] - b_m);
    }
    {
      int b_m = min(m, b[i]);
      int a_m = m - b_m;
      diff_mx[i] = (a[i] - a_m) - (b[i] - b_m);
    }
  }

  ll sum_mn = 0;
  for (int i = 0; i < n; i++) {
    sum_mn += diff_mn[i];
  }

  ll cur_sum = sum_mn;
  vector<int> add(n);
  for (int i = 0; i < n; i++) {
    add[i] = min(max(0ll, 0 - cur_sum), (ll)diff_mx[i] - diff_mn[i]);
    if (add[i] & 1) add[i]--;
    cur_sum += add[i];
  }

  cout << abs(cur_sum) << "\n";
  for (int i = 0; i < n; i++) {
    int a_m = min(m, a[i]);
    int b_m = m - a_m;
    a_m -= add[i] / 2;
    b_m += add[i] / 2;
    cout << a_m << " " << b_m << "\n";
  }
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