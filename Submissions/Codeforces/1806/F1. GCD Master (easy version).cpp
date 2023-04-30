#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct MaxKSum {
  int max_val;
  vector<int> freq_bit;
  vector<ll> sum_bit;
  int tot_val;
  ll tot_sum;

  MaxKSum(int max_val) : max_val(max_val), tot_val(0), tot_sum(0ll) {
    freq_bit.assign(max_val + 1, 0);
    sum_bit.assign(max_val + 1, 0ll);
  }

  void insert(int v) {
    tot_val++;
    tot_sum += v;
    int val = v;
    while (v <= max_val) {
      freq_bit[v]++;
      sum_bit[v] += val;
      v += v & -v;
    }
  }

  void erase(int v) {
    tot_val--;
    tot_sum -= v;
    int val = v;
    while (v <= max_val) {
      freq_bit[v]--;
      sum_bit[v] -= val;
      v += v & -v;
    }
  }

  ll max_k_sum(int k) {
    if (k == 0) return 0;
    k = tot_val - k;
    ll small_sum = 0;
    int at = 0, got = 0;
    for (int p = 31 - __builtin_clz(max_val); p >= 0; p--) {
      int to = at + (1 << p);
      if (to <= max_val and got + freq_bit[to] < k) {
        got += freq_bit[to];
        small_sum += sum_bit[to];
        at = to;
      }
    }
    small_sum += 1ll * (at + 1) * (k - got);
    ll big_sum = tot_sum - small_sum;
    return big_sum;
  }
};

void test_case() {
  int n, m, k;
  cin >> n >> m >> k;
  k = n - k - 1;

  vector<int> a(n);
  vector<int> freq(m + 1, 0);
  MaxKSum ds(m);
  int tot_values = 0;
  ll tot_sum = 0;

  for (int &i : a) {
    cin >> i;
    if (freq[i]) ds.insert(i);
    else {
      tot_values++;
      tot_sum += i;
    }
    freq[i]++;
  }

  ll ans = 0;

  for (int g = 1; g <= m; g++) {
    int cur_values = 0;
    ll cur_sum = tot_sum + g;

    for (int mul = g; mul <= m; mul += g) {
      if (freq[mul]) {
        if (cur_values > 0) ds.insert(mul);
        cur_values++;
        cur_sum -= mul;
      }
    }

    if (cur_values > 0) {
      if (tot_values - cur_values <= k) {
        ll cur_ans = cur_sum + ds.max_k_sum(k - (tot_values - cur_values));
        ans = max(ans, cur_ans);
      }

      cur_values = 0;
      for (int mul = g; mul <= m; mul += g) {
        if (freq[mul]) {
          if (cur_values > 0) ds.erase(mul);
          cur_values++;
        }
      }
    }
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
