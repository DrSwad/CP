#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 5;
const ll MX = 1e18;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
struct chash {
  const int RANDOM = (long long)(make_unique<char>().get())
                     ^ chrono::high_resolution_clock::now()
                     .time_since_epoch()
                     .count();
  static unsigned long long hash_f(unsigned long long x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  static unsigned hash_combine(unsigned a, unsigned b) {
    return a * 31 + b;
  }
  int operator()(int x) const { return hash_f(x) ^ RANDOM; }
  int operator()(pair<int, int> x) const {
    return hash_combine(x.first, x.second) ^ RANDOM;
  }
};

gp_hash_table<ll, int, chash> vis;

bool solve(ll n) {
  ll maybe_k = sqrtl(n);
  ll sqrt_mx = sqrtl(MX);
  for (ll k = max(2ll, maybe_k - 10); k <= maybe_k + 10; k++) {
    if (k > sqrt_mx) break;
    if (k * k + k + 1 == n) return true;
  }
  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int k = 2; k < N; k++) {
    ll sum = 1ll * k * k + k + 1;
    ll term = 1ll * k * k;
    while (sum < MX) {
      vis[sum] = true;
      if (MX / k < term) break;
      term *= k;
      sum += term;
    }
  }

  for (int cs = 1; cs <= t; cs++) {
    ll n;
    cin >> n;
    if (vis.find(n) != vis.end() or solve(n)) cout << "YES\n";
    else cout << "NO\n";
  }

  return 0;
}