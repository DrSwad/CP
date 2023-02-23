#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> position;

int n;
vector<int> L;
vector<int> dp;
int block_size;
int block_cnt;
vector<pair<position, int>> block_dp;
vector<vector<int>> block_L;
vector<int> block_max;

position find_previous(int block, int at, int low = -1) {
  int blk, st;
  if (at) blk = block, st = at - 1;
  else if (block) {
    for (blk = block - 1, st = -1; ~blk; blk--) {
      if (~block_max[blk] and L[block_max[blk]] > low) {
        st = block_L[blk].size() - 1;
        break;
      }
    }
  }
  else blk = st = -1;
  return {blk, st};
}

int query(int block, int at, int L_max, int dp_min) {
  int id = block_L[block][at];
  if (L[id] > L_max) {
    L_max = L[id];
    dp_min = min(dp_min, dp[id]);

    if (id == block_max[block]) {
      while (~block) {
        dp_min = min(dp_min, block_dp[block].second);
        block = block_dp[block].first.first;
      }
      return dp_min;
    }
  }

  auto res = find_previous(block, at, L_max);
  int blk = res.first;
  int st = res.second;
  return ~blk and ~st ? query(blk, st, L_max, dp_min) : dp_min;
}

void update(int block, int at) {
  int id = block_L[block][at];
  block_max[block] = id;
  block_dp[block] = {{-1, -1}, dp[id]};

  vector<int> ans_at{dp[id]};
  stack<int> st;
  st.push(at);

  for (int i = at + 1; i < block_L[block].size(); i++) {
    int id0 = block_L[block][i];
    while (L[block_L[block][st.top()]] < L[id0]) st.pop();
    ans_at.push_back(min(dp[id0], ans_at[st.top() - at]));
    st.push(i);
  }

  for (int blk = block + 1; blk < block_cnt; blk++) {
    int prv_blk = block_dp[blk].first.first;
    int prv_at = prv_blk < block ? -1 : block_dp[blk].first.second + 1;

    if (block_max[blk] == -1 or prv_blk > block) continue;
    else {
      block_dp[blk] = {{block, max(at, prv_at)}, min(ans_at[max(0, prv_at - at)], dp[block_max[blk]])};
    }
  }
}

int solve() {
  n++;
  L.push_back(n);
  dp.resize(n);

  block_size = ceil(sqrt(n));
  block_cnt = ceil((double)n / block_size);

  block_dp.assign(block_cnt, {{-1, -1}, n});
  block_L.assign(block_cnt, {});
  block_max.assign(block_cnt, -1);

  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int i, int j) {return L[i] < L[j];});

  for (int i = 0; i < n; i++) {
    int id = order[i];
    int block = id / block_size;
    block_L[block].insert(lower_bound(block_L[block].begin(), block_L[block].end(), id), id);

    int at = lower_bound(block_L[block].begin(), block_L[block].end(), id) - block_L[block].begin();
    auto res = find_previous(block, at);
    int blk = res.first;
    int st = res.second;

    dp[id] = ~blk and ~st ? query(blk, st, -1, n) + 1 : 1;

    update(block, at);
  }

  return dp.back() - 1;
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    scanf("%d", &n);

    L.resize(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &L[i]);
      L[i]--;
    }

    printf("%d\n", solve());
  }

  return 0;
}