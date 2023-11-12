#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 3e5 + 5;
const int bits = 31;
const int mod1 = int(1e9) + 7;
const int mod2 = int(1e9) + 9;
const int base1 = 97;
const int base2 = 1000003;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int add(int a, int b, int mod) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b, int mod) {
  return 1ll * a * b % mod;
}

int f[N];
int sz;
void update(int p, int v) {
  while (p <= sz) f[p] += v, p += p & -p;
}
int pref(int p) {
  int ret = 0;
  while (p) ret += f[p], p -= p & -p;
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> c(n);
  for (int i = 0; i < n; i++) cin >> c[i];

  string s;
  cin >> s;

  vector<vector<int>> adj(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<int> char_maps(26);
  iota(char_maps.begin(), char_maps.end(), 1);
  shuffle(char_maps.begin(), char_maps.end(), rng);

  vector<int> st(n), en(n);
  vector<ll> euler;
  function<void(int, int, int, int)> dfs =
    [&](int at, int from, int parent_hash1, int parent_hash2) {
      st[at] = euler.size();

      int cur_hash1 = add(mul(parent_hash1, base1, mod1), char_maps[s[at] - 'a'], mod1);
      int cur_hash2 = add(mul(parent_hash2, base2, mod2), char_maps[s[at] - 'a'], mod2);
      ll cur_hash = (ll)cur_hash1 << bits | cur_hash2;
      euler.push_back(cur_hash);

      for (int to : adj[at]) {
        if (to != from) {
          dfs(to, at, cur_hash1, cur_hash2);
        }
      }

      en[at] = euler.size();
    };

  dfs(0, -1, 0, 0);

  {
    vector<ll> vals;
    for (ll i : euler) vals.push_back(i);
    sort(vals.begin(), vals.end());
    vals.resize(unique(vals.begin(), vals.end()) - vals.begin());
    for (ll &i : euler) {
      i = lower_bound(vals.begin(), vals.end(), i) - vals.begin();
    }
  }

  vector<vector<int>> qr(n);
  for (int i = 0; i < n; i++) {
    qr[en[i] - 1].push_back(i);
  }

  map<int, int> freq;
  sz = n;

  vector<int> last(n);
  for (int r = 0; r < n; r++) {
    if (last[euler[r]]) {
      update(last[euler[r]], -1);
    }
    last[euler[r]] = r + 1;
    update(last[euler[r]], 1);
    for (int i : qr[r]) {
      int l = st[i];
      int dif = pref(sz) - pref(l);
      freq[dif + c[i]]++;
    }
  }

  cout << freq.rbegin()->first << "\n" << freq.rbegin()->second << "\n";

  return 0;
}