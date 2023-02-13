#include <bits/stdc++.h>
using namespace std;

int brute(int n) {
  for (int diff = 1; diff < n; diff++) {
    for (int st = 2; st + diff < n; st++) {
      int mid = diff - 1;
      for (int mask = 0; mask < 1 << mid; mask++) {
        int sum = st + (st + diff);
        for (int i = 0; i < mid; i++) {
          if (mask & 1 << i) sum += st + 1 + i;
        }
        if (sum != n) continue;
        if (gcd(st, st + diff) != 1) continue;
        bool flag = false;
        for (int i = 0; i < mid; i++) {
          if (mask & 1 << i) {
            if (gcd(st, st + 1 + i) != 1) flag = true;
          }
        }
        if (flag) continue;
        for (int i = 0; i < mid; i++) {
          if (mask & 1 << i) {
            if (gcd(st + diff, st + 1 + i) != 1) flag = true;
          }
        }
        if (flag) continue;
        for (int i = 0; i < mid; i++) {
          for (int j = i + 1; j < mid; j++) {
            if (gcd(st + i + 1, st + j + 1) != 1) flag = true;
          }
        }
        return diff;
      }
    }
  }
  return -1;
}

int main() {
  // for (int x = 5; x <= 100; x++) {
  //   if (x % 2 == 0) debug() << name(x) name(brute(x));
  // }

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    printf("Case #%d: ", cs);

    int x;
    scanf("%d", &x);

    if (x & 1) {
      puts("1");
      continue;
    }

    int ans = -1;
    for (int diff = 2; diff <= 4 and ans == -1; diff++) {
      for (int mask = 0; mask < 1 << (diff - 1) and ans == -1;
           mask++) {
        int sum = diff;
        for (int i = 0; i < diff - 1; i++) {
          if (mask & 1 << i) sum += i + 1;
        }
        int tot = __builtin_popcount(mask) + 2;

        if (sum > x or (x - sum) % tot != 0) continue;
        int a = (x - sum) / tot;
        if (a <= 1) continue;

        if (gcd(a, a + diff) != 1) continue;
        bool flag = false;
        for (int i = 0; i < diff - 1; i++) {
          if (mask & 1 << i) {
            if (gcd(a, i + 1) != 1) flag = true;
          }
        }
        if (flag) continue;
        for (int i = 0; i < diff - 1; i++) {
          if (mask & 1 << i) {
            if (gcd(a + diff, a + i + 1) != 1) flag = true;
          }
        }
        if (flag) continue;
        for (int i = 0; i < diff - 1; i++) {
          if (mask & 1 << i) {
            for (int j = i + 1; j < diff - 1; j++) {
              if (mask & 1 << j) {
                if (gcd(a + i + 1, a + j + 1) != 1) flag = true;
              }
            }
          }
        }
        if (flag) continue;
        if (ans == -1) ans = diff;
      }
    }

    printf("%d\n", ans);
  }

  return 0;
}