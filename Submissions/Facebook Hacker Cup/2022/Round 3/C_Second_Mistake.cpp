#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int C = 26;
const int L = 20005;
const int BASE = 882373;
const int MOD = 1e9 + 7;

int cmap[26];
ll chash[4];
ll pbase[L];

void init() {
  cmap['m' - 'a'] = 0;
  cmap['e' - 'a'] = 1;
  cmap['t' - 'a'] = 2;
  cmap['a' - 'a'] = 3;

  chash[0] = 17;
  chash[1] = 20;
  chash[2] = 31;
  chash[3] = 47;

  pbase[0] = 1;
  for (int i = 1; i < L; i++) {
    pbase[i] = pbase[i - 1] * BASE % MOD;
  }
}

pair<ll, vector<ll>> get_hashes(string s) {
  ll hash_val = 0;
  int l = s.length();
  for (int i = 0; i < l; i++) {
    (hash_val += chash[cmap[s[i] - 'a']] * pbase[i + 1] % MOD) %= MOD;
  }
  ll ret0 = hash_val;
  vector<ll> ret1;
  for (int i = 0; i < l; i++) {
    int c1 = cmap[s[i] - 'a'];
    for (int c2 = 0; c2 < 4; c2++) {
      if (c1 != c2) {
        ll delta = (chash[c2] - chash[c1] + MOD) * pbase[i + 1] % MOD;
        ret1.push_back((hash_val + delta) % MOD);
      }
    }
  }
  return {ret0, ret1};
}

void test_case() {
  int n;
  cin >> n;

  vector<string> v(n);
  for (string &s : v) cin >> s;

  int q;
  cin >> q;
  vector<string> w(q);
  for (string &s : w) cin >> s;

  map<ll, int> hash_freq_0, hash_freq_1;
  for (int i = 0; i < n; i++) {
    auto [hash0, hash1] = get_hashes(v[i]);
    hash_freq_0[hash0]++;
    for (ll hash_val : hash1) {
      hash_freq_1[hash_val]++;
    }
  }

  vector<ll> ans(q, 0);

  for (int i = 0; i < q; i++) {
    auto [hash0, hash1] = get_hashes(w[i]);

    int matches0 = hash_freq_0.find(hash0) != hash_freq_0.end() ? hash_freq_0[hash0] : 0;
    int matches1 = hash_freq_1.find(hash0) != hash_freq_1.end() ? hash_freq_1[hash0] : 0;

    for (ll hash_val : hash1) {
      if (hash_freq_1.find(hash_val) != hash_freq_1.end()) {
        ans[i] += hash_freq_1[hash_val];
      }
    }

    int l = v[0].length();
    ans[i] -= matches0 * 3ll * l;
    ans[i] -= matches1 * 2;
    ans[i] /= 2;
  }

  ll sum = 0;
  for (ll i : ans) sum += i;
  cout << sum << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}