#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 5005;
const int M = 1000010;
const int INF = 1e8 + 69;

int t, cs, n, k, a[N], f[M];

int main() {
  for (int i = 0; i < M; ++i) f[i] = INF;
  cin >> t;
  while (t--) {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; ++i) {
      scanf("%d", a + i);
    }
    int ans = INT_MAX;
    for (int i = 2; i <= n; ++i) {
      int cur = 0;
      for (int j = i - 1; j >= 1; --j) {
        cur += a[j];
        if (cur > k) break;
        f[cur] = min(f[cur], i - j);
      }
      cur = 0;
      for (int j = i; j <= n; ++j) {
        cur += a[j];
        if (cur > k) break;
        ans = min(ans, j - i + 1 + f[k - cur]);
      }
    }
    for (int i = 1; i <= n; ++i) {
      int cur = 0;
      for (int j = i; j <= n; ++j) {
        cur += a[j];
        if (cur > k) break;
        if (cur == k) ans = min(ans, j - i + 1);
        f[cur] = INF;
      }
    }
    if (ans > INF / 2) ans = -1;
    printf("Case #%d: %d\n", ++cs, ans);
  }
  return 0;
}

