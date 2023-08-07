#include <bits/stdc++.h>
using namespace std;

int binExp(int a, int e, int m) {
  int ret = 1;
  while (e) {
    if (e & 1) ret = 1ll * ret * a % m;
    a = 1ll * a * a % m, e >>= 1;
  }
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<int> is_allowed(m, true);
  while (n--) {
    int v;
    cin >> v;
    is_allowed[v] = false;
  }

  vector<vector<int>> chain(m + 1);
  for (int i = 0; i < m; i++) {
    if (is_allowed[i]) {
      int g = i == 0 ? m : gcd(i, m);
      chain[g].push_back(i);
    }
  }

  vector<int> max_chain(m + 1), chain_next(m + 1);
  for (int g = m; g >= 1; g--) {
    max_chain[g] = chain[g].size();
    chain_next[g] = m + 1;
    for (int mul = 2 * g; mul <= m; mul += g) {
      if (chain[g].size() + max_chain[mul] > max_chain[g]) {
        max_chain[g] = chain[g].size() + max_chain[mul];
        chain_next[g] = mul;
      }
    }
  }

  vector<int> phi(m + 1);
  {
    vector<int> sp(m + 1, -1), spf(m + 1);
    phi[1] = 1;
    for (int i = 2; i <= m; i++) {
      if (sp[i] == -1) {
        sp[i] = i;
        for (int j = 2 * i; j <= m; j += i) {
          if (sp[j] == -1) {
            sp[j] = i;
          }
        }
      }
      spf[i] = sp[i] * (sp[i / sp[i]] == sp[i] ? spf[i / sp[i]] : 1);
      if (spf[i] == i) phi[i] = i - i / sp[i];
      else phi[i] = phi[spf[i]] * phi[i / spf[i]];
    }
  }

  function<int(int, int)> inv =
    [&](int a, int mod) {
      assert(1 <= mod);
      assert(gcd(a, mod) == 1);
      assert(mod <= m);
      if (mod == 1) return 1;
      a %= mod;
      return binExp(a, phi[mod] - 1, mod);
    };

  int g = max_element(max_chain.begin(), max_chain.end()) - max_chain.begin();
  vector<int> ans;
  int prv_gcd = 1;
  int prv_rem = 1;

  while (g <= m) {
    for (int rem : chain[g]) {
      int mul = g / prv_gcd;

      int prv_cop = prv_rem / prv_gcd;
      int cop = rem / g;
      mul = 1ll * mul * cop % m * inv(prv_cop, m / g) % m;
      ans.push_back(mul);

      prv_rem = rem;
      prv_gcd = g;
    }

    g = chain_next[g];
  }

  cout << ans.size() << "\n";
  for (int i = 0; i < ans.size(); i++) {
    if (i) cout << " ";
    cout << ans[i];
  }
  cout << "\n";

  return 0;
}