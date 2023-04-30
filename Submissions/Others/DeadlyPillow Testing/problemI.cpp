#include <bits/stdc++.h>
using namespace std;

const int N = 2e3 + 5;

int fn, fm;
int f[2 * N][2 * N];
void init_bit() {
  for (int i = 1; i <= fn; i++) {
    for (int j = 1; j <= fm; j++) {
      if (j + (j & -j) <= fm) {
        f[i][j + (j & -j)] += f[i][j];
      }
      if (i + (i & -i) <= fn) {
        f[i + (i & -i)][j] += f[i][j];
      }
    }
  }
}
void update(int p, int q, int v) {
  assert(1 <= p and p <= fn and 1 <= q and q <= fm);
  while (p <= fn) {
    int _q = q;
    while (_q <= fm) f[p][_q] += v, _q += _q & -_q;
    p += p & -p;
  }
}
int pref(int p, int q) {
  p = clamp(p, 0, fn);
  q = clamp(q, 0, fm);
  int ret = 0;
  while (p) {
    int _q = q;
    while (_q) ret += f[p][_q], _q -= _q & -_q;
    p -= p & -p;
  }
  return ret;
}
int range(int x1, int y1, int x2, int y2) {
  return pref(x2, y2) - pref(x2, y1 - 1) - pref(x1 - 1, y2) + pref(x1 - 1, y1 - 1);
}

int n, m;
set<int> diag_remain_x[2][2 * N];

int get_diag_id(int diag_index, int x, int y) {
  if (diag_index == 0) return x + y - 1;
  else return y - x + n;
}

int get_diag_y(int diag_index, int x, int diag_id) {
  if (diag_index == 0) return diag_id - x + 1;
  else return diag_id + x - n;
}

pair<int, int> convert(int x, int y) {
  return {get_diag_id(0, x, y), get_diag_id(1, x, y)};
}

int rect_remain_cells(int x, int y, int d) {
  pair<int, int> top_left = convert(x, y - d);
  auto [x1, y1] = top_left;
  pair<int, int> bottom_right = convert(x, y + d);
  auto [x2, y2] = bottom_right;
  return range(x1, y1, x2, y2);
}

vector<int> two_ends(const set<int> &s, int l, int r) {
  if (r < l) swap(l, r);
  vector<int> ret(2, 0);
  auto it = s.lower_bound(l);
  if (it != s.end() and *it <= r) {
    ret[0] = *it;
    auto it = s.upper_bound(r);
    it--;
    ret[1] = *it;
  }
  return ret;
}

pair<int, int> query(int x, int y) {
  const int max_dist = (n - 1) + (m - 1);
  int dL = -1, dR = max_dist;
  int d = dR;
  while (dR - dL > 1) {
    int dM = (dL + dR) / 2;
    if (rect_remain_cells(x, y, dM)) dR = d = dM;
    else dL = dM;
  }

  pair<int, int> ans(n + 1, m + 1);

  for (int diag_index = 0; diag_index < 2; diag_index++) {
    for (int it = 0; it < 2; it++) {
      int xl, xr;
      if (it == diag_index) xl = x - d, xr = x;
      else xl = x, xr = x + d;

      int diag_id = it == 0 ? get_diag_id(diag_index, x, y - d) : get_diag_id(diag_index, x, y + d);
      int tot_diags = get_diag_id(0, n, m);
      if (diag_id <= 0 or tot_diags < diag_id) continue;

      vector<int> end_x = two_ends(diag_remain_x[diag_index][diag_id], xl, xr);
      if (end_x[0] and end_x[1]) {
        for (int it = 0; it < 2; it++) {
          int cur_x = end_x[it];
          int cur_y = get_diag_y(diag_index, cur_x, diag_id);
          pair<int, int> cur(cur_x, cur_y);
          ans = min(ans, cur);
        }
      }
    }
  }

  assert(ans.first <= n and ans.second <= m);
  return ans;
}

void remove(int x, int y) {
  auto [dx, dy] = convert(x, y);
  update(dx, dy, -1);
  diag_remain_x[0][dx].erase(x);
  diag_remain_x[1][dy].erase(x);
}

void init() {
  int tot_diags = get_diag_id(0, n, m);
  fn = fm = tot_diags;
  for (int x = 1; x <= n; x++) {
    for (int y = 1; y <= m; y++) {
      auto [dx, dy] = convert(x, y);
      f[dx][dy] = 1;
      diag_remain_x[0][dx].insert(diag_remain_x[0][dx].end(), x);
      diag_remain_x[1][dy].insert(diag_remain_x[1][dy].end(), x);
    }
  }
  init_bit();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;

  init();

  int q;
  cin >> q;

  for (int cs = 1; cs <= q; cs++) {
    int x, y;
    cin >> x >> y;

    auto [ans_x, ans_y] = query(x, y);
    cout << ans_x << " " << ans_y << "\n";

    remove(ans_x, ans_y);
  }

  return 0;
}