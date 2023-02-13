#include <bits/stdc++.h>
using namespace std;

const int N = 2e3 + 2;
const int D = 1.8e3 + 2;
const int S = N * D;

int n;
int to[2];
int d[N];
bitset<S> dp[N];

void no() {
  cout << "No\n";
  exit(EXIT_SUCCESS);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> to[0] >> to[1];
  to[0] += to[1], to[1] = to[0] - 2 * to[1];

  int sd = 0;
  for (int i = 1; i <= n; i++) {
    cin >> d[i];
    sd += d[i];
  }

  to[0] += sd, to[1] += sd;
  if (to[0] % 2 == 1 or to[1] % 2 == 1) no();
  to[0] /= 2, to[1] /= 2;

  dp[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    dp[i] |= dp[i - 1];
    dp[i] |= dp[i - 1] << d[i];
  }

  vector<vector<int>> t(2, vector<int>(n + 1));
  for (int it = 0; it < 2; it++) {
    for (int i = n; i >= 1; i--) {
      if (to[it] < 0 or to[it] > sd or dp[i][to[it]] != 1) no();
      else if (dp[i - 1][to[it]]) t[it][i] = 0;
      else {
        t[it][i] = 1;
        to[it] -= d[i];
      }
    }
  }

  cout << "Yes\n";
  string dd = "LDUR";
  for (int i = 1; i <= n; i++) {
    cout << dd[(t[0][i] << 1) + t[1][i]];
  }
  cout << "\n";

  return 0;
}