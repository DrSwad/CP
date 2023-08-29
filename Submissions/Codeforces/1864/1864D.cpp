#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector state(n, vector(n, 0));
  for (int row = 0; row < n; row++) {
    string s;
    cin >> s;
    for (int col = 0; col < n; col++) {
      state[row][col] = s[col] - '0';
    }
  }

  if (n == 1) {
    if (state[0][0]) cout << "1\n";
    else cout << "0\n";
    return;
  }

  vector carry(n, vector(n, 0));

  int ans = 0;
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      state[row][col] ^= carry[row][col];
      if (state[row][col]) ans++;

      if (state[row][col] ^ carry[row][col]) {
        if (row + 1 < n) {
          if (col > 0) carry[row + 1][col - 1] ^= 1;
          if (col + 1 < n) carry[row + 1][col + 1] ^= 1;
          state[row + 1][col] ^= 1;
          if (col > 0 and col + 1 < n and row + 2 < n) carry[row + 2][col] ^= 1;
        }
      }
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}