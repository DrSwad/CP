#include <bits/stdc++.h>
using namespace std;

const int B = 30;
const int N = 1e5 + 5;

int n;
int p[N][2];
vector<int> insert_at[B];
int ans[B];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> p[i][0] >> p[i][1];
  }

  for (int i = 0; i < n; i++) {
    int len = p[i][1] - p[i][0] + 1;
    int index = 32 - __builtin_clz(len);
    if (index < B) {
      insert_at[index].push_back(i);
    }
    for (int j = 0; j < index; j++) {
      ans[j]++;
    }
  }

  vector<pair<int, int>> order;

  for (int b = 0; b < B; b++) {
    vector<pair<int, int>> norder[3];
    int mask = (1 << b) - 1;

    for (int i : insert_at[b]) {
      norder[2].push_back({p[i][0] & mask, i});
      norder[2].push_back({p[i][1] & mask, i + n});
    }
    sort(norder[2].begin(), norder[2].end());

    for (auto [v, i] : order) {
      int val = p[i >= n ? i - n : i][i >= n];
      norder[val >> (b - 1) & 1].push_back({val &mask, i});
    }

    order.clear();
    for (int i = 0; i < 3; i++) {
      vector<pair<int, int>> merged(order.size() + norder[i].size());
      merge(order.begin(), order.end(), norder[i].begin(), norder[i].end(), merged.begin());
      swap(order, merged);
    }

    int sum = ans[b];

    vector<bool> vis(n, false);
    for (auto [_, i] : order) {
      int id = i >= n ? i - n : i;
      if (i >= n and !vis[id]) sum++;
      vis[id] = true;
    }

    for (auto [_, i] : order) {
      sum += (i >= n) ? -1 : 1;
      ans[b] = max(ans[b], sum);
    }
  }

  int q;
  cin >> q;

  while (q--) {
    int w;
    cin >> w;
    int lsb = __builtin_ctz(w);
    cout << ans[lsb] << "\n";
  }

  return 0;
}