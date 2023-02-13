#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int SQRT_A = 4e4;
const int MOD = 998244353;

vector<int> primes;

void sieve() {
  vector<bool> vis(SQRT_A, false);
  for (int p = 2; p < SQRT_A; p++) {
    if (!vis[p]) {
      primes.push_back(p);
      for (int q = 2 * p; q < SQRT_A; q += p) {
        vis[q] = true;
      }
    }
  }
}

vector<int> prime_facts(int n) {
  vector<int> ret;
  for (int p : primes) {
    if (n % p == 0) {
      ret.push_back(p);
      while (n % p == 0) n /= p;
    }
  }
  if (n > 1) ret.push_back(n);
  return ret;
}

int no_prime_div(ll max_num, vector<int> &primes) {
  int sz = primes.size();
  ll ret = 0;
  for (int mask = 0; mask < 1 << sz; mask++) {
    int cnt = 0;
    ll mul = 1;
    for (int i = 0; i < sz; i++) {
      if (mask >> i & 1) {
        mul *= primes[i];
        if (mul > max_num) {
          mul = 0;
          break;
        }
        cnt++;
      }
    }
    if (mul == 0) continue;
    ret += ((cnt & 1) ? -1 : 1) * (max_num / mul);
  }
  return ret;
}

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  for (int i = 1; i < n; i++) {
    if (a[i - 1] % a[i] != 0) {
      cout << "0\n";
      return;
    }
  }

  ll ans = 1;
  vector<int> all_prime_facts = prime_facts(a[0]);

  for (int i = 1; i < n; i++) {
    if (a[i] == a[i - 1]) {
      ans = 1ll * ans * (m / a[i]) % MOD;
    }
    else {
      vector<int> prime_facts;
      for (int p : all_prime_facts) {
        if ((a[i - 1] / a[i]) % p == 0) {
          prime_facts.push_back(p);
        }
      }
      ans = 1ll * ans * no_prime_div(m / a[i], prime_facts) % MOD;
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  sieve();

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}