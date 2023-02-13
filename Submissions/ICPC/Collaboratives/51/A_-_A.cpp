#include <bits/stdc++.h>
using namespace std;

const int N = 305;
const int mod = 1e9 + 7;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

int n, m;
int l[N], r[N], x[N];
vector<int> conds_at[N];
int dp[N][N][N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    cin >> l[i] >> r[i] >> x[i];
    l[i]--, r[i]--;
    conds_at[l[i]].push_back(i);
  }

  int ans = 0;
  vector<int> pos(3);
  dp[n][n][n] = 1;

  for (pos[0] = n; pos[0] >= 0; pos[0]--) {
    for (pos[1] = n; pos[1] >= 0; pos[1]--) {
      for (pos[2] = n; pos[2] >= 0; pos[2]--) {
        if (pos[0] == pos[1] and pos[0] != n) continue;
        if (pos[0] == pos[2] and pos[0] != n) continue;
        if (pos[1] == pos[2] and pos[1] != n) continue;

        int at = *min_element(pos.begin(), pos.end());
        for (int cond_id : conds_at[at]) {
          int count = 0;
          for (int c = 0; c < 3; c++) {
            count += pos[c] <= r[cond_id];
          }
          if (count != x[cond_id]) dp[pos[0]][pos[1]][pos[2]] = 0;
        }

        if (pos[0] == 0 or pos[1] == 0 or pos[2] == 0) {
          ans = add(ans, dp[pos[0]][pos[1]][pos[2]]);
        }

        if (at == 0) continue;
        for (int c = 0; c < 3; c++) {
          vector<int> npos = pos;
          npos[c] = at - 1;
          dp[npos[0]][npos[1]][npos[2]] = add(dp[npos[0]][npos[1]][npos[2]], dp[pos[0]][pos[1]][pos[2]]);
        }
      }
    }
  }

  cout << ans << "\n";

  return 0;
}