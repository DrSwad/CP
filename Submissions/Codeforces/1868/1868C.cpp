#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int mod = 998244353;
const int bits = 60;
const int max_depth = bits - 1;
const int max_dist = 2 * max_depth;
const int max_m = 1e5;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

ll n_val;
string n;
int max_tree_depth;
int m;
// bamboo_dp[tree_depth][len] = number of paths of length len starting at the root of a
//                              full binary tree of depth tree_depth
int bamboo_dp[max_depth + 1][max_depth + 1];
// path_dp[tree_depth][len] = number of paths of length len in a full binary tree of depth
//                            tree_depth
int path_dp[max_depth + 1][max_dist + 1];
// subtree_bamboo_dp[tree_depth][len] = number of paths of length len starting at the root
//                                      in the given binary until depth tree_depth
int subtree_bamboo_dp[max_depth + 1][max_depth + 1];
// dist_freq[d] = number of pairs (i, j) s.t. dist(i, j) = d
int dist_freq[max_dist + 1];
// ways[d][mx] = number of assignments of a path of length d s.t. the max value on it is mx
// ways[d][mx] = mx**(d+1) - (mx-1)**(d+1)
int ways[max_dist + 1][max_m + 1];
// m_exp[m][e] = m**e
// m_inv = 1/m
int m_exp[max_m + 1][max_dist + 2];
int m_inv[max_m + 1];

ll binExp(ll a, ll e) {
  ll ret = 1;
  while (e) {
    if (e & 1) ret = mul(ret, a);
    a = mul(a, a), e >>= 1;
  }
  return ret;
}

void init() {
  for (int m = 1; m <= max_m; m++) {
    m_exp[m][0] = 1;
    for (int e = 1; e <= max_dist + 1; e++) {
      m_exp[m][e] = mul(m_exp[m][e - 1], m);
    }
  }
  m_inv[1] = 1;
  for (int m = 2; m <= max_m; m++) {
    m_inv[m] = mul(m_inv[mod % m], mod - mod / m);
  }

  bamboo_dp[0][0] = 1;
  for (int tree_depth = 1; tree_depth <= max_depth; tree_depth++) {
    bamboo_dp[tree_depth][0] = 1;
    for (int path_len = 1; path_len <= max_depth; path_len++) {
      bamboo_dp[tree_depth][path_len] = mul(2, bamboo_dp[tree_depth - 1][path_len - 1]);
    }
  }

  path_dp[0][0] = 1;
  for (int tree_depth = 1; tree_depth <= max_depth; tree_depth++) {
    for (int path_len = 0; path_len <= max_dist; path_len++) {
      path_dp[tree_depth][path_len] = add(path_dp[tree_depth][path_len], mul(2, path_dp[tree_depth - 1][path_len]));
    }

    for (int left_depth = 0; left_depth <= max_depth; left_depth++) {
      for (int right_depth = 0; right_depth <= max_depth; right_depth++) {
        int left_ways = left_depth == 0 ? 1 : bamboo_dp[tree_depth - 1][left_depth - 1];
        int right_ways = right_depth == 0 ? 1 : bamboo_dp[tree_depth - 1][right_depth - 1];
        int len = left_depth + right_depth;
        path_dp[tree_depth][len] = add(path_dp[tree_depth][len], mul(left_ways, right_ways));
      }
    }
  }
}

void dfs(int at_depth) {
  if (at_depth == max_tree_depth) {
    subtree_bamboo_dp[at_depth][0] = 1;
  }
  else {
    dfs(at_depth + 1);

    int full_tree_depth;
    if (n[at_depth + 1] == '0') {
      full_tree_depth = max_tree_depth - at_depth - 2;
    }
    else {
      full_tree_depth = max_tree_depth - at_depth - 1;
    }

    subtree_bamboo_dp[at_depth][0] = 1;
    for (int depth = 1; depth <= max_depth; depth++) {
      if (full_tree_depth >= 0) subtree_bamboo_dp[at_depth][depth] = add(subtree_bamboo_dp[at_depth][depth], bamboo_dp[full_tree_depth][depth - 1]);
      subtree_bamboo_dp[at_depth][depth] = add(subtree_bamboo_dp[at_depth][depth], subtree_bamboo_dp[at_depth + 1][depth - 1]);
    }

    if (full_tree_depth >= 0) {
      for (int left_depth = 1; left_depth <= max_depth; left_depth++) {
        for (int right_depth = 1; right_depth <= max_depth; right_depth++) {
          int left_ways, right_ways;
          if (n[at_depth + 1] == '0') {
            left_ways = subtree_bamboo_dp[at_depth + 1][left_depth - 1];
            right_ways = bamboo_dp[full_tree_depth][right_depth - 1];
          }
          else {
            left_ways = bamboo_dp[full_tree_depth][left_depth - 1];
            right_ways = subtree_bamboo_dp[at_depth + 1][right_depth - 1];
          }
          int len = left_depth + right_depth;
          dist_freq[len] = add(dist_freq[len], mul(left_ways, right_ways));
        }
      }

      for (int path_len = 0; path_len <= max_dist; path_len++) {
        dist_freq[path_len] = add(dist_freq[path_len], path_dp[full_tree_depth][path_len]);
      }
    }
  }

  for (int depth = 0; depth <= max_depth; depth++) {
    dist_freq[depth] = add(dist_freq[depth], subtree_bamboo_dp[at_depth][depth]);
  }
}

void test_case() {
  {
    cin >> n_val >> m;

    n = "";
    ll _ = n_val;
    while (_) {
      n += '0' + (_ & 1);
      _ >>= 1;
    }
    reverse(n.begin(), n.end());

    max_tree_depth = (int)n.length() - 1;
  }

  memset(subtree_bamboo_dp, 0, sizeof subtree_bamboo_dp);
  memset(dist_freq, 0, sizeof dist_freq);
  dfs(0);

  for (int d = 0; d <= max_dist; d++) {
    for (int mx = 1; mx <= m; mx++) {
      ways[d][mx] = add(m_exp[mx][d + 1], mod - m_exp[mx - 1][d + 1]);
    }
  }

  // ans = sum(dist_freq[d] * ways[d][mx] * m**(n-(d+1)) * mx)
  int ans = 0;
  int m_pow = binExp(m, n_val - 1);
  for (int d = 0; d <= min(n_val - 1, (ll)max_dist); d++) {
    for (int mx = 1; mx <= m; mx++) {
      ans = add(ans, mul(dist_freq[d], mul(ways[d][mx], mul(m_pow, mx))));
    }
    m_pow = mul(m_pow, m_inv[m]);
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}