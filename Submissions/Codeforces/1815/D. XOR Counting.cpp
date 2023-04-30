#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int BITS = 60;
const int mod = 998244353;

int p2[BITS];

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

void test_case() {
  ll sum;
  int n;
  cin >> sum >> n;

  int mx = 5;

  vector<int> prv_sum(mx + 1, 0), prv_cnt(mx + 1, 0);
  prv_cnt[0] = 1;

  for (int bit = 0; bit < BITS; bit++) {
    vector<int> new_sum(mx + 1, 0), new_cnt(mx + 1, 0);

    for (int cur_carry = 0; cur_carry <= mx; cur_carry++) {
      for (int take = 0; take <= 1; take++) {
        for (int remove_pair = 0; remove_pair <= 1; remove_pair++) {
          int cur_ones = take + remove_pair * 2;
          if (cur_ones > n) continue;

          int rem_ones = cur_carry - cur_ones;
          if (rem_ones < 0) continue;

          int prv_carry = rem_ones * 2 + (bit > 0 and (sum >> (bit - 1) & 1) ? 1 : 0);
          if (prv_carry > mx) continue;

          new_sum[cur_carry] = add(new_sum[cur_carry], prv_sum[prv_carry]);
          if (take) {
            new_sum[cur_carry] = add(new_sum[cur_carry], mul(prv_cnt[prv_carry], p2[bit]));
          }

          new_cnt[cur_carry] = add(new_cnt[cur_carry], prv_cnt[prv_carry]);
        }
      }
    }

    swap(prv_sum, new_sum);
    swap(prv_cnt, new_cnt);
  }

  cout << prv_sum[((sum >> (BITS - 1)) & 1) ? 1 : 0] << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  p2[0] = 1;
  for (int i = 1; i < BITS; i++) {
    p2[i] = mul(p2[i - 1], 2);
  }

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}
