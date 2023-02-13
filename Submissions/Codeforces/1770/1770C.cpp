#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 102;
const int NN = N * N;

vector<int> primes;

void sieve() {
  vector<bool> vis(NN + 1, false);
  for (int p = 2; p < NN; p++) {
    if (!vis[p]) {
      primes.push_back(p);
      for (int q = p; q < NN; q += p) {
        vis[q] = true;
      }
    }
  }
}

void test_case() {
  int n;
  cin >> n;

  vector<ll> a(n);
  for (ll &i : a) cin >> i;

  map<ll, bool> a_vis;
  for (ll i : a) {
    if (a_vis[i]) {
      cout << "NO\n";
      return;
    }
    a_vis[i] = true;
  }

  int nn = n * n;
  int np;
  vector<int> rem_vis1(nn, -1);
  vector<int> rem_vis2(nn, -1);

  for (np = 0; np < primes.size() and primes[np] <= nn; np++) {
    int p = primes[np];
    int bad_r = 0;

    for (ll i : a) {
      int r = i % p;
      if (rem_vis1[r] == np) {
        if (rem_vis2[r] != np) {
          bad_r++;
          rem_vis2[r] = np;
        }
      }
      else rem_vis1[r] = np;
    }

    if (bad_r == p) {
      cout << "NO\n";
      return;
    }
  }

  cout << "YES\n";
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