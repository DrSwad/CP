#include <bits/stdc++.h>
using namespace std;

int n, m, q;
int a[50], b[50], c[50], d[50];
int e[10];
long long ans;

void go(int at) {
  if (at == n) {
    long long curr = 0;

    for (int i = 0; i < q; i++) {
      if (e[b[i]] - e[a[i]] == c[i]) {
        curr += d[i];
      }
    }

    ans = max(ans, curr);
    return;
  }

  int prev = at == 0 ? 0 : e[at - 1];
  for (e[at] = prev; e[at] < m; e[at]++) {
    go(at + 1);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m >> q;
  for (int i = 0; i < q; i++) {
    cin >> a[i] >> b[i] >> c[i] >> d[i];
    a[i]--, b[i]--;
  }

  go(0);

  cout << ans << endl;

  return 0;
}