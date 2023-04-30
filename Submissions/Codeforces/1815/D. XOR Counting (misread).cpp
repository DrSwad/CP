#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int BITS = 3; // CHANGE
const int N = 1e5 + 5;
const int mod = 998244353;

int inv[N << 1], fact[N << 1], ifact[N << 1];
int p2[N << 1];

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

int nCk(int n, int k) {
  if (k < 0 or k > n) return 0;
  return mul(fact[n], mul(ifact[k], ifact[n - k]));
}

vector<int> multiply(vector<int> a, vector<int> b) {
  vector<int> c;
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < b.size(); j++) {
      if (c.size() <= i + j) c.push_back(0);
      c[i + j] = add(c[i + j], mul(a[i], b[j]));
    }
  }
  debug(a, b, c);
  return c;
}

void test_case() {
  ll sum;
  int n;
  cin >> sum >> n;

  vector<int> prv_sum(n, 0), prv_cnt(n, 0);
  prv_cnt[0] = 1;

  for (int bit = 0; bit < BITS; bit++) {
    DB();
    debug(bit);

    vector<int> cur_sum(n + 1, 0), cur_cnt(n + 1, 0);
    for (int cur_ones = 0; cur_ones <= n; cur_ones++) {
      cur_sum[cur_ones] = mul(cur_ones % 2 == 1 ? p2[bit] : 0, nCk(n, cur_ones));
      cur_cnt[cur_ones] = nCk(n, cur_ones);
    }
    debug(cur_sum, cur_cnt);

    vector<int> new_sum(2 * n, 0);
    vector<int> mult[2];
    mult[0] = multiply(cur_cnt, prv_sum);
    mult[1] = multiply(prv_cnt, cur_sum);
    for (int it = 0; it < 2; it++) {
      for (int i = 0; i < 2 * n; i++) {
        new_sum[i] = add(new_sum[i], mult[it][i]);
      }
    }

    vector<int> new_cnt = multiply(cur_cnt, prv_cnt);

    if (sum >> bit & 1) {
      for (int i = 0; i < 2 * n - 1; i++) {
        new_sum[i] = new_sum[i + 1];
        new_cnt[i] = new_cnt[i + 1];
      }
      new_sum[2 * n - 1] = 0;
      new_cnt[2 * n - 1] = 0;
    }

    for (int carry = 0; carry < n; carry++) {
      prv_sum[carry] = new_sum[2 * carry];
      prv_cnt[carry] = new_cnt[2 * carry];
    }

    debug(prv_sum, prv_cnt);
  }

  cout << prv_sum[0] << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  inv[1] = fact[0] = ifact[0] = 1;
  for (int i = 2; i < N << 1; i++) inv[i] = mul(inv[mod % i], (mod - mod / i));
  for (int i = 1; i < N << 1; i++) fact[i] = mul(fact[i - 1], i);
  for (int i = 1; i < N << 1; i++) ifact[i] = mul(ifact[i - 1], inv[i]);

  p2[0] = 1;
  for (int i = 1; i < N << 1; i++) {
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
