// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt") // use avx for older judges

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int D = 18;
const int L = 1e4, R = 1e5;
const int TRIES = 10;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll nCk(int n, int k) {
  if (k<0 or k> n) return 0;
  ll ret = 1;
  for (int i = 1; i <= n; i++) ret *= i;
  for (int i = 1; i <= k; i++) ret /= i;
  for (int i = 1; i <= n - k; i++) ret /= i;
  return ret;
}

vector<int> sieve(int l, int r) {
  vector<bool> vis(r + 1, false);
  vector<int> primes;
  for (int i = 2; i <= r; i++) {
    if (!vis[i]) {
      primes.push_back(i);
      for (int j = i; j <= r; j += i) {
        vis[j] = true;
      }
    }
  }
  return primes;
}

void test_case() {
  vector<int> primes = sieve(L, R);
  uniform_int_distribution<int> uid(0, (int)primes.size() - 1);
  auto gen = bind(uid, rng);

  vector<ll> p10(1, 1);
  for (int i = 1; i <= D; i++) {
    p10.push_back(p10.back() * 10);
  }

  ll n;
  cin >> n;

  function<void(const vector<vector<ll>>&, const vector<int>&)> check_solution = [&](const vector<vector<ll>> &w, const vector<int> &d) {
    ll sum = 0;
    for (int i = 0; i < d.size(); i++) {
      sum += w[i][d[i]];
      if (sum > n) return;
    }
    if (sum == n) {
      bool found_non_zero = false;
      for (int i = (int)d.size() - 1; i >= 0; i--) {
        if (d[i] != 0) found_non_zero = true;
        if (found_non_zero) cout << d[i];
      }
      cout << "\n";
      exit(EXIT_SUCCESS);
    }
  };

  function<int(void)> pick_hash_mod = [&]() { return primes[gen()]; };

  function<void(int, int, const vector<vector<ll>>&)> try_mod = [&](int mod, int d, const vector<vector<ll>> &w) {
    vector<vector<int>> hash_path(d + 1, vector<int>(mod, -1));
    hash_path[0][0] = 0;

    for (int i = 1; i <= d; i++) {
      for (int j = i < d ? 0 : 1; j < w[i - 1].size(); j++) {
        for (int m = 0; m < mod; m++) {
          if (hash_path[i - 1][m] != -1) {
            ll new_m = (m + w[i - 1][j]) % mod;
            if (hash_path[i][new_m] == -1) {
              hash_path[i][new_m] = j;
            }
          }
        }
      }
    }

    int need_hash = n % mod;
    if (hash_path[d][need_hash] == -1) return;

    vector<int> picked(d);

    for (int i = d; i >= 1; i--) {
      picked[i - 1] = hash_path[i][need_hash];
      need_hash = (need_hash - w[i - 1][picked[i - 1]] % mod + mod) % mod;
    }

    check_solution(w, picked);
  };

  function<void(int)> try_num_digits = [&](int d) {
    vector<vector<ll>> w(d, vector<ll>(1, 0));

    for (int i = 0; i < d; i++) {
      ll sum = 0;
      bool flag = true;
      for (int k = 0; k <= i; k++) {
        __int128 term = p10[k] * nCk(i, k);
        sum += term;
        if (term > n or sum > n) {
          flag = false;
          break;
        }
      }
      for (int c = 1; c <= 9; c++) {
        ll mul = (1ll << (d - 1 - i)) * c;
        if (sum * mul > n) break;
        w[i].push_back(sum * mul);
      }
    }

    int tries = TRIES;
    while (tries--) {
      try_mod(pick_hash_mod(), d, w);
    }
  };

  for (int d = 1; d <= D; d++) {
    try_num_digits(d);
  }

  cout << "NIE\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}