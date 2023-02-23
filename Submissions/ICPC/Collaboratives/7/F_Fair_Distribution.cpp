#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, m;
    scanf("%d %d", &n, &m);

    if (n > m) {
      printf("%d\n", n - m);
    } else {
      int mini = INT_MAX;
      int mid = sqrt(m + .5);

      for (int i = 1; i <= mid; i++) {
        int curr = 0;
        int u = (m + i - 1) / i * i;
        curr += u - m;
        int l = u / i;
        if (l > n) continue;
        curr += n - l;
        mini = min(mini, curr);
      }

      for (int i = 1; i <= min(n, mid); i++) {
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