#include <bits/stdc++.h>
using namespace std;

int n, vw, vp, xw, xp;

bool movePony() {
  if (xp == n) {
    if (xw == xp - 1) return false;
    if (vp % 2 == 1) xp--;
    return true;
  }

  if (xp + vp < n - 1) xp += vp;
  else if ((n - xp) % 2 == vp % 2) xp = n;
  else xp = n - 1;

  return true;
}

bool moveWolf() {
  xw += vw;
  return xw < xp;
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    scanf("%d %d %d %d %d", &n, &vw, &vp, &xw, &xp);
    if (xw > xp) {
      xw = (n + 1) - xw;
      xp = (n + 1) - xp;
    }

    int ans = 0;
    while (true) {
      ans++;
      if (!movePony()) break;
      ans++;
      if (!moveWolf()) break;
    }

    printf("%d\n", ans);
  }

  return 0;
}