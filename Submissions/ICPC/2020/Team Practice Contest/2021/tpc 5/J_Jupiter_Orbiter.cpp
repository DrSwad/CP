#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  int nw, nq, ns;
  scanf("%d %d %d", &nw, &nq, &ns);

  vector<int> sq(ns);
  for (int &i : sq) {
    scanf("%d", &i);
    i--;
  }

  vector<ll> szq(nq);
  for (ll &i : szq) {
    scanf("%lld", &i);
  }

  vector<ll> szw(nw), remw;
  vector<vector<ll>> genq(nw, vector<ll>(nq, 0)), remq;
  remw = szw;
  remq = genq;

  for (int atw = 0; atw < nw; atw++) {
    scanf("%lld", &szw[atw]);
    remw[atw] = szw[atw];

    for (int ats = 0; ats < ns; ats++) {
      ll gens;
      scanf("%lld", &gens);
      genq[atw][sq[ats]] += gens;
    }

    for (int atq = 0; atq < nq; atq++) {
      remq[atw][atq] = szq[atq];
    }
  }

  for (int atw = nw - 1; ~atw; atw--) {
    for (int atq = 0; atq < nq; atq++) {
      while (genq[atw][atq] > 0) {
        int fromw = -1;
        ll take = LLONG_MAX;
        ll ctake = LLONG_MAX;

        for (int _atw = atw; _atw < nw and remq[_atw][atq] > 0; _atw++) {
          ctake = min(ctake, remq[_atw][atq]);
          if (remw[_atw] > 0) {
            fromw = _atw;
            take = ctake;
          }
        }

        if (fromw == -1) break;

        take = min(take, min(genq[atw][atq], remw[fromw]));
        genq[atw][atq] -= take;
        remw[fromw] -= take;
        for (int _atw = atw; _atw <= fromw; _atw++) remq[_atw][atq] -= take;
      }

      if (genq[atw][atq] > 0) {
        puts("impossible");
        return 0;
      }
    }
  }

  puts("possible");

  return 0;
}