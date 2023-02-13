#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  int n;
  ll D;

  while (cin >> n >> D) {
    vector<ll> a(n);
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);

    sort(a.begin(), a.end());

    ll delR = -1;
    ll ans = a.back();

    map<ll, int> distFreq;
    for (int L = 0, R = 0; L < n; L++) {
      if (L > 0) {
        distFreq[a[L] - a[L - 1]]--;
        if (distFreq[a[L] - a[L - 1]] == 0) {
          distFreq.erase(a[L] - a[L - 1]);
        }
      }

      R = max(R, L + 1);
      while (R < n and a[R] - a[L] <= D) {
        distFreq[a[R] - a[R - 1]]++;
        R++;
      }
      if (R <= L + 3) continue;
      debug() << name(L) name(R);

      ll maxDist = a[R - 1] - a[L];
      ll minDist = distFreq.begin()->first;
      if (maxDist % minDist == 0) {
        debug() << name(maxDist) name(minDist);
        ll delL = max(delR, a[L] - 1);
        ans -= a[R - 1] - delR;
        delR = a[R - 1];
      }
    }

    printf("%lld\n", ans);
  }

  return 0;
}