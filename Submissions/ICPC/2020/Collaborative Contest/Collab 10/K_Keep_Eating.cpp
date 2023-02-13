#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, k;
  scanf("%d %d", &n, &k);

  long long sum = 0;
  while (n--) {
    int a;
    scanf("%d", &a);
    sum += a;
  }

  printf("%lld\n", sum < k ? 0 : (sum - (k + 1) / 2));

  return 0;
}