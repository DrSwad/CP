#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n, x;
bool vis[N];

int main() {
  cin >> n >> x;

  for (int i = 0; i < n; i++) {
    int s, d;
    scanf("%d %d", &s, &d);

    for (int j = s; j <= s + d; j++) vis[j] = true;
  }

  int ans = -1, mn = N;

  for (int i = 0; i <= 8 * 60; i++) {
    int cnt = 0;

    for (int j = i; j < N; j += x) {
      cnt += vis[j];
    }

    if (cnt < mn) {
      ans = i;
      mn = cnt;
    }
  }

  cout << ans << " " << mn << endl;

  return 0;
}