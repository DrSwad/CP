#include <bits/stdc++.h>
using namespace std;

const int N = 5e3;
const int mod = 1e9 + 7;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

int C[N][N];

void init() {
  for (int n = 0; n < N; n++) {
    C[n][0] = C[n][n] = 1;
    for (int k = 1; k < n; k++) {
      C[n][k] = add(C[n - 1][k], C[n - 1][k - 1]);
    }
  }
}

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<int> c(n);
  for (int &i : c) cin >> i, i--;

  vector<int> max_blocks(n, 0);
  for (int i = 0; i < n; i++) {
    int got = 0, prv;
    for (prv = i; prv >= 0; prv--) {
      if (c[prv] == c[i]) got++;
      if (got >= k) {
        max_blocks[i] = max(max_blocks[i], 1 + (prv > 0 ? max_blocks[prv - 1] : 0));
      }
    }
  }

  vector<int> ways(n);
  for (int i = 0; i < n; i++) {
    int got = 0, prv;
    for (prv = i - 1; prv >= -1; prv--) {
      if (c[prv + 1] == c[i]) got++;
      if ((prv == -1 and max_blocks[i] <= 1) or (prv >= 0 and max_blocks[i] <= max_blocks[prv] + 1)) {
        ways[i] = add(ways[i], mul(C[got - 1][k - 1], prv >= 0 ? ways[prv] : 1));
      }
    }
  }

  int mx_blocks = *max_element(max_blocks.begin(), max_blocks.end());
  int ans = mx_blocks == 0;
  for (int i = 0; i < n; i++) {
    if (max_blocks[i] == mx_blocks) {
      ans = add(ans, ways[i]);
    }
  }
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}