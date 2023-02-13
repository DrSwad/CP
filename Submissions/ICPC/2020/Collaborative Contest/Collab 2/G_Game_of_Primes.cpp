#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

bool isPrime[N];
vector<int> primes;

void sieve() {
  fill(isPrime, isPrime + N, true);
  isPrime[1] = false;

  for (int p = 2; p < N; p++) {
    if (isPrime[p]) {
      primes.push_back(p);
      for (long long q = 1ll * p * p; q < N; q += p) { isPrime[q] = false; }
    }
  }
}

bool diffs[N];

bool check(int x, int y, int k) {
  if (x == k) return false;
  if (y == k) return false;

  for (int i = 0; i < max(x, y); i++) diffs[i] = false;
  for (int p : primes) {
    if (p <= k) continue;
    if (p > x) break;
    diffs[x - p] = true;
  }

  for (int p : primes) {
    if (p <= k) continue;
    if (p > y) break;
    if (diffs[y - p]) return true;
  }

  return false;
}

bool solve(int x, int y, int k) {
  if (x == k or y == k) return true;
  if (isPrime[x] and isPrime[y]) return false;
  if (x - 1 == k or y - 1 == k) return true;

  if (x % 2 != y % 2) return true;
  if (check(x, y, k)) return false;
  if (check(x - 2, y, k) and check(x, y - 2, k)) return false;
  return true;
}

int main() {
  sieve();

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    int x, y, k, w;
    scanf("%d %d %d %d", &x, &y, &k, &w);

    bool res;
    if (w == 1) res = solve(x, y, k);
    else {
      if (x == k or y == k) res = true;
      else if (isPrime[x] and isPrime[y])
        res = false;
      else {
        res = true;
        if (res == true and x > k) res = solve(x - 1, y, k);
        if (res == true and y > k) res = solve(x, y - 1, k);
      }
    }

    printf("Case %d: %s\n", cs, res ? "Bob" : "Alice");
  }

  return 0;
}
