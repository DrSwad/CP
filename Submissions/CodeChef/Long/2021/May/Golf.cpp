#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, x, k;
    scanf("%d %d %d", &n, &x, &k);
    printf("%s\n", x % k == 0 or (n + 1 - x) % k == 0 ? "YES" : "NO");
  }

  return 0;
}