#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 3e5 + 5;
const int B = 60;
const int T = N * B + 2;
const int MOD = 998244353;

ll x;
int trie_sz;
int trie[2][T];
int sub[T];
int depth[T];
int inv[T];
bool dp_done[T];
int dp[T];
int q[T], qi;

void reset_q() {
  qi = 0;
}

void push_q(int val) {
  assert(qi < T);
  q[qi++] = val;
}

void pop_q() {
  assert(qi >= 1);
  qi--;
}

int front_q() {
  assert(qi >= 1);
  return q[qi - 1];
}

bool empty_q() {
  return qi == 0;
}

int add(int a, int b) {
  int c = a + b;
  if (c >= MOD) c -= MOD;
  return c;
}

int mul(int a, int b) {
  return 1ll * a * b % MOD;
}

void insert(ll a) {
  int at = 1;
  sub[at]++;
  for (int i = B - 1; i >= 0; i--) {
    bool b = a & 1ll << i;
    if (!trie[b][at]) trie[b][at] = ++trie_sz;
    at = trie[b][at];
    sub[at]++;
  }
}

void init() {
  reset_q();
  push_q(1);
  depth[1] = 0;
  inv[1] = 1;

  while (!empty_q()) {
    int at = front_q();
    pop_q();
    // debug(at, depth[at]);

    for (int bv = 0; bv < 2; bv++) {
      int to = trie[bv][at];
      if (to) {
        depth[to] = depth[at] + 1;
        bool bx = x & 1ll << (B - depth[to]);
        int bi = bv ^ bx;
        // debug(to, nx, bx, bi);
        inv[to] = inv[at] ? trie[bi][inv[at]] : 0;
        push_q(to);
      }
    }
  }
}

void calc_dp() {
  reset_q();
  push_q(1);
  stack<int> order;
  while (!empty_q()) {
    int at = front_q();
    order.push(at);
    pop_q();
    for (int bv = 0; bv < 2; bv++) {
      int to = trie[bv][at];
      if (to) {
        push_q(to);
      }
    }
  }

  while (!order.empty()) {
    // DB();
    int at = order.top();
    order.pop();
    // debug(at);
    if (inv[at] and dp_done[inv[at]]) {
      dp[at] = dp[inv[at]];
      dp_done[at] = true;
      continue;
    }
    dp_done[at] = true;

    int iat = inv[at];
    int b = depth[at];
    bool bx = x & 1ll << (B - 1 - b);

    if (b == B) {
      assert(at != iat);
      // debug(at, iat);
      if (iat) dp[at] = mul(sub[at], sub[iat]);
      else dp[at] = 0;
    }
    else {
      int at_l = trie[0][at];
      int at_r = trie[1][at];
      if (at == iat) {
        if (bx == 1) {
          int dp_l = at_l ? dp[at_l] : 0;
          int sub_l = at_l ? sub[at_l] : 0;
          int sub_r = at_r ? sub[at_r] : 0;
          dp[at] = add(dp_l, add(sub_l, add(sub_r, 1)));
        }
        else dp[at] = mul((at_l ? dp[at_l] : 1), (at_r ? dp[at_r] : 1));
      }
      else {
        if (bx == 1) {
          int dp_l = at_l ? dp[at_l] : 0;
          int dp_r = at_r ? dp[at_r] : 0;
          dp[at] = add(dp_l, dp_r);
        }
        else {
          int iat_l = iat ? trie[0][iat] : 0;
          int iat_r = iat ? trie[1][iat] : 0;
          int dp_l = at_l ? dp[at_l] : 0;
          int sub_l = at_l ? sub[at_l] : 0;
          int dp_r = at_r ? dp[at_r] : 0;
          int sub_r = at_r ? sub[at_r] : 0;
          int isub_l = iat_l ? sub[iat_l] : 0;
          int isub_r = iat_r ? sub[iat_r] : 0;
          dp[at] = add(add(dp_l, dp_r), add(mul(sub_l, isub_r), mul(sub_r, isub_l)));
        }
      }
    }
    // debug(dp[at]);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n >> x;

  vector<ll> a(n);
  for (ll &i : a) cin >> i;

  if (x == 0) {
    ll p2 = 1;
    for (int i = 1; i <= n; i++) {
      p2 = p2 * 2 % MOD;
    }
    cout << (p2 - 1) % MOD << "\n";
    return 0;
  }

  trie_sz = 1;
  for (ll i : a) insert(i);

  init();
  calc_dp();

  cout << add(dp[1], MOD - 1) << "\n";

  return 0;
}