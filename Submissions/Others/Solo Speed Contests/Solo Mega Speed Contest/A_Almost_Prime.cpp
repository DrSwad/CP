#include <bits/stdc++.h>
using namespace std;

const int N = 3e3 + 5;

int pfact[N];

int main() {
  for (int i = 2; i < N; i++) {
    int j;
    for (j = 2; j <= i; j++) {
      if (i % j == 0) break;
    }

    int ii = i;
    while (ii % j == 0) ii /= j;
    pfact[i] = 1 + pfact[ii];
  }

  int n;
  cin >> n;

  int ans = 0;
  for (int i = 1; i <= n; i++) ans += pfact[i] == 2;

  cout << ans << endl;

  return 0;
}