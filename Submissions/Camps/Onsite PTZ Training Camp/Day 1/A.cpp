#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  string s;
  cin >> s;

  function<int(string)> solve = [&](string s) {
    for (int l = 0; l < n; l++) {
      if (s[l] != 'B') continue;
      int r = l + 1;
      while (r < n and s[r] != 'B') r++;
      if (r >= n) continue;

      int cnt = 0;
      for (int i = l + 1; i < r; i++) {
        cnt += s[i] == 'W';
      }

      if ((r - l - 1) > 0 and cnt == (r - l - 1)) return -1;
      l = r - 1;
    }

    int ret = 0;

    for (int l = 0; l < n; l++) {
      if (s[l] != 'W') continue;
      int r = l + 1;
      while (r < n and s[r] != 'W') r++;
      if (r >= n) continue;

      int cnt = 0;
      for (int i = l + 1; i < r; i++) {
        cnt += s[i] == 'B';
      }

      if ((r - l - 1) > 0 and cnt == (r - l - 1)) {
        ret = max(ret, r - l - 1);
      }
      l = r - 1;
    }

    return ret;
  };

  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == '.') {
      s[i] = 'W';
      ans = max(ans, solve(s));
      s[i] = '.';
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}