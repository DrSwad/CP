#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll gcd(ll a, ll b) {
  if (a < b) swap(a, b);
  if (b == 0) return a;
  return gcd(b, a % b);
}

int main() {
  ll i, I, p, q;
  while ( scanf("%lld %lld %lld/%lld", &i, &I, &p, &q) ) {
    if (p == 0 and q == 0) break;

    ll n1 = abs( q * (I - 1) - p * (i - 1) );
    ll n2 = q;
    ll d1 = p;
    ll d2 = abs(p - q);
    ll g;


    g = gcd(n1, d1);
    n1 /= g, d1 /= g;
    g = gcd(n2, d1);
    n2 /= g, d1 /= g;
    g = gcd(n1, d2);
    n1 /= g, d2 /= g;
    g = gcd(n2, d2);
    n2 /= g, d2 /= g;

    printf( "%lld\n", n1 * n2 * (d1 * d2 == 1 ? 2 : 1) );
  }

  return 0;
}