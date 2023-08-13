#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int max_sum = 9 * 18;
const int mod = 1e9 + 7;
const int inv2 = (mod + 1) / 2;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

vector<int> solve(ll n) {
  string s = to_string(n);
  reverse(s.begin(), s.end());

  vector<int> all(max_sum + 1, 0);
  all[0] = 1;

  vector<int> ret(max_sum + 1, 0);
  ret[0] = 1;

  for (int i = 0; i < s.size(); i++) {
    vector<int> nret(max_sum + 1, 0);
    for (int d = 0; d < s[i] - '0'; d++) {
      for (int sum = 0; sum <= max_sum - d; sum++) {
        int nsum = sum + d;
        nret[nsum] = add(nret[nsum], all[sum]);
      }
    }
    {
      int d = s[i] - '0';
      for (int sum = 0; sum <= max_sum - d; sum++) {
        int nsum = sum + d;
        nret[nsum] = add(nret[nsum], ret[sum]);
      }
    }
    swap(ret, nret);

    vector<int> nall(max_sum + 1, 0);
    for (int d = 0; d < 10; d++) {
      for (int sum = 0; sum <= max_sum - d; sum++) {
        int nsum = sum + d;
        nall[nsum] = add(nall[nsum], all[sum]);
      }
    }
    swap(all, nall);
  }

  return ret;
}

void test_case() {
  ll l, r;
  cin >> l >> r;

  vector<int> cnt_l = solve(l - 1);
  vector<int> cnt_r = solve(r);
  vector<int> cnt(max_sum + 1);
  for (int sum = 0; sum <= max_sum; sum++) {
    cnt[sum] = add(cnt_r[sum], mod - cnt_l[sum]);
  }

  int ans = mul(mul(cnt[1], cnt[1] + mod - 1), inv2);
  for (int sum1 = 1; sum1 <= max_sum; sum1++) {
    for (int sum2 = sum1 + 1; sum2 <= max_sum; sum2++) {
      if (gcd(sum1, sum2) == 1) {
        ans = add(ans, mul(cnt[sum1], cnt[sum2]));
      }
    }
  }

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