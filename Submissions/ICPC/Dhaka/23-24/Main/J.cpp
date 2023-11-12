#include <bits/stdc++.h>
using namespace std;

void solve() {
  vector<int> a(3);
  for (int i = 0; i < 3; i++) cin >> a[i];
  sort(a.begin(), a.end());

  for (int msk = 0; msk < 27; msk++) {
    int now = msk;
    vector<int> b(3, 0);
    for (int i = 0; i < 3; i++) {
      int result = now % 3;
      now /= 3;
      int x = i, y = (i + 1) % 3;
      if (result == 0) b[x]++, b[y]++;
      else if (result == 1) b[x] += 3;
      else b[y] += 3;
    }
    sort(b.begin(), b.end());
    if (a == b) {
      puts("perfectus");
      return;
    }
  }
  puts("invalidum");
}

int main() {
  int t, cs = 0;
  cin >> t;
  while (t--) {
    printf("Case %d: ", ++cs);
    solve();
  }
}