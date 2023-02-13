#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i, i--;

  vector<int> mxr(n);
  vector<bool> vis(n, false);
  for (int l = 0, r = 0; l < n; l++) {
    while (r < n and !vis[a[r]]) {
      vis[a[r]] = true;
      r++;
    }
    mxr[l] = r;
    vis[a[l]] = false;
  }

  vector<long long> pref(n);
  for (int i = 0; i < n; i++) {
    pref[i] = a[i] + (i > 0 ? pref[i - 1] : 0);
  }

  vector<vector<int>> nxt(2, vector<int>(n));
  for (int it = 0; it < 2; it++) {
    for (int i = 0; i < n; i++) {
      nxt[it][i] = i - 1;
      while (nxt[it][i] >= 0 and a[nxt[it][i]] < a[i]) {
        nxt[it][i] = nxt[it][nxt[it][i]];
      }
    }
    reverse(a.begin(), a.end());
  }
  reverse(nxt[1].begin(), nxt[1].end());
  for (int &i : nxt[1]) i = n - 1 - i;

  long long ans = 0;
  for (int i = 0; i < n; i++) {
    int d = a[i];
    int st = max(0, max(i - d, nxt[0][i] + 1));
    int en = min(i + 1, nxt[1][i] - d);
    long long esum = 1ll * d * (d + 1) / 2;
    for (int j = st; j < en; j++) {
      if (pref[j + d] - (j > 0 ? pref[j - 1] : 0) == esum
          and mxr[j] > j + d) {
        ans++;
      }
    }
  }

  cout << ans << "\n";

  return 0;
}