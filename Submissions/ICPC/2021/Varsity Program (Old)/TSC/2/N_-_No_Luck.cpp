#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;

const int n = N - 1;
int f[N];
void update(int p, int v) {
  while (p <= n) f[p] += v, p += p & -p;
}
int pref(int p) {
  int ret = 0;
  while (p) ret += f[p], p -= p & -p;
  return ret;
}

vector<int> enables_at[N];
vector<tuple<int, int, int>> queries_at[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int y, n;
  cin >> y >> n;

  vector<int> x(y + 1);
  for (int i = 1; i <= y; i++) {
    cin >> x[i];
    enables_at[x[i]].push_back(i);
  }

  for (int i = 0; i < n; i++) {
    int a, p, f;
    cin >> a >> p >> f;
    queries_at[p].push_back({i, a, a + f});
  }

  vector<int> ans(n);

  for (int p = N - 1; p >= 0; p--) {
    for (int i : enables_at[p]) {
      update(i, 1);
    }

    for (auto [i, l, r] : queries_at[p]) {
      ans[i] = p <= x[l] ? 0 : pref(r) - pref(l);
    }
  }

  for (int i : ans) {
    cout << i << "\n";
  }

  return 0;
}