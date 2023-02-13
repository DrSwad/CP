#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll simulate(int n, vector<ll> &v, vector<int> &remOrder) {
  ll ret = 0;
  int mask = (1 << n) - 1;

  for (int remAt : remOrder) {
    mask &= ~(1 << remAt);
    ll add = 1;
    int upMask = mask >> (remAt + 1);
    if (upMask) add *= v[__builtin_ctz(upMask) + remAt + 1];
    int downMask = remAt == 0 ? 0 : (mask & ((1 << remAt) - 1));
    if (downMask) add *= v[31 - __builtin_clz(downMask)];
    ret += add;
  }

  return ret;
}

int main() {
  int n;
  while (cin >> n) {
    vector<ll> v(n);
    for (int i = 0; i < n; i++) { scanf("%lld", &v[i]); }

    ll ans = 0;
    vector<int> remOrder(n);
    iota(remOrder.begin(), remOrder.end(), 0);

    do {
      ans = max(ans, simulate(n, v, remOrder));
    } while (next_permutation(remOrder.begin(), remOrder.end()));

    cout << ans - 1 << endl;
  }

  return 0;
}