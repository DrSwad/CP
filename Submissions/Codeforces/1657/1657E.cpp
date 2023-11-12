#include <bits/stdc++.h>
using namespace std;

const int N = 250;
const int mod = 998244353;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

// dp[len][max_w] = solution to the problem when:
//                  there are (len + 1) nodes
//                  the largest weight of an edge is <= max_w
// 0 <= len <= n - 1
// 0 <= max_w <= k

// dp2[len][max_cnt][max_w] = solution to the problem when:
//                            there are (len + 1) nodes
//                            the largest weight of an edge is max_w
//                            there are exactly max_cnt edges from 1 of weight max_w
// 0 <= len <= n - 1
// 0 <= max_cnt <= len
// 0 <= max_w <= k

// dp2[len][cnt][w] = cnt > 1:
//                      ((n - 1) - (len - 1)) * dp2[len - 1][cnt - 1][w] / cnt * (k - (w - 1))**(len - 1):
//                    else:
//                      ((n - 1) - (len - 1)) * dp[len - 1][w - 1] * w**(len - 1)

int n, k;
int inv[N];
int p[N + 1][N - 1];
int dp[N][N + 1];
int dp2[N][N][N + 1];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  inv[1] = 1;
  for (int i = 2; i < N; i++) inv[i] = mul(inv[mod % i], mod - mod / i);

  for (int w = 1; w <= N; w++) {
    p[w][0] = 1;
    for (int e = 1; e < N - 1; e++) {
      p[w][e] = mul(p[w][e - 1], w);
    }
  }

  cin >> n >> k;

  for (int w = 0; w <= k; w++) {
    dp[0][w] = 1;
  }

  for (int len = 1; len <= n - 1; len++) {
    for (int cnt = 1; cnt <= n - 1; cnt++) {
      for (int w = 1; w <= k; w++) {
        if (cnt == 1) {
          dp2[len][cnt][w] = mul(((n - 1) - (len - 1)), mul(dp[len - 1][w - 1], p[k - (w - 1)][len - 1]));
        }
        else {
          dp2[len][cnt][w] = mul((n - 1) - (len - 1), mul(dp2[len - 1][cnt - 1][w], mul(inv[cnt], p[k - (w - 1)][len - 1])));
        }

        dp[len][w] = add(dp[len][w], dp2[len][cnt][w]);
      }
    }

    for (int w = 1; w <= k; w++) {
      dp[len][w] = add(dp[len][w], dp[len][w - 1]);
    }
  }

  cout << dp[n - 1][k] << "\n";

  return 0;
}