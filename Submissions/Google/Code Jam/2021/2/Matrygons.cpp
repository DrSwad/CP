#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

vector<int> divs[N];
int dp[N];

void sieve() {
  for (int div = 2; div < N; div++) {
    for (int mul = div; mul < N; mul += div) {
      divs[mul].push_back(div);
    }
  }
}

void init() {
  dp[1] = dp[2] = 1;
  for (int i = 3; i < N; i++) {
    for (int div : divs[i - 1]) {
      dp[i] = max(dp[i], dp[(i - 1) / div] + 1);
    }
  }
}

int main() {
  sieve();
  init();

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    int n;
    scanf("%d", &n);

    int ans = 0;
    for (int div : divs[n]) {
      if (div > 2) {
        ans = max(ans, dp[n / div]);
      }
    }

    printf("Case #%d: %d\n", cs, ans);
  }

  return 0;
}