#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    scanf("%d", &n);

    int cnt = 0;
    for (int i = 0; i < 2 * n; i++) {
      int a;
      scanf("%d", &a);
      cnt += a & 1;
    }

    puts(cnt == n ? "Yes" : "No");
  }

  return 0;
}