#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int mod[2] = {941, 10627};
int inv[2];

ll binExp(ll a, ll e, ll m) {
  if (a >= m) a %= m;
  if (e == -1) e = m - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % m;
    a = a * a % m, e >>= 1;
  }
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  inv[0] = binExp(mod[0], -1, mod[1]);
  inv[1] = binExp(mod[1], -1, mod[0]);

  vector<int> ns;
  {
    int n;
    while (cin >> n, n != 0) {
      ns.push_back(n);
    }
  }
  if (ns.empty()) return 0;

  int mx_n = *max_element(ns.begin(), ns.end());

  vector<int> sp(mx_n + 1, -1);
  for (int p = 2; p <= mx_n; p++) {
    if (sp[p] != -1) continue;
    sp[p] = p;
    for (int q = 2 * p; q <= mx_n; q += p) {
      if (sp[q] == -1) {
        sp[q] = p;
      }
    }
  }

  vector<vector<int>> queries_at(mx_n + 1);
  for (int i = 0; i < ns.size(); i++) {
    queries_at[ns[i]].push_back(i);
  }

  vector<int> exp(mx_n + 1, 0);
  vector<int> mod_exp_cnt(2, 0);
  vector<int> ans(ns.size());
  vector<ll> cur_ans_mod(2, 1ll);

  for (int n = 1; n <= mx_n; n++) {
    int at_n = n;
    while (at_n > 1) {
      int p = sp[at_n];
      int cnt = 0;
      while (at_n % p == 0) {
        cnt++;
        at_n /= p;
      }

      for (int it = 0; it < 2; it++) {
        ll div = 1ll * (exp[p] + 1) * (exp[p] + 2) / 2;
        while (div % mod[it] == 0) {
          div /= mod[it];
          mod_exp_cnt[it]--;
        }
        assert(mod_exp_cnt[it] >= 0);
        (cur_ans_mod[it] *= binExp(div, -1, mod[it])) %= mod[it];
        ll mul = 1ll * ((exp[p] + cnt) + 1) * ((exp[p] + cnt) + 2) / 2;
        while (mul % mod[it] == 0) {
          mul /= mod[it];
          mod_exp_cnt[it]++;
        }
        (cur_ans_mod[it] *= mul % mod[it]) %= mod[it];
      }
      exp[p] += cnt;
    }

    int cur_ans_mod_0 = mod_exp_cnt[0] ? 0 : cur_ans_mod[0];
    int cur_ans_mod_1 = mod_exp_cnt[1] ? 0 : cur_ans_mod[1];
    int cur_ans =
      (mod[0] * (cur_ans_mod_1 * inv[0] % mod[1]) +
       mod[1] * (cur_ans_mod_0 * inv[1] % mod[0])) % (mod[0] * mod[1]);

    for (int i : queries_at[n]) {
      ans[i] = cur_ans;
    }
  }

  for (int cur_ans : ans) cout << cur_ans << "\n";

  return 0;
}