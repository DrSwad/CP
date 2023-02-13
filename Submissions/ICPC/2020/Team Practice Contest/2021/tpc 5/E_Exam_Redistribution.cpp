#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  scanf("%d", &n);

  vector<pair<int, int>> a(n);
  int sum = 0;

  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i].first);
    a[i].second = i + 1;
    sum += a[i].first;
  }

  sort(a.begin(), a.end(), greater<pair<int, int>>());

  if (a[0].first > sum - a[0].first) puts("impossible");
  else {
    for (int i = 0; i < n; i++) {
      if (i) printf(" ");
      printf("%d", a[i].second);
    }
    puts("");
  }

  return 0;
}