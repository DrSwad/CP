#include <bits/stdc++.h>
using namespace std;

const int N = 20;

int n, m;
int adj_mask[N];
int covers[1 << N];
int path[1 << N][N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  while (m--) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj_mask[u] |= 1 << v;
    adj_mask[v] |= 1 << u;
  }

  for (int i = 0; i < n; i++) {
    adj_mask[i] |= 1 << i;
  }

  memset(path, -1, sizeof path);

  int cycle_mask = -1;

  for (int mask = 1; mask < 1 << n; mask++) {
    int lsb = __builtin_ctz(mask);
    covers[mask] = covers[mask ^ 1 << lsb] | adj_mask[lsb];

    bool cycle = false;

    for (int i = 0; i < n; i++) {
      if ((mask >> i & 1) and ((i != lsb and path[mask][i] != -1) or (mask == 1 << lsb))) {
        int to_mask = adj_mask[i] & (~mask);
        for (int j = lsb; j < n; j++) {
          if (to_mask >> j & 1) {
            path[mask | 1 << j][j] = i;
          }
        }

        if (adj_mask[i] >> lsb & 1) {
          cycle = true;
        }
      }
    }

    int rest = (~mask) & ((1 << n) - 1);
    if (cycle and (rest & covers[mask]) == rest) {
      cycle_mask = mask;
      break;
    }
  }

  if (cycle_mask == -1) cout << "No\n";
  else {
    vector<int> a(n);

    int rest = (~cycle_mask) & ((1 << n) - 1);
    for (int i = 0; i < n; i++) {
      if (rest >> i & 1) {
        int adj_cycle = adj_mask[i] & cycle_mask;
        assert(adj_cycle != 0);
        a[i] = __builtin_ctz(adj_cycle);
      }
    }

    int lsb = __builtin_ctz(cycle_mask);
    if (cycle_mask == 1 << lsb) {
      int adj = adj_mask[lsb] ^ (1 << lsb);
      assert(adj != 0);
      a[lsb] = __builtin_ctz(adj);
    }
    else {
      int start = -1;
      for (int i = 0; i < n; i++) {
        if (path[cycle_mask][i] != -1 and (adj_mask[i] >> lsb & 1)) {
          start = i;
          break;
        }
      }

      assert(start != -1);

      int at = start;
      int mask = cycle_mask;
      while (at != lsb) {
        int prv = path[mask][at];
        a[at] = prv;
        mask ^= 1 << at;
        at = prv;
      }
      a[lsb] = start;
    }

    cout << "Yes\n";
    for (int i = 0; i < n; i++) {
      if (i) cout << " ";
      cout << a[i] + 1;
    }
    cout << "\n";
  }

  return 0;
}
