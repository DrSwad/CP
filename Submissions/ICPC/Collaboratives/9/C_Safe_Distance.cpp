#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
typedef pair<ld, ld> point;
#define x first
#define y second

const int OFFSET = 4;
const int N = 1e3 + 5;
const ld eps = 1e-6;
const ld INF = 1e18;

int X, Y;
int n;
point p[N];
ld pdist[N][N];
ld radius_squared, diameter_squared;
bool dfsVis[N + OFFSET];

inline bool is_directly_connected(int p1, int p2) {
  if (p1 < n and p2 < n) return pdist[p1][p2] < diameter_squared + eps;
  else if (p1 >= n) {
    if (p2 >= n) return false;
    else swap(p1, p2);
  }

  ld p2X, p2Y;
  if (p2 == n + 0) p2X = 0, p2Y = p[p1].y;
  else if (p2 == n + 1) p2X = X, p2Y = p[p1].y;
  else if (p2 == n + 2) p2X = p[p1].x, p2Y = 0;
  else p2X = p[p1].x, p2Y = Y;

  return (ld)(p[p1].x - p2X) * (p[p1].x - p2X) + (ld)(p[p1].y - p2Y) * (p[p1].y - p2Y) < radius_squared + eps;
}

void dfs(int at) {
  dfsVis[at] = true;

  for (int to = 0; to < n + OFFSET; to++) {
    if (to != at) {
      if (is_directly_connected(at, to) and !dfsVis[to]) dfs(to);
    }
  }
}

int main() {
  scanf("%d %d", &X, &Y);
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%Lf %Lf", &p[i].x, &p[i].y);
  }

  for (int p1 = 0; p1 < n; p1++) {
    for (int p2 = 0; p2 < n; p2++) {
      pdist[p1][p2] = (ld)(p[p1].x - p[p2].x) * (p[p1].x - p[p2].x) + (ld)(p[p1].y - p[p2].y) * (p[p1].y - p[p2].y);
    }
  }

  ld low = 0, high = 2 * X;

  while (low + eps < high) {
    ld radius = (low + high) / 2;
    radius_squared = radius * radius;
    diameter_squared  = 4 * radius_squared;

    // cerr << endl;
    // debug() << name(radius);

    memset(dfsVis, false, sizeof dfsVis);
    dfs(n + 0);
    // debug() << name(n + 0);
    // for (int i = 0; i < n + OFFSET; i++) cerr << dfsVis[i] << " ";
    // cerr << endl;
    if (dfsVis[n + 1] or dfsVis[n + 2]) { high = radius; continue; }

    memset(dfsVis, false, sizeof dfsVis);
    dfs(n + 1);
    // debug() << name(n + 1);
    // for (int i = 0; i < n + OFFSET; i++) cerr << dfsVis[i] << " ";
    // cerr << endl;
    if (dfsVis[n + 3]) { high = radius; continue; }

    memset(dfsVis, false, sizeof dfsVis);
    dfs(n + 2);
    // debug() << name(n + 2);
    // for (int i = 0; i < n + OFFSET; i++) cerr << dfsVis[i] << " ";
    // cerr << endl;
    if (dfsVis[n + 3]) { high = radius; continue; }

    low = radius;
  }

  printf("%.10Lf\n", low);

  return 0;
}