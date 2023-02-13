#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 5;
const int MOD = 1e9 + 9;
const int BASE = 8739483;

int main() {
  int t;
  cin >> t;

  vector<int> base_pow(N);
  base_pow[0] = 1;
  for (int i = 1; i < N; i++) {
    base_pow[i] = base_pow[i - 1] * 1ll * BASE % MOD;
  }

  while (t--) {
    int n, m;
    scanf("%d %d", &n, &m);

    vector<int> c(n + 1);
    for (int i = 1; i <= n; i++) {
      scanf("%d", &c[i]);
    }

    vector<pair<int, int>> C;
    for (int i = 1; i <= n; i++) {
      if (C.empty() or c[i] != C.back().first) {
        C.emplace_back(c[i], 1);
      } else {
        C.back().second++;
      }
    }

    vector<int> c_hash(n + 1);
    c_hash[0] = 0;
    for (int i = 1; i <= n; i++) {
      c_hash[i] = (c_hash[i - 1] + c[i] * 1ll * base_pow[i] % MOD) % MOD;
    }

    vector<int> b(m + 1);
    for (int i = 1; i <= m; i++) {
      scanf("%d", &b[i]);
    }

    vector<pair<int, int>> B;
    for (int i = 1; i <= m; i++) {
      if (B.empty() or b[i] != B.back().first) {
        B.emplace_back(b[i], 1);
      } else {
        B.back().second++;
      }
    }

    int mm = B.size();
    vector<int> B0_hash, B_hash, b_hash;
    for (int j = 0; j < mm; j++) {
      int val = B[j].first;
      int freq = B[j].second;
      int hash_val = 0;
      for (int i = 1; i <= freq; i++) {
        (hash_val += val * 1ll * base_pow[i] % MOD) %= MOD;
      }
      B0_hash.push_back(hash_val);
    }

    B_hash.resize(mm, 0);
    b_hash.push_back(0);

    for (int exp = 1; exp * m <= n; exp++) {
      b_hash.push_back(0);
      int tot_freq = 0;

      for (int i = 0; i < mm; i++) {
        int val = B[i].first;
        int freq = B[i].second;
        int prev_freq = (exp - 1) * freq;

        (B_hash[i] += B0_hash[i] * 1ll * base_pow[prev_freq] % MOD) %= MOD;
        (b_hash.back() += B_hash[i] * 1ll * base_pow[tot_freq] % MOD) %= MOD;

        tot_freq += exp * freq;
      }
    }

    int ans = 0;
    int at = 1;

    for (int i = 0; i < C.size(); i++) {
      int val = C[i].first;
      int freq = C[i].second;
      if (val == B[1].first and freq % B[1].second == 0) {
        int exp = freq / B[1].second;
        int st = at - B[0].second * exp;
        int en = st + m * exp - 1;

        if (1 <= st and en <= n) {
          ans += (c_hash[en] - c_hash[st - 1] + MOD) % MOD == b_hash[exp] * 1ll * base_pow[st - 1] % MOD;
        }
      }

      at += freq;
    }

    printf("%d\n", ans);
  }

  return 0;
}