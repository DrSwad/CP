#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

int n;
int a[N];
int p[N], mn[N], mx[N];
int ans;

void solve(const vector<int> &v) {
  memset(mn, -1, sizeof mn);
  memset(mx, -1, sizeof mx);

  int nn = v.size();
  vector<vector<int>> vv(1, v);

  for (int b = 19; ~b; b--) {
    for (int i = 1; i <= n; i++) {
      p[i] = p[i - 1] + ((a[i] >> b & 1) ^ 1);
    }

    vector<vector<int>> nvv;
    for (const vector<int> &v : vv) {
      vector<int> nv[2];
      for (int i : v) {
        nv[p[i] & 1].push_back(i);
      }

      for (int it = 0; it < 2; it++) {
        for (int i : nv[it]) {
          mn[p[i]] = mn[p[i]] == -1 ? i : min(mn[p[i]], i);
          mx[p[i]] = mx[p[i]] == -1 ? i : max(mx[p[i]], i);
        }
        for (int i : nv[it]) ans = max(ans, mx[p[i]] - mn[p[i]]);
        for (int i : nv[it]) mn[p[i]] = mx[p[i]] = -1;

        if (!nv[it].empty()) nvv.push_back(nv[it]);
      }
    }

    swap(vv, nvv);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  vector<int> odd, even;
  for (int i = 0; i <= n; i++) {
    if (i & 1) odd.push_back(i);
    else even.push_back(i);
  }

  solve(odd);
  solve(even);

  cout << ans << "\n";

  return 0;
}