#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;
  a.insert(a.begin(), n + 1);

  vector<vector<int>> nxt(2, vector<int>(n + 1));
  for (int it = 0; it < 2; it++) {
    for (int i = 1; i <= n; i++) {
      int &l = nxt[it][i];
      l = i - 1;
      while (l and a[l] < a[i]) l = nxt[it][l];
    }
    reverse(a.begin(), a.end());
  }
  reverse(nxt[1].begin(), nxt[1].end());
  for (int &i : nxt[1]) i = n + 1 - i;

  vector<vector<int>> pos(n + 1);
  for (int i = 1; i <= n; i++) {
    pos[a[i]].push_back(i);
  }

  long long ans = 0;

  for (int i = 1; i <= n; i++) {
    int st = nxt[0][i] + 1, en = i - 1;
    int L = i + 1, R = nxt[1][i] - 1;
    if (i - nxt[0][i] > nxt[1][i] - i) {
      swap(st, L), swap(en, R);
    }

    for (int j = st; j <= en; j++) {
      int need = a[i] - a[j];
      if (need <= 0) continue;
      int fR = upper_bound(pos[need].begin(), pos[need].end(), R) - pos[need].begin();
      int fL = upper_bound(pos[need].begin(), pos[need].end(), L - 1) - pos[need].begin();
      ans += fR - fL;
    }
  }

  cout << ans << "\n";

  return 0;
}