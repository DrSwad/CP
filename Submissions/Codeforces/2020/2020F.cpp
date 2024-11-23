#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int tt;
  cin >> tt;

  while (tt--) {
    int n, k, d;
    cin >> n >> k >> d;

    vector<int> v;
    for (int i = 1; i * i <= n; i++) v.push_back(i);
    for (int i = v.size() - 1; i >= 0; i--) {
      if (v[i] == n / v[i]) continue;
      v.push_back(n / v[i]);
    }

    int sq = sqrt(n);
    auto get_i =
      [&](int x) {
        if (x <= sq) return x - 1;
        return (int)v.size() - n / x;
      };

    vector<int> pi = v;
    {
      int primes_found = 0;
      for (int p = 2; p * p <= n; p++) {
        if (pi[get_i(p)] != pi[get_i(p - 1)]) {
          primes_found++;
          for (int i = v.size() - 1; i >= 0; i--) {
            if (v[i] < p * p) break;
            pi[i] -= pi[get_i(v[i] / p)] - primes_found;
          }
        }
      }
      for (int &i : pi) i--;
    }
  }

  return 0;
}