#include <bits/stdc++.h>
using namespace std;

int segment_grundy(int segment_len, int l, int r) {
  segment_len %= (l + r);
  return segment_len / l;
}

bool does_segments_intersect(int l1, int r1, int l2, int r2) {
  return !(r1 < l2 or r2 < l1);
}

bool is_grundy_covered(int segment_grundy, int l, int r, int cl, int cr) {
  int L = segment_grundy * l;
  int R = (segment_grundy + 1) * l - 1;
  return does_segments_intersect(cl, cr, L, R) or
         does_segments_intersect(cl, cr, (l + r) + L, (l + r) + R);
}

int cycle_grundy(int cycle_size, int l, int r) {
  r = min(r, cycle_size);
  if (r < l) return 0;

  int cl = cycle_size - r;
  int cr = cycle_size - l;

  int ret = segment_grundy(l + r - 1, l, r) + 1;
  if (cr - cl + 1 >= l + r) return ret;

  cl %= (l + r);
  cr %= (l + r);
  if (cr < cl) cr += l + r;

  if (!is_grundy_covered(0, l, r, cl, cr)) ret = min(ret, 0);
  int crg = segment_grundy(cr, l, r) + 1;
  if (!is_grundy_covered(crg, l, r, cl, cr)) ret = min(ret, crg);

  return ret;
}

void brute(int n, int l, int r) {
  vector<int> grundy(n + 1, 0);
  for (int len = 0; len <= n; len++) {
    set<int> st;
    for (int seg = l; seg <= r; seg++) {
      for (int i = 0; i <= len and i + seg <= len; i++) {
        int j = len - i - seg;
        st.insert(grundy[i] ^ grundy[j]);
      }
    }
    int mex = 0;
    while (st.count(mex)) mex++;
    grundy[len] = mex;
  }

  debug(n, l, r);
  for (int l = 0; l <= n; ) {
    int r = l;
    while (r <= n and grundy[r] == grundy[l]) r++;
    cerr << r - l << " " << grundy[l] << endl;
    l = r;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  brute(100, 4, 10);

  // int n, l, r;
  // cin >> n >> l >> r;

  // vector<vector<int>> adj(n);
  // for (int i = 0; i < n; i++) {
  //   int u, v;
  //   cin >> u >> v;
  //   u--, v--;
  //   adj[u].push_back(v);
  //   adj[v].push_back(u);
  // }

  // int tot_grundy = 0;
  // vector<bool> vis(n, false);
  // for (int i = 0; i < n; i++) {
  //   if (!vis[i]) {
  //     int cycle_size = 0;
  //     int at = i;
  //     while (!vis[at]) {
  //       cycle_size++;
  //       vis[at] = true;
  //       int nxt = adj[at][0];
  //       if (vis[nxt]) nxt = adj[at][1];
  //       if (vis[nxt]) break;
  //       at = nxt;
  //     }
  //     tot_grundy ^= cycle_grundy(cycle_size, l, r);
  //   }
  // }

  // cout << (tot_grundy ? "Alice\n" : "Bob\n");

  return 0;
}