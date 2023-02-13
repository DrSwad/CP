#include <bits/stdc++.h>
using namespace std;

class BIT {
public:
  int n;
  vector<int> f;
  BIT(int n) : n(n) {
    f.resize(n + 1, 0);
  }
  void update(int p, int v) {
    while (p <= n) f[p] += v, p += p & -p;
  }
  int pref(int p) {
    int ret = 0;
    while (p) ret += f[p], p -= p & -p;
    return ret;
  }
  int range(int l, int r) {
    return pref(r) - pref(l - 1);
  }
};

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<BIT> bit(3, BIT(n));
  for (int i = 0; i < n; i++) {
    bit[a[i] - 1].update(i + 1, 1);
  }

  long long ans = 0;

  while (m--) {
    int at, val, pref;
    cin >> at >> val >> pref;
    int old = a[at - 1];
    a[at - 1] = val;

    bit[old - 1].update(at, -1);
    bit[val - 1].update(at, 1);

    vector<vector<int>> f(2, vector<int>(3));
    for (int i = 0; i < 3; i++) {
      f[0][i] = bit[i].pref(pref);
    }
    for (int i = 0; i < 3; i++) {
      f[1][i] = bit[i].pref(n) - f[0][i];
    }

    vector<int> sum(2, 0);
    for (int it = 0; it < 2; it++) {
      for (int i = 0; i < 3; i++) {
        sum[it] += f[it][i] * (i + 1);
      }
    }

    if (sum[0] > sum[1]) swap(sum[0], sum[1]), swap(f[0], f[1]);
    int moves = 0;

    // swap 1 and 3
    {
      int take = min(f[0][0], f[1][2]);
      take = min(take, (sum[1] - sum[0]) / 4);
      f[0][0] -= take, f[1][2] -= take;
      f[0][2] += take, f[1][0] += take;
      sum[0] += 2 * take, sum[1] -= 2 * take;
      moves += take;
    }

    // swap 1 and 2
    {
      int take = min(f[0][0], f[1][1]);
      take = min(take, (sum[1] - sum[0]) / 2);
      f[0][0] -= take, f[1][1] -= take;
      f[0][1] += take, f[1][0] += take;
      sum[0] += take, sum[1] -= take;
      moves += take;
    }

    // swap 2 and 3
    {
      int take = min(f[0][1], f[1][2]);
      take = min(take, (sum[1] - sum[0]) / 2);
      f[0][1] -= take, f[1][2] -= take;
      f[0][2] += take, f[1][1] += take;
      sum[0] += take, sum[1] -= take;
      moves += take;
    }

    if (sum[0] != sum[1]) moves = -1;

    ans += moves;
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}