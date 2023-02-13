#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  scanf("%d", &n);

  vector<int> a(n);
  for (int &i: a) scanf("%d", &i);

  if (a[0] == 1) {
    printf("%d", n + 1);
    for (int i = 1; i <= n; i++) printf(" %d", i);
    puts("");
    return;
  } else if (a[n - 1] == 0) {
    for (int i = 1; i <= n; i++) printf("%d ", i);
    printf("%d", n + 1);
    puts("");
    return;
  } else {
    int at;
    for (at = 0; at < n - 1; at++) {
      if (a[at] == 0 and a[at + 1] == 1) break;
    }
    at++;

    if (at < n) {
      for (int i = 1; i <= at; i++) printf("%d ", i);
      printf("%d ", n + 1);
      for (int i = at + 1; i <= n; i++) printf(" %d", i);
      puts("");
      return;
    }
  }

  puts("-1");
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    test_case();
  }

  return 0;
}