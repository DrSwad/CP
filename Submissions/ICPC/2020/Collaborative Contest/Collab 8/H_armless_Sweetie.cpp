#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    scanf("%d", &n);

    vector<int> a(n);
    for (int &i : a) scanf("%d", &i);

    if (n == 1) {
      puts("0");
      continue;
    }

    a.push_back(0);
    n++;
    int cnt = 0;

    bool flag = false;
    for (int i = 0, prv = 0, freq = 0; i < n; i++) {
      if (a[i] != prv) {
        if (prv == -1 and freq % 2 == 1) {
          cnt++;
          if (i == freq or i == n - 1) flag = true;
        }
        freq = 1;
        prv = a[i];
      }
      else freq++;
    }

    printf("%d\n", n - 2 - (cnt + 1) / 2 * 2 - 2 * (cnt % 2 == 1 and !flag));
  }

  return 0;
}