#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int B = 61;
vector<ll> basis(B);

void insert(ll x) {
  for (int i = 0; i < B; i++) {
    if (x & (1LL << i)) {
      if (!basis[i]) {
        basis[i] = x;
        return;
      }
      x ^= basis[i];
    }
  }
}

int main() {
  int n;
  scanf("%d", &n);

  ll tot = 0;
  for (int i = 0; i < n; i++) {
    ll x;
    scanf("%lld", &x);
    insert(x);
    tot ^= x;
  }

  ll ans = tot + 1;
  for (int i = 1; i < B; i++) {
    ll cur = (1LL << i) - 1;
    bool poss = true;

    for (int b = 0; b <= i; b++) {
      if (cur & (1LL << b)) {
        if (!basis[b]) {
          poss = false;
          break;
        }
        cur ^= basis[b];
      }
    }

    if (poss) {
      ans = max(ans, tot ^ ((1ll << (i + 1)) - 1));
    }
  }

  printf("%lld\n", ans);

  return 0;
}