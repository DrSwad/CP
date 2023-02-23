#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

#define ff first
#define ss second
#define pb push_back
#define sz size()
#define mp make_pair
/*--------------------------------------------------------------------*/

const int N = 3e5 + 5;
const int MOD = 998244353;

const char START = '0'; // first letter in alphabet

ll pow2[N];

struct Trie {

  static const int MAX = N * 60, ALPHA = 2, LEN = 60; // total characters, alphabet size
  int root, nodes, nxt[MAX][ALPHA], cnt[MAX];

  void init() {
    root = nodes = 1;
    memset(nxt, 0, sizeof nxt);
    memset(cnt, 0, sizeof cnt);
  }

  void insert(string str) {
    int cur = root;
    for (auto c : str) {
      if (!nxt[cur][c - START]) nxt[cur][c - START] = ++nodes;
      cur = nxt[cur][c - START];
      cnt[cur]++;
    }
  }

  void insert(int n) {
    bitset<LEN> bits(n);
    insert(bits.to_string());
  }

  bool find(string str) {
    int cur = root;
    for (auto c : str) {
      if (!nxt[cur][c - START] or !cnt[nxt[cur][c - START]]) return false;
      cur = nxt[cur][c - START];
    }
    return true;
  }

  ll get(ll num, ll x) {
    bitset<LEN> bits(num);
    string s1 = bits.to_string();
    bits = x;
    string s2 = bits.to_string();
    ll ret = 0;

    // cout << s1 << ' ' << s2 << endl;

    int cur = root;
    for (int i = 0; i < LEN; i++) {

      // cout << cur << ' ' << cnt[nxt[cur][0]] << ' ' << cnt[nxt[cur][1]] << '\n';

      if (s2[i] == '0') {
        if (s1[i] == '0') {
          cur = nxt[cur][0];
        } else {
          cur = nxt[cur][1];
        }
      } else {
        if (s1[i] == '1') {
          ret += cnt[nxt[cur][1]];
          cur = nxt[cur][0];
        } else {
          ret += cnt[nxt[cur][0]];
          cur = nxt[cur][1];
        }
      }

      if (cur == 0 or cnt[cur] == 0) break;
    }
    return ret;
  }
} T;

int main() {

  ios::sync_with_stdio(false);
  cin.tie(0);

  T.init();

  int n;
  ll x, v;
  cin >> n >> x;

  pow2[0] = 1LL;
  for (int i = 1; i <= n; i++) {
    pow2[i] = pow2[i - 1] * 2LL;
    pow2[i] %= MOD;
  }
  vector<ll> dp(n);

  ll pref_sum = 0;
  for (int i = 1; i < n; i++) {
    cin >> v;
    int w = T.get(v, x);
    T.insert(v);

    if (i) {
      dp[i] = (pow2[i] - pow2[i - w] - pref_sum) % MOD;
      if (dp[i] < 0) dp[i] += MOD;
      pref_sum += dp[i];
      pref_sum %= MOD;
    }
  }

  ll ans = pow2[n] - 1;
  for (int i = 1; i < n; i++) {
    ans -= dp[i];
    ans %= MOD;
  }
  if (ans < 0) ans += MOD;
  cout << ans << endl;
  return 0;
}