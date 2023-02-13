#include <bits/stdc++.h>
using namespace std;

// p(n) = sum((-1)^(k+1) * p(n - p_k)), k in Z, k != 0
// gf(p) = prod(1/(1-x^i)), i >= 1
// ans = coeff(gf(p) * prod(1-x^a_i), m)

typedef long long ll;
const int M = 3e5 + 5;
const int MOD = (int)1e9 + 7;

int partition_number[M];

void init() {
  partition_number[0] = 1;
  for (int n = 1; n < M; n++) {
    for (int k = 1, pentagonal_number = 0; ; k++) {
      pentagonal_number += 3 * k - 2;
      int nn = n - pentagonal_number;
      if (nn < 0) break;
      if (k & 1) {
        partition_number[n] += partition_number[nn];
        if (partition_number[n] >= MOD) partition_number[n] -= MOD;
        if (nn - k >= 0) {
          partition_number[n] += partition_number[nn - k];
          if (partition_number[n] >= MOD) partition_number[n] -= MOD;
        }
      }
      else {
        partition_number[n] -= partition_number[nn];
        if (partition_number[n] < 0) partition_number[n] += MOD;
        if (nn - k >= 0) {
          partition_number[n] -= partition_number[nn - k];
          if (partition_number[n] < 0) partition_number[n] += MOD;
        }
      }
    }
  }
}

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<int> p(partition_number, partition_number + m + 1);

  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    for (int j = m; j >= a; j--) {
      p[j] -= p[j - a];
      if (p[j] < 0) p[j] += MOD;
    }
  }

  cout << p[m] << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}