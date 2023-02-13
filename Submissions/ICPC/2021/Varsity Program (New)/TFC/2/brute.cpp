#include <bits/stdc++.h>

using namespace std;

const int N = 100005;

vector<vector<int>> comp(N);
int n, m, a[N], col[N], p[N];

int find(int x) {
  return p[x] == x ? x : p[x] = find(p[x]);
}

void unite(int x, int y) {
  x = find(x), y = find(y);
  if (x == y) return;
  if (comp[x].size() < comp[y].size()) swap(x, y);
  for (int u : comp[y]) comp[x].emplace_back(u);
  comp[y].clear(), p[y] = x;
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a + i);
    p[i] = i, comp[i] = {i};
  }
  while (m--) {
    int type, x, y, c;
    scanf("%d %d %d", &type, &x, &y);
    if (type == 1) {
      a[x] = y;
    } else if (type == 2) {
      if (find(x) == find(y)) {
        if (col[x] == col[y]) col[find(x)] = -1;
      } else {
        int r_x = find(x), r_y = find(y);
        if (col[r_x] == -1 or col[r_y] == -1) {
          col[r_x] = col[r_y] = -1;
          unite(x, y);
        } else {
          if (comp[r_x].size() < comp[r_y].size()) {
            swap(x, y);
            swap(r_x, r_y);
          }
          if (col[x] == col[y]) {
            for (int u : comp[r_y]) col[u] ^= 1;
          }
          unite(x, y);
        }
      }
    } else {
      scanf("%d", &c);
      if (find(x) != find(y) or col[find(x)] == -1) {
        puts("0");
      } else {
        long long up = (long long) c * a[x], down = a[y], g = __gcd(up, down);
        up /= g, down /= g;
        if (col[x] != col[y]) putchar('-');
        printf("%lld/%lld\n", up, down);
      }
    }
  }
  return 0;
}
