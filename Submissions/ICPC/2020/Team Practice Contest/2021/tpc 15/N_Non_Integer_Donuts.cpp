#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  int taka, poysha;
  scanf(" $%d.%d", &taka, &poysha);

  int ans = 0;

  while (n--) {
    int t, p;
    scanf(" $%d.%d", &t, &p);

    taka += t;
    poysha += p;

    taka += poysha / 100;
    poysha %= 100;

    ans += poysha % 100 != 0;
  }

  cout << ans << endl;

  return 0;
}