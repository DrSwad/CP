#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int MAX_BLOCKS = 1000;
const int MOD = 1e9 + 7;

int n;
int p[N];
vector<int> e[N];
int a[N], inva[N];
int dp[N];

int block_size, total_blocks;
vector<pair<int, int>> block[MAX_BLOCKS];

int timestamp;
int disc[N];

void reset() {
  timestamp = 0;
  for (int i = 0; i < n; i++) {
    e[i].clear();
  }
  for (int i = 0; i < total_blocks; i++) {
    block[i].clear();
  }
}

inline void add(int &var, int val) {
  var += val;
  if (var >= MOD) var -= MOD;
}

void dfs(int at) {
  dp[at] = 1;
  disc[at] = timestamp++;

  debug() << name(at) name(disc[at]);

  for (int to : e[at]) {
    dfs(to);
  }

  int at_block = disc[at] / block_size;

  for (auto [ai, pref] : block[at_block]) {
    int i = inva[ai];
    if (disc[i] > disc[at] and a[i] < a[at]) {
      add(dp[at], dp[i]);
    }
  }

  for (int blk = at_block + 1; blk < total_blocks; blk++) {
    int up = upper_bound(block[blk].begin(), block[blk].end(), make_pair(a[at], 0)) - block[blk].begin();
    if (up > 0) add(dp[at], block[blk][up - 1].second);
  }

  debug() << name(dp[at]);
  for (int i = 0; i < total_blocks; i++) {
    debug() << name(i) name(block[i]);
  }

  vector<pair<int, int>> new_blk;
  int i = 0;
  for ( ; i < block[at_block].size() and block[at_block][i].first < a[at]; i++) {
    new_blk.push_back(block[at_block][i]);
  }
  int pref = new_blk.empty() ? 0 : new_blk.back().second;
  add(pref, dp[at]);
  new_blk.push_back({a[at], pref});
  for ( ; i < block[at_block].size(); i++) {
    add(block[at_block][i].second, dp[at]);
    new_blk.push_back(block[at_block][i]);
  }
  block[at_block] = new_blk;
}

void test_case() {
  scanf("%d", &n);
  for (int i = 2; i <= n; i++) {
    scanf("%d", &p[i]);
    e[p[i]].push_back(i);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }

  vector<int> order(n);
  iota(order.begin(), order.end(), 1);
  sort(order.begin(), order.end(), [&](int i, int j) {
    return a[i] < a[j];
  });

  for (int i = 0; i < n; i++) {
    int id = order[i];
    a[id] = i + 1;
    inva[a[id]] = id;
    debug() << name(id) name(a[id]);
  }

  block_size = sqrt(n);
  total_blocks = (n + block_size - 1) / block_size;

  dfs(1);

  printf("%d\n", dp[1] - n);

  reset();
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    test_case();
  }

  return 0;
}