#include <bits/stdc++.h>
using namespace std;

const int max_n = 100;
const int max_k = 20;
const int mod = 1e9 + 7;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

int n, k;
vector<int> adj[max_n + 1];
int dp[max_n + 1][max_k + 1][max_k + 1];
int trans_dp[2][max_k + 1][2][max_k + 1][2][max_k + 1];

void dfs(int at, int from) {
  if (from != 0 and adj[at].size() == 1) {
    dp[at][0][0] = 1;
    if (k > 0) {
      dp[at][k][1] = 1;
    }
  }
  else {
    for (int to : adj[at]) {
      if (to != from) {
        dfs(to, at);
      }
    }

    memset(trans_dp[0], 0, sizeof trans_dp[0]);

    for (int tot_min_picked_depth0 = 0; tot_min_picked_depth0 <= k; tot_min_picked_depth0++) {
      for (int tot_min_picked_depth1 = tot_min_picked_depth0; tot_min_picked_depth1 <= k; tot_min_picked_depth1++) {
        trans_dp[0][tot_min_picked_depth0][tot_min_picked_depth0 == k][tot_min_picked_depth1][tot_min_picked_depth1 == k][0] = 1;
      }
    }

    dp[at][0][0] = 1;

    for (int to : adj[at]) {
      if (to != from) {
        int sum = 0;
        for (int cur_min_picked_depth = 0; cur_min_picked_depth <= k; cur_min_picked_depth++) {
          for (int cur_max_stranded_depth = 0; cur_max_stranded_depth <= k; cur_max_stranded_depth++) {
            sum = add(sum, dp[to][cur_min_picked_depth][cur_max_stranded_depth]);
          }
        }
        dp[at][0][0] = mul(dp[at][0][0], sum);

        memset(trans_dp[1], 0, sizeof trans_dp[1]);
        for (int tot_min_picked_depth0 = 0; tot_min_picked_depth0 <= k; tot_min_picked_depth0++) {
          for (int prv_min_picked_depth0_found = 0; prv_min_picked_depth0_found < 2; prv_min_picked_depth0_found++) {
            for (int tot_min_picked_depth1 = tot_min_picked_depth0; tot_min_picked_depth1 <= k; tot_min_picked_depth1++) {
              for (int prv_min_picked_depth1_found = 0; prv_min_picked_depth1_found < 2; prv_min_picked_depth1_found++) {
                for (int prv_max_stranded_depth = 0; prv_max_stranded_depth <= k; prv_max_stranded_depth++) {
                  for (int cur_min_picked_depth = tot_min_picked_depth0; cur_min_picked_depth <= k; cur_min_picked_depth++) {
                    for (int cur_max_stranded_depth = 0; cur_max_stranded_depth <= k; cur_max_stranded_depth++) {
                      int new_min_picked_depth0_found = prv_min_picked_depth0_found;
                      int new_min_picked_depth1_found = prv_min_picked_depth1_found;
                      int new_max_stranded_depth = prv_max_stranded_depth;
                      int rest_min_picked_depth;

                      if (tot_min_picked_depth0 != tot_min_picked_depth1 and cur_min_picked_depth == tot_min_picked_depth0) {
                        rest_min_picked_depth = tot_min_picked_depth1;
                      }
                      else {
                        rest_min_picked_depth = tot_min_picked_depth0;
                      }

                      if (tot_min_picked_depth0 == tot_min_picked_depth1) {
                        if (cur_min_picked_depth == tot_min_picked_depth0) {
                          if (!prv_min_picked_depth0_found) {
                            new_min_picked_depth0_found = 1;
                          }
                          else if (!prv_min_picked_depth1_found) {
                            new_min_picked_depth1_found = 1;
                          }
                        }
                      }
                      else {
                        if (cur_min_picked_depth == tot_min_picked_depth0) {
                          if (!prv_min_picked_depth0_found) {
                            new_min_picked_depth0_found = 1;
                          }
                          else {
                            continue;
                          }
                        }
                        else if (cur_min_picked_depth < tot_min_picked_depth1) {
                          continue;
                        }
                        else if (cur_min_picked_depth == tot_min_picked_depth1) {
                          if (!prv_min_picked_depth1_found) {
                            new_min_picked_depth1_found = 1;
                          }
                        }
                      }

                      if (cur_max_stranded_depth > 0 and rest_min_picked_depth + 1 + cur_max_stranded_depth > k) {
                        new_max_stranded_depth = max(new_max_stranded_depth, cur_max_stranded_depth);
                      }

                      int &new_dp = trans_dp[1][tot_min_picked_depth0][new_min_picked_depth0_found][tot_min_picked_depth1][new_min_picked_depth1_found][new_max_stranded_depth];
                      int &prv_dp = trans_dp[0][tot_min_picked_depth0][prv_min_picked_depth0_found][tot_min_picked_depth1][prv_min_picked_depth1_found][prv_max_stranded_depth];
                      int &cur_dp = dp[to][cur_min_picked_depth][cur_max_stranded_depth];
                      new_dp = add(new_dp, mul(prv_dp, cur_dp));
                    }
                  }
                }
              }
            }
          }
        }

        swap(trans_dp[0], trans_dp[1]);
      }
    }

    for (int tot_min_picked_depth0 = 0; tot_min_picked_depth0 <= k; tot_min_picked_depth0++) {
      for (int tot_min_picked_depth1 = tot_min_picked_depth0; tot_min_picked_depth1 <= k; tot_min_picked_depth1++) {
        for (int tot_max_stranded_depth = 0; tot_max_stranded_depth <= k; tot_max_stranded_depth++) {
          int new_min_picked_depth0 = min(k, tot_min_picked_depth0 + 1);
          int new_max_stranded_depth = tot_max_stranded_depth ? tot_max_stranded_depth + 1 : 0;
          if (tot_max_stranded_depth == 0 and tot_min_picked_depth0 == k) new_max_stranded_depth = 1;

          if (new_max_stranded_depth <= k) {
            dp[at][new_min_picked_depth0][new_max_stranded_depth] = add(dp[at][new_min_picked_depth0][new_max_stranded_depth], trans_dp[0][tot_min_picked_depth0][1][tot_min_picked_depth1][1][tot_max_stranded_depth]);
          }
        }
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> k;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  if (n == 1) {
    assert(k == 0);
    cout << "1\n";
  }
  else {
    dfs(1, 0);

    int ans = 0;
    for (int min_picked_depth = 0; min_picked_depth <= k; min_picked_depth++) {
      ans = add(ans, dp[1][min_picked_depth][0]);
    }

    cout << ans << "\n";
  }

  return 0;
}