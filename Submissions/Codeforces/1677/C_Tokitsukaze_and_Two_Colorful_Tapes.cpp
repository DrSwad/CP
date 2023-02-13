#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i, i--;

  vector<int> b(n), bval_at(n);
  for (int &i : b) cin >> i, i--;
  for (int i = 0; i < n; i++) {
    bval_at[b[i]] = i;
  }

  vector<int> cycle_lengths;
  vector<bool> vis(n, false);
  for (int i = 0; i < n; i++) {
    if (!vis[i]) {
      int at = i;
      int len = 0;
      while (!vis[at]) {
        len++;
        vis[at] = true;
        at = bval_at[a[at]];
      }
      if (len > 1) cycle_lengths.push_back(len / 2);
    }
  }
  sort(cycle_lengths.begin(), cycle_lengths.end());

  long long ans = 0;
  int at = 0;
  for (int len : cycle_lengths) {
    ans += (n - 1 - at) - at;
    for (int i = 0; i < len - 1; i++) {
      ans += 2 * ((n - 1 - at - 1) - at);
      at++;
    }
    ans += (n - 1 - at) - at;

    at++;
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