#include <bits/stdc++.h>
using namespace std;

const int N = 42;

long long dp[N][N][N][N];

void test_case() {
  memset(dp, -1, sizeof dp);

  int n, A, B;
  cin >> n >> A >> B;

  vector<int> pA(N), pB(N);
  pA[0] = 1, pB[0] = 1;
  for (int i = 1; i < N; i++) pA[i] = pA[i - 1] * 10 % A;
  for (int i = 1; i < N; i++) pB[i] = pB[i - 1] * 10 % B;

  string x;
  cin >> x;
  reverse(x.begin(), x.end());

  dp[0][0][0][0] = 0;
  for (int i = 0; i < n; i++) {
    for (int rA = 0; rA < A; rA++) {
      for (int rB = 0; rB < B; rB++) {
        for (int nA = 0; nA <= i; nA++) {
          if (~dp[i][rA][rB][nA]) {
            int nrA = (rA + (x[i] - '0') * pA[nA]) % A;
            int nB = i - nA;
            int nrB = (rB + (x[i] - '0') * pB[nB]) % B;
            dp[i + 1][rA][nrB][nA] = dp[i][rA][rB][nA] + (1ll << i);
            dp[i + 1][nrA][rB][nA + 1] = dp[i][rA][rB][nA];
          }
        }
      }
    }
  }

  int mn = -1;
  long long ans;
  for (int nA = 1; nA < n; nA++) {
    int nB = n - nA;
    if (~dp[n][0][0][nA]) {
      int curr = abs(nA - nB);
      if (mn == -1 or mn > curr) {
        mn = curr;
        ans = dp[n][0][0][nA];
      }
    }
  }

  cout << (mn == -1 ? "-1" : bitset<N>(ans).to_string('R', 'B').substr(N - n)) << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}