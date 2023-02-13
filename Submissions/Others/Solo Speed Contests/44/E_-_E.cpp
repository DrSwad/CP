#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int f[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  f[0] = 0;
  for (int i = 1; i < N; i++) {
    f[i] = 1 + f[i % __builtin_popcount(i)];
  }

  int n;
  cin >> n;

  string s;
  cin >> s;

  int tot = count(s.begin(), s.end(), '1');
  int val[2], rem[2] = {0}, p[2][N];
  val[0] = tot - 1, val[1] = tot + 1;

  for (int it = 0; it < 2; it++) {
    if (val[it] > 0) {
      for (int i = n - 1, p2 = 1; i >= 0; i--, p2 = p2 * 2 % val[it]) {
        p[it][n - 1 - i] = p2;
        if (s[i] == '1') {
          (rem[it] += p2) %= val[it];
        }
      }
    }
  }

  for (int i = 0; i < n; i++) {
    if (s[i] == '0') {
      int new_val = (rem[1] + p[1][n - 1 - i]) % val[1];
      cout << 1 + f[new_val] << "\n";
    }
    else {
      if (val[0] <= 0) {
        cout << "0\n";
      }
      else {
        int new_val = (rem[0] + val[0] - p[0][n - 1 - i]) % val[0];
        cout << 1 + f[new_val] << "\n";
      }
    }
  }

  return 0;
}