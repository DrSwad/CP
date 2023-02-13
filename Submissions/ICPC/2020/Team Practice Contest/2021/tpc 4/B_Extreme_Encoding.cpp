#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    int n;
    scanf("%d", &n);

    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
      long long num;
      scanf("%lld", &num);
      a[i] = num % (1 << 16);
      b[i] = num >> 16;
    }

    printf("Case %d:\n", cs);

    for (int i = 0; i < n; i++) {
      if (i) printf(" ");
      printf("%d", a[i]);
    }
    puts("");

    for (int i = 0; i < n; i++) {
      if (i) printf(" ");
      printf("%d", b[i]);
    }
    puts("");
  }

  return 0;
}