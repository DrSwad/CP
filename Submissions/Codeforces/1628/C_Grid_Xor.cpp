#include <bits/stdc++.h>
using namespace std;

void test_case() {
    int n;
    cin >> n;
    
    vector a(n, vector<int>(n));
    for (auto &row : a) {
        for (auto &i : row) {
            cin >> i;
        }
    }

    vector pref(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            pref[i][j] = a[i - 1][j - 1] ^ pref[i - 1][j] ^ pref[i][j - 1] ^ pref[i - 1][j - 1];
        }
    }

    int ans = 0;

    for (int i1 = 1; i1 <= n / 2; i1++) {
        int j1 = i1;
        int i2 = (n + 1) - i1;
        int j2 = i2;

        ans ^= pref[i2][j2] ^ pref[i1 - 1][j2] ^ pref[i2][j1 - 1] ^ pref[i1 - 1][j1 - 1];
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