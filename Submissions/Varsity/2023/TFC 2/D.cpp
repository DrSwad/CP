#include <bits/stdc++.h>
using namespace std;

const int N = 2e5;

vector<int> primes;

void sieve() {
  vector<bool> is_prime(N + 1, true);
  for (int p = 2; p <= N; p++) {
    if (is_prime[p]) {
      primes.push_back(p);
      for (int q = 2 * p; q <= N; q += p) {
        is_prime[q] = false;
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  sieve();

  int n, m;
  cin >> n >> m;

  vector grid(n, vector(m, 0));
  for (auto &row : grid) {
    for (int &cell : row) {
      cin >> cell;
      cell = *lower_bound(primes.begin(), primes.end(), cell) - cell;
    }
  }

  int ans = INT_MAX;
  for (int i = 0; i < n; i++) {
    int cur = 0;
    for (int j = 0; j < m; j++) {
      cur += grid[i][j];
    }
    ans = min(ans, cur);
  }
  for (int j = 0; j < m; j++) {
    int cur = 0;
    for (int i = 0; i < n; i++) {
      cur += grid[i][j];
    }
    ans = min(ans, cur);
  }

  cout << ans << "\n";

  return 0;
}