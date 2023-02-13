#include <bits/stdc++.h>
using namespace std;

const int N = 500;
int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

struct DSU {
  int n, sz;
  vector<int> p; // root: -1 * component size, otherwise: parent
  DSU(int n) : n(n), sz(n), p(n, -1) {}
  bool same(int a, int b) { return root(a) == root(b); }
  int root(int a) { return p[a] < 0 ? a : (p[a] = root(p[a])); }
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

struct Query {
  int type;
  int x1, y1, x2, y2;
  int full_ans, partial_ans;
  Query() {
    full_ans = partial_ans = 0;
  }
};

struct Component {
  int x, y, mn_x, mx_x, mn_y, mx_y;
  Component() {
    mx_x = mx_y = -1;
    mn_x = mn_y = x = y = N;
  }
  Component(int _x, int _y, int _mn_x, int _mn_y, int _mx_x, int _mx_y) {
    x = _x;
    y = _y;
    mn_x = _mn_x;
    mx_x = _mx_x;
    mn_y = _mn_y;
    mx_y = _mx_y;
  }
  void update(const Component &other) {
    if (make_pair(x, y) > make_pair(other.x, other.y)) {
      x = other.x;
      y = other.y;
    }
    mn_x = min(mn_x, other.mn_x);
    mx_x = max(mx_x, other.mx_x);
    mn_y = min(mn_y, other.mn_y);
    mx_y = max(mx_y, other.mx_y);
  }
};

class BIT {
public:
  int n;
  vector<int> f;
  BIT(int n) : n(n) {
    f.resize(n + 1, 0);
  }
  void update(int p, int v) {
    p++;
    while (p <= n) f[p] += v, p += p & -p;
  }
  int pref(int p) {
    p++;
    int ret = 0;
    while (p) ret += f[p], p -= p & -p;
    return ret;
  }
};

class BIT2D {
public:
  int n, m;
  vector<BIT> f;
  BIT2D(int n, int m) : n(n) {
    f.resize(n + 1, BIT(m));
  }
  void update(int p, int q, int v) {
    p++;
    while (p <= n) f[p].update(q, v), p += p & -p;
  }
  int pref(int p, int q) {
    p++;
    int ret = 0;
    while (p) ret += f[p].pref(q), p -= p & -p;
    return ret;
  }
  int rect(int x1, int y1, int x2, int y2) {
    return pref(x2, y2) - pref(x2, y1 - 1) - pref(x1 - 1, y2) + pref(x1 - 1, y1 - 1);
  }
};

void test_case() {
  int n, m, q;
  cin >> n >> m >> q;

  vector<vector<int>> g(n, vector<int>(m));
  for (vector<int> &row : g) {
    for (int &c : row) {
      cin >> c;
    }
  }

  vector<Query> query(q);
  vector<vector<int>> blocked(n, vector<int>(m, 0));
  for (int i = 0; i < q; i++) {
    Query &qq = query[i];
    cin >> qq.type;
    if (query[i].type == 1) {
      cin >> qq.x1 >> qq.y1 >> qq.x2 >> qq.y2;
      qq.x1--, qq.y1--, qq.x2--, qq.y2--;
    }
    else {
      cin >> qq.x1 >> qq.y1;
      qq.x1--, qq.y1--;
      blocked[query[i].x1][query[i].y1]++;
    }
  }

  vector<vector<int>> id(n, vector<int>(m, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (j > 0) id[i][j] = id[i][j - 1] + 1;
      else id[i][j] = m * i;
    }
  }

  DSU dsu(n * m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (blocked[i][j]) continue;
      if (j < m - 1 and !blocked[i][j + 1] and g[i][j] == g[i][j + 1]) {
        dsu.merge(id[i][j], id[i][j + 1]);
      }
      if (i < n - 1 and !blocked[i + 1][j] and g[i][j] == g[i + 1][j]) {
        dsu.merge(id[i][j], id[i + 1][j]);
      }
    }
  }

  vector<Component> comp(n * m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      comp[dsu.root(id[i][j])].update(Component(i, j, i, j, i, j));
    }
  }

  BIT2D bit(n, m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (!blocked[i][j] and dsu.root(id[i][j]) == id[i][j]) {
        bit.update(comp[id[i][j]].x, comp[id[i][j]].y, 1);
      }
    }
  }

  function<bool(int, int, int)> is_comp_inside_query = [&](int i, int j, int qid) {
    int comp_id = dsu.root(id[i][j]);
    if (comp[comp_id].mn_x < query[qid].x1) return false;
    if (comp[comp_id].mx_x > query[qid].x2) return false;
    if (comp[comp_id].mn_y < query[qid].y1) return false;
    if (comp[comp_id].mx_y > query[qid].y2) return false;
    return true;
  };

  function<bool(int, int, int)> is_cell_inside_query = [&](int x, int y, int qid) {
    if (x < query[qid].x1) return false;
    if (x > query[qid].x2) return false;
    if (y < query[qid].y1) return false;
    if (y > query[qid].y2) return false;
    return true;
  };

  vector<bool> comp_vis(n * m, false);
  vector<int> comps_changed;

  function<bool(int, int, int)> check_cell_on_edge = [&](int x, int y, int qid) {
    int comp_id = dsu.root(id[x][y]);
    if (!comp_vis[comp_id] and !is_comp_inside_query(x, y, qid)) {
      query[qid].partial_ans++;
      comp_vis[comp_id] = true;
      comps_changed.push_back(comp_id);
      return is_cell_inside_query(comp[comp_id].x, comp[comp_id].y, qid);
    }
    return false;
  };

  for (int i = q - 1; i >= 0; i--) {
    Query &qq = query[i];

    if (qq.type == 1) {
      int overcount = 0;
      for (int x = qq.x1; x <= qq.x2; x++) {
        overcount += check_cell_on_edge(x, qq.y1, i);
        if (qq.y2 > qq.y1) overcount += check_cell_on_edge(x, qq.y2, i);
      }
      for (int y = qq.y1 + 1; y < qq.y2; y++) {
        overcount += check_cell_on_edge(qq.x1, y, i);
        if (qq.x2 > qq.x1) overcount += check_cell_on_edge(qq.x2, y, i);
      }

      qq.full_ans = bit.rect(qq.x1, qq.y1, qq.x2, qq.y2) - overcount;

      while (!comps_changed.empty()) {
        comp_vis[comps_changed.back()] = false;
        comps_changed.pop_back();
      }
    }
    else {
      int qx = query[i].x1;
      int qy = query[i].y1;
      blocked[qx][qy]--;
      if (blocked[qx][qy]) continue;

      Component merged_comp;
      merged_comp.update(comp[id[qx][qy]]);

      for (int i = 0; i < 4; i++) {
        int nx = qx + dx[i];
        if (nx < 0 or nx >= n) continue;
        int ny = qy + dy[i];
        if (ny < 0 or ny >= m) continue;
        if (blocked[nx][ny]) continue;

        if (g[qx][qy] != g[nx][ny]) continue;
        if (dsu.same(id[qx][qy], id[nx][ny])) continue;

        int comp_id = dsu.root(id[nx][ny]);
        merged_comp.update(comp[comp_id]);
        bit.update(comp[comp_id].x, comp[comp_id].y, -1);
        dsu.merge(id[qx][qy], id[nx][ny]);
      }
      int comp_id = dsu.root(id[qx][qy]);
      comp[comp_id].update(merged_comp);
      bit.update(comp[comp_id].x, comp[comp_id].y, 1);
    }
  }

  for (int i = 0; i < q; i++) {
    if (query[i].type == 1) {
      cout << query[i].full_ans << " " << query[i].partial_ans << "\n";
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}