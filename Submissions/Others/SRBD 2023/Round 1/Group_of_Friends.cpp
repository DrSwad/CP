#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

struct DSU {
  int n, sz;
  vector<int> p; // root: -1 * component size, otherwise: parent
  DSU(int n) : n(n), sz(n), p(n, -1) {}
  bool same(int a, int b) { return root(a) == root(b); }
  int root(int a) { return p[a] < 0 ? a : (p[a] = root(p[a])); }
  int size(int a) { return -p[root(a)]; }
  int size() { return sz; }
  bool merge(int a, int b, bool rank = true) {
    int x = root(a), y = root(b);
    if (x == y) return false;
    sz--;
    if (rank and - p[x] < -p[y]) swap(x, y);
    p[x] += p[y];
    p[y] = x;
    return true;
  }
};

int n;
int a[N];
vector<int> at[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    at[a[i]].push_back(i);
  }

  DSU dsu(n);

  for (int i = 1; i < N; i++) {
    if (!at[i].empty()) {
      for (int j = 0; j < (int)at[i].size() - 1; j++) {
        dsu.merge(at[i][j], at[i][j + 1]);
      }
    }
  }

  for (int div = 2; div < N; div++) {
    int last = -1;
    for (int mul = div; mul < N; mul += div) {
      if (!at[mul].empty()) {
        if (last != -1) dsu.merge(at[mul].back(), last);
        last = at[mul].back();
      }
    }
  }

  cout << dsu.size() << "\n";

  return 0;
}