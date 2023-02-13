#include <bits/stdc++.h>
using namespace std;

// Use arrays everywhere instead of vectors
// Store input strings as boolean vectors to compress
// len_f[k] = length of f[k]
// dp[i] = (dp[0]+...+dp[i-1])-(dp[i-len_f[]]+...+dp[i-len_f[]])
// Maintain the sum (dp[0]+...+dp[i])
// Store the most recent DP_SZ dp values only

const int MOD = 998244353;
const int HASH_MOD = 1e9 + 9;
const int N = 3e3;
const int F = 40;
const int DP_SZ = 1e5;
const int BASE = 12356789;

int n;
vector<bool> s;
int sep[N];
int f_hash[F], f_len[F], f_pow[F];
int dp[DP_SZ];
int s_hash[F];
unordered_map<int, int> dp_mp;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 0; i < n; i++) {
    string ss;
    cin >> ss;
    for (char c : ss) {
      s.push_back(c - '0');
    }
    sep[i] = (i == 0 ? -1 : sep[i - 1]) + ss.length();
  }

  int s_len = s.size();
  int f_sz = 0;

  {
    f_hash[f_sz] = 0;
    f_len[f_sz] = 1;
    f_pow[f_sz] = BASE;
    f_sz++;
  }

  {
    f_hash[f_sz] = BASE;
    f_len[f_sz] = 1;
    f_pow[f_sz] = BASE;
    f_sz++;
  }

  while (true) {
    f_len[f_sz] = f_len[f_sz - 1] + f_len[f_sz - 2];
    if (f_len[f_sz] > s_len) break;

    f_hash[f_sz] = f_hash[f_sz - 1];
    f_pow[f_sz] = f_pow[f_sz - 1];

    for (int i = 0; i < f_len[f_sz - 2]; i++) {
      f_pow[f_sz] = 1ll * f_pow[f_sz] * BASE % HASH_MOD;
      f_hash[f_sz] = 1ll * f_hash[f_sz] * BASE % HASH_MOD;
    }

    (f_hash[f_sz] += f_hash[f_sz - 2]) %= HASH_MOD;

    f_sz++;
  }

  {
    for (int j = 0; j < f_sz; j++) {
      if (f_len[j] < DP_SZ) continue;
      for (int i = 1; i <= s_len; i++) {
        if (f_len[j] <= i - 1 and s[i - 1 - f_len[j]]) {
          (s_hash[j] += HASH_MOD - f_pow[j]) %= HASH_MOD;
        }
        s_hash[j] = 1ll * s_hash[j] * BASE % HASH_MOD;
        if (s[i - 1]) (s_hash[j] += BASE) %= HASH_MOD;

        if (s_hash[j] == f_hash[j]) {
          dp_mp[i - f_len[j]] = 0;
        }
      }
    }
  }

  dp[0] = 1;
  if (dp_mp.count(0)) dp_mp[0] = dp[0];
  memset(s_hash, 0, sizeof s_hash);

  for (int i = 1, dp_i = 1, pref = dp[0], ans_i = 0; i <= s_len; (pref += dp[dp_i]) %= MOD, i++, (dp_i += 1) %= DP_SZ) {
    dp[dp_i] = pref;

    for (int j = 0; j < f_sz; j++) {
      if (f_len[j] <= i - 1 and s[i - 1 - f_len[j]]) {
        (s_hash[j] += HASH_MOD - f_pow[j]) %= HASH_MOD;
      }
      s_hash[j] = 1ll * s_hash[j] * BASE % HASH_MOD;
      if (s[i - 1]) (s_hash[j] += BASE) %= HASH_MOD;

      if (s_hash[j] == f_hash[j]) {
        int k = i - f_len[j];
        if (f_len[j] < DP_SZ) {
          (dp[dp_i] += MOD - dp[(k + DP_SZ) % DP_SZ]) %= MOD;
        }
        else if (dp_mp.count(k)) {
          (dp[dp_i] += MOD - dp_mp[k]) %= MOD;
        }
      }
    }

    if (dp_mp.count(i)) dp_mp[i] = dp[dp_i];

    if (i - 1 == sep[ans_i]) {
      cout << dp[dp_i] << "\n";
      ans_i++;
    }
  }

  return 0;
}