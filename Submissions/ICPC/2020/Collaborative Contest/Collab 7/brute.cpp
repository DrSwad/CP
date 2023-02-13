#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, m;
    scanf("%d %d", &n, &m);

    if (n > m) {
      printf("%d\n", min(m, n - m));
    } else {
      int mini = INT_MAX;

      for (int i = 1; i <= n; i++) {
        int curr = 0;
        curr += n - i;
        int u = (m + i - 1) / i * i;
        curr += u - m;
        mini = min(curr, mini);
      }

      printf("%d\n", mini);
    }
  }

  return 0;
}