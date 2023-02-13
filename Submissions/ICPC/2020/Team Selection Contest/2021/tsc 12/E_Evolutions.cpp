#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int S = 1e6 + 5;
const int SQRTS = 1e3 + 5;
const int MAGIC = 14;
const int CHECK_DIFF = 5;

inline bool check(ll a, int p, int q, int terms, int s) {
  if (a <= 0) { return false; }
  ll sum = a;
  terms--;

  while (terms--) {
    if (a % q != 0) { return false; }
    (a /= q) *= p;
    sum += a;
    if (sum > s) { return false; }
  }

  return sum == s;
}

int main() {
  vector<int> toCheck;
  for (long long i = 2; i < S; i++) {
    long long num = i * i;
    while (true) {
      num *= i;
      long long q = (num - 1) / (i - 1);
      if (q >= S) { break; }
      toCheck.push_back(q);
    }
  }

  vector<vector<pair<int, int>>> rToCheck(MAGIC);
  for (int i = 4; i < MAGIC; i++) {
    int up = 1;
    while (pow(up, i - 1) < S) { up++; }
    for (int q = 2; q < up; q++) {
      for (int p = q + 1; p < up; p++) {
        if (gcd(p, q) == 1) rToCheck[i].emplace_back(p, q);
      }
    }
  }

  vector<int> sumFreq(S, 0);
  for (ll q = 2; q < SQRTS; q++) {
    for (ll p = q + 1; p < SQRTS; p++) {
      if (gcd(p, q) == 1) {
        ll sum = p * p + p * q + q * q;
        if (sum < S) sumFreq[sum]++;
      }
    }
  }

  int t;
  cin >> t;

  while (t--) {
    int s;
    scanf("%d", &s);

    int ans = 1 + (s - 1) / 2;
    for (int d : toCheck) ans += s % d == 0;

    for (int d = 1; d * d <= s; d++) {
      if (s % d == 0) {
        ans += sumFreq[s / d];
        if (d != s / d) { ans += sumFreq[d]; }
      }
    }

    for (int i = 4; i < MAGIC; i++) {
      for (auto [p, q] : rToCheck[i]) {
        double r = (double)p / q;
        double rat = (pow(r, i) - 1) / (r - 1);
        int a = s / rat;
        for (int j = -CHECK_DIFF; j < CHECK_DIFF; j++) {
          ans += check(a + j, p, q, i, s);
        }
      }
    }

    printf("%d", ans);
    if (t) { printf(" "); }
  }

  return 0;
}