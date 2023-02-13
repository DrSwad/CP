#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
#pragma GCC target("fma,sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#pragma GCC optimize("unroll-loops")

const int MOD = 51123987;
const int A = 26;
const int N = 2e6 + 1;

char s[N];   // 1-indexed
int last, ptr, link[N], len[N], occ[N], depth[N], end_at[N];
map<pair<int, int>, int> nxt;
void init(string _s) {
  copy(_s.begin(), _s.end(), s + 1);
  len[1] = -1, len[2] = 0, link[1] = link[2] = 1, last = ptr = 2;
}
void reset(string _s) {
  copy(_s.begin(), _s.end(), s + 1);
  len[1] = -1, len[2] = 0, link[1] = link[2] = 1, last = ptr = 2;
  nxt.clear();
}
void feed(int at) {
  while (s[at - len[last] - 1] != s[at]) last = link[last];
  int ch = s[at] - 'a', temp = link[last];
  while (s[at - len[temp] - 1] != s[at]) temp = link[temp];
  if (nxt.find({last, ch}) == nxt.end()) {
    nxt[{last, ch}] = ++ptr, len[ptr] = len[last] + 2;
    link[ptr] = len[ptr] == 1 ? 2 : nxt[{temp, ch}];
    depth[ptr] = depth[link[ptr]] + 1;
  }
  last = nxt[{last, ch}], ++occ[last];
  end_at[at] = depth[last];
}

int main() {
  int n;
  scanf("%d", &n);

  string s;
  cin >> s;

  init(s);
  vector<int> before(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    feed(i);
    before[i] = (before[i - 1] + end_at[i]) % MOD;
  }

  reverse(s.begin(), s.end());
  reset(s);
  for (int i = 1; i <= n; i++) {
    feed(i);
  }

  int bad = 0;
  for (int i = 1; i <= n; i++) {
    (bad += 1ll * end_at[n - i] * before[i] % MOD) %= MOD;
  }

  long long tot = before[n];
  long long ans = tot * (tot - 1 + MOD) % MOD * (MOD + 1) / 2 % MOD;
  (ans += MOD - bad) %= MOD;

  cout << ans << endl;

  return 0;
}