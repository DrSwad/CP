#include <bits/stdc++.h> // asdf
using namespace std;

const int N = 505;

bool dp[2][N][N * N];

int inversions(vector<int> perm) {
  int ret = 0;
  int n = perm.size();
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      ret += perm[i] > perm[j];
    }
  }
  return ret;
}

bool is_involution(vector<int> perm) {
  int n = perm.size();
  for (int i = 0; i < n; i++) {
    if (perm[perm[i]] != i) return false;
  }
  return true;
}

bool add(bool &a, bool b) {
  return a = (a & 1) ^ (b & 1);
  // return a = a + b;
}

bool sub(bool &a, bool b) {
  return a = (a & 1) ^ (b & 1);
  // return a = a - b;
}

int brute(int n, int k) {
  vector<int> perm(n);
  iota(perm.begin(), perm.end(), 0);
  int ans = 0;
  do {
    ans += is_involution(perm) and inversions(perm) == k;
  } while (next_permutation(perm.begin(), perm.end()));
  return ans;
}

void init() {
  dp[0][0][0] = 1;
  dp[0][1][0] = 1;

  for (int k = 1; k < N * N; k++) {
    dp[1][0][k] = dp[0][0][k - 1];
    if (k >= 2) add(dp[1][0][k], dp[1][0][k - 2]);
  }

  for (int k = 1; k < N * N; k++) {
    dp[1][1][k] = dp[0][1][k - 1];
    if (k >= 2) add(dp[1][1][k], dp[1][1][k - 2]);
  }

  for (int n = 2; n < N; n++) {
    int mx_k = n * (n - 1) / 2;
    for (int k = 0; k < N * N; k++) {
      if (k > mx_k) dp[0][n][k] = 0;
      else {
        dp[0][n][k] = dp[0][n - 1][k];
        add(dp[0][n][k], dp[1][n - 2][k]);
        if (k >= 2 * (n - 1)) {
          sub(dp[0][n][k], dp[1][n - 2][k - 2 * (n - 1)]);
        }
      }

      if (k >= 1) {
        dp[1][n][k] = dp[0][n][k - 1];
        if (k >= 2) {
          add(dp[1][n][k], dp[1][n][k - 2]);
        }
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  int n, k;
  cin >> n >> k;

  cout << dp[0][n][k] << "\n";

/*   for (int n = 1; n <= 6; n++) {
    for (int k = 0; k <= 15; k++) {
      if (dp[0][n][k] != brute(n, k)) {
        debug(n, k);
        debug(dp[0][n][k], brute(n, k));
      }
    }
   } */

  return 0;
}