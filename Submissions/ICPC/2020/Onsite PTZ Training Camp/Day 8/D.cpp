#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i, i--;

  vector<int> mx_l(n), mx_r(n);
  for (int i = 0; i < n; i++) {
    mx_l[i] = i - 1;
    while (mx_l[i] >= 0 and a[mx_l[i]] < a[i]) mx_l[i] = mx_l[mx_l[i]];
  }
  for (int i = n - 1; i >= 0; i--) {
    mx_r[i] = i + 1;
    while (mx_r[i] < n and a[mx_r[i]] < a[i]) mx_r[i] = mx_r[mx_r[i]];
  }

  vector<int> prv(n), nxt(n), seen(n);
  fill(seen.begin(), seen.end(), -1);
  for (int i = 0; i < n; i++) {
    prv[i] = seen[a[i]];
    seen[a[i]] = i;
  }
  fill(seen.begin(), seen.end(), n);
  for (int i = n - 1; i >= 0; i--) {
    nxt[i] = seen[a[i]];
    seen[a[i]] = i;
  }

  vector<int> match_l(n), match_r(n);
  for (int i = 0; i < n; i++) {
    match_l[i] = i == 0 ? -1 : match_l[i - 1];
    match_l[i] = max(match_l[i], prv[i]);
    mx_l[i] = max(mx_l[i], match_l[i]);
  }
  for (int i = n - 1; i >= 0; i--) {
    match_r[i] = i == n - 1 ? n : match_r[i + 1];
    match_r[i] = min(match_r[i], nxt[i]);
    mx_r[i] = min(mx_r[i], match_r[i]);
  }

  long long ans = 0;
  for (int i = 0; i < n; i++) {
    // DB();
    // debug(i);
    int left = i - mx_l[i], right = mx_r[i] - i;
    vector<bool> vis(n, false);
    if (left <= right) {
      int min_r = mx_r[i];
      for (int l = i; l > mx_l[i]; l--) {
        if (vis[a[l]]) break;
        vis[a[l]] = true;
        min_r = min(min_r, nxt[l]);
        // a[i] - k + l <= r
        // i <= r
        // r < min_r
        int st_r = max(i, a[i] - k + l);
        int en_r = min_r;
        // debug(l, nxt[l], st_r, en_r);
        ans += max(0, en_r - st_r);
      }
    }
    else {
      int max_l = mx_l[i];
      for (int r = i; r < mx_r[i]; r++) {
        if (vis[a[r]]) break;
        vis[a[r]] = true;
        max_l = max(max_l, prv[r]);
        // l <= r + k - a[i]
        // l <= i
        // max_l < l
        int st_l = max_l + 1;
        int en_l = min(r + k - a[i] + 1, i + 1);
        ans += max(0, en_l - st_l);
      }
    }

    // for (int l = mx_l[i] + 1; l <= i; l++) {
    //   for (int r = i; r < mx_r[i]; r++) {
    //     bool flag = true;
    //     for (int j = l; j <= r; j++) {
    //       if (vis[a[j]]) flag = false;
    //       vis[a[j]] = true;
    //     }
    //     ans += flag and a[i] - k + l <= r;
    //   }
    // }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}