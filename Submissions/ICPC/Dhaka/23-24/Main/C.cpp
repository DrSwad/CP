#include <bits/stdc++.h>

using namespace std;

const int N = 100100;

bool good[N];
int tests, n, t[N << 1];

void update(int p, int v) {
  for (p += n + 1, t[p] = max(t[p], v); p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]);
}

int query(int l, int r) {
  int res = 0;
  for (l += n + 1, r += n + 1; l < r; l >>= 1, r >>= 1) {
    if (l & 1) res = max(res, t[l++]);
    if (r & 1) res = max(res, t[--r]);
  }
  return res;
}

int main() {
  cin >> tests;
  while (tests--) {
    scanf("%d", &n);
    for (int i = 0; i <= n; ++i) good[i] = false;
    for (int i = 0; i < n; ++i) {
      int x; scanf("%d", &x); good[x] = true;
    }
    for (int i = 0; i <= 2 * (n + 1); ++i) t[i] = 0;
    int ans = 1;
    for (int i = n; i >= 1; --i) {
      for (int j = i; j <= n; j += i) if (good[j]) {
          int h = j / i, here = 1 + query(h + 1, n + 1);
          update(h, here), ans = max(ans, here);
        }
    }
    printf("%d\n", ans);
  }
  return 0;
}