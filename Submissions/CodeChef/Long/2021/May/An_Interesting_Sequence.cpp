#include <bits/stdc++.h>
using namespace std;

const int N = 4e6 + 5;

bool is_prime[N];
int mu[N];
int dp[N];
long long ans[N];

void init() {
  fill(begin(is_prime), end(is_prime), true);
  is_prime[1] = false;
  fill(begin(mu), end(mu), 1);
  dp[1] = 1;
  ans[1] = 1;

  for (int at = 1; at < N; at++) {
    for (int mul = at; mul < N; mul += at) {
      int q = mul / at;

      if (is_prime[at]) {
        if (mul > at) is_prime[mul] = false;

        if (mu[mul]) {
          mu[mul] = q % at == 0 ? 0 : -mu[mul];
        }
      }

      if (mul > 1) {
        dp[mul] += mu[at] * ((mul / at) + 1) / 2;
        if (at >= q) {
          ans[mul] += at * 1ll * dp[q];
          if (at != q) ans[mul] += q * 1ll * dp[at];
        }
      }
    }
  }
}

int main() {
  init();

  int t;
  cin >> t;

  while (t--) {
    int n;
    scanf("%d", &n);
    printf("%lld\n", ans[4 * n + 1] - 1);
  }

  return 0;
}