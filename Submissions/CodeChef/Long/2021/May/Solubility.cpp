#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  while (t--) {
    int x, a, b;
    scanf("%d %d %d", &x, &a, &b);
    printf("%d\n", (a + (100 - x) * b) * 10);
  }

  return 0;
}