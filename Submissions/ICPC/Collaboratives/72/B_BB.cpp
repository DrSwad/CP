#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll a0 = 960002411612632915ll;
const ll mod = (ll)1e18 + 31;
const int root = 42;
const int N = 1e6;

ll add(ll a, ll b, ll m = mod) {
  ll c = a + b;
  return c < m ? c : c - m;
}

ll mul(ll a, ll b, ll m = mod) {
  return (__int128)a * b % m;
}

ll binExp(ll a, ll e, ll m = mod) {
  ll ret = 1 % m;
  while (e) {
    if (e & 1) ret = mul(ret, a, m);
    a = mul(a, a, m), e >>= 1;
  }
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  // for (int i = 1; ; i++) {
  //   debug(i);
  //   ll at = i;
  //   for (int i = 1; i <= N; i++) {
  //     at = binExp(root, at, mod);
  //   }
  //   if (at == a0) {
  //     break;
  //   }
  // }

  int n;
  cin >> n;

  ll at = 300;
  n = N - n;

  while (n--) {
    at = binExp(root, at, mod);
  }

  cout << at << "\n";

  return 0;
}