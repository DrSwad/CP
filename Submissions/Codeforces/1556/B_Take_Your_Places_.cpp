#include <bits/stdc++.h>
using namespace std;

long long go(vector<int> a, int b) {
  int cnt = 0;
  long long ret = 0;

  for (int i = 0; i < a.size(); i++) {
    if (a[i] == b) {
      ret += abs(i - 2 * cnt);
      cnt++;
    }
  }

  return ret;
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    scanf("%d", &n);

    vector<int> a(n);
    for (int &i: a) scanf("%d", &i), i %= 2;

    int zero = count(a.begin(), a.end(), 0);
    if (n % 2 == 0) {
      if (zero != n / 2) puts("-1");
      else {
        printf("%lld\n", min(go(a, 0), go(a, 1)));
      }
    } else {
      printf("%lld\n", zero == n / 2 ? go(a, 1) : zero == n / 2 + 1 ? go(a, 0) : -1);
    }
  }

  return 0;
}