#include <bits/stdc++.h>
using namespace std;

const int N = 10 + 2; // CHANGE
const int M = 15;

int n;
int a[N];
vector<pair<int, int>> dp[N][N][2][M];
vector<pair<int, int>> nxt[2][N][2][M];

void init() {
  for (int level = 0; level < N; level++) {
    for (int going_down = 0; going_down < 2; going_down++) {
      for (int max_up = 0; max_up < M; max_up++) {
        if (level == 0 and going_down) continue;
        dp[0][level][going_down][max_up].push_back({level, going_down});
      }
    }
  }

  for (int a = 1; a < N; a++) {
    for (int level = 0; level < N; level++) {
      for (int going_down = 0; going_down < 2; going_down++) {
        if (level == 0 and going_down) continue;
        for (int max_up = 0; max_up < M; max_up++) {
          // go down
          if (level > 0 and a >= level) {
            int new_a = a - level;
            int new_level = level - 1;
            int new_going_down = new_level == 0 ? false : true;
            int new_max_up = min(max_up + 1, M - 1);
            for (auto [out_level, out_going_down] : dp[new_a][new_level][new_going_down][new_max_up]) {
              dp[a][level][going_down][max_up].push_back({out_level, out_going_down});
            }
          }

          // go up
          if (!going_down and a >= level + 1 and max_up >= 1) {
            int new_a = a - (level + 1);
            int new_level = level + 1;
            int new_going_down = false;
            int new_max_up = max_up - 1;
            for (auto [out_level, out_going_down] : dp[new_a][new_level][new_going_down][new_max_up]) {
              dp[a][level][going_down][max_up].push_back({out_level, out_going_down});
            }
          }
        }
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  int n;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  for (int level = 0; level < N; level++) {
    for (int going_down = 0; going_down < 2; going_down++) {
      if (level == 0 and going_down) continue;
      for (int max_up = 0; max_up < M; max_up++) {
        nxt[0][level][going_down][max_up] = dp[n - 1][level][going_down][max_up];
      }
    }
  }

  for (int i = n - 2, it = 1; i >= 0; i--, it ^= 1) {
    for (int level = 0; level < N; level++) {
      for (int going_down = 0; going_down < 2; going_down++) {
        if (level == 0 and going_down) continue;
        for (int max_up = 0; max_up < M; max_up++) {
          nxt[it][level][going_down][max_up].clear();
          int max_level = level + max_up;
          for (auto [out_level, out_going_down] : dp[i][level][going_down][max_up]) {
            int new_max_up = min(M - 1, max(0, max_level - out_level));
            for (auto [out_level2, out_going_down2] : nxt[it ^ 1][out_level][out_going_down][max_up]) {
              nxt[it][level][going_down][max_up].push_back({out_level2, out_going_down2});
            }
          }
        }
      }
    }
  }

  for (int level = 0; level <= a[0]; level++) {
    int need_level = level + 1;
  }

  return 0;
}