#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> divs;

pair<int, int> solveOdd() {
  for (int d : divs) {
    int terms = 2 * d - 1;
  }
  return {0, 0};
}

pair<int, int> solveEven() {
  for (int d : divs) {
    int sum = n / d;
    if (sum % 2 != 1) continue;
    int mid = (sum + 1) / 2;
    int st = mid - d;
    if (st > 0) return {st, 2 * d};
  }
  return {0, 0};
}

void solve() {
  scanf("%d", &n);

  divs.clear();
  for (long long d = 1; d * d <= n; d++) {
    if (n % d == 0) {
      divs.push_back(d);
      if (d * d != n) divs.push_back(n / d);
    }
  }

  pair<int, int> solOdd = solveOdd();
  pair<int, int> solEven = solveEven();

  pair<int, int> sol;
  if (!solOdd.first) sol = solEven;
  else if (!solEven.first) sol = solOdd;
  else if (solOdd.first < solEven.first) sol = solOdd;
  else sol = solEven;

  if (!sol.first) puts("IMPOSSIBLE");
  else {
    printf("%d =", n);
    for (int i = 0; i < sol.first; i++) {
      printf(" %d", sol.second + i);
    }
    puts("");
  }
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}