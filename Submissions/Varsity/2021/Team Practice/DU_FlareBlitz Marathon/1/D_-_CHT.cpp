#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
#define x first
#define y second

// Line = pair (m, c) for a line y = mx + c
// Queries for minimum
// Make sure lines are inserted in non-increasing order
template<typename T, class Line = pair<T, T>> // Make sure multiplications fit in T
class CHT {
private:
  vector<Line> lines;
public:
  CHT() {}
  void addLine(Line line) {
    line.first = -line.first, line.second = -line.second;
    lines.push_back(line);
  }
  void build() {
    sort(lines.begin(), lines.end());
    vector<pll> _lines = lines;
    lines.clear();
    for (pll line : _lines) insert(line);
  }
  T query(const T &x) {
    if (lines.empty()) return LLONG_MAX;
    // assert(!lines.empty());

    int L = 0, R = lines.size() - 1;
    while (L != R) {
      int mid1 = L + (R - L) / 3;
      int mid2 = R - (R - L) / 3;
      if (lines[mid1].x * x + lines[mid1].y
          >= lines[mid2].x * x + lines[mid2].y
          ) R = mid2 - 1;
      else L = mid1 + 1;
    }

    T res = lines[L].x * x + lines[L].y;
    return -res;
  }
private:
  bool bad(const Line &line1, const Line &line2, const Line &line3) {
    return __int128(line3.y - line1.y) * __int128(line1.x - line2.x)
           <= __int128(line2.y - line1.y) * __int128(line1.x - line3.x);
  }
  void insert(const Line &line) {
    while (lines.size() > 0 && lines.back().x == line.x) lines.pop_back();
    lines.push_back(line);
    int sz = lines.size();
    while (sz >= 3 && bad(lines[sz - 3], lines[sz - 2], lines[sz - 1])) {
      lines.erase(lines.end() - 2);
      sz--;
    }
  }
};

int tot_q, qi;
vector<int> line_last_inserted_at;
vector<tuple<int, int, ll>> queries;

vector<CHT<ll>> st;
void build(int stI, int L, int R) {
  st[stI].build();

  if (L == R) return;

  int mid = (L + R) / 2;
  build((stI << 1), L, mid);
  build((stI << 1) + 1, mid + 1, R);
}
void build() {
  build(1, 1, tot_q);
}
void insert(int stI, int L, int R, int l, int r, pll val) {
  if (r < L || R < l) return;
  if (l <= L && R <= r) {
    st[stI].addLine(val);
    return;
  }

  int mid = (L + R) / 2;
  insert((stI << 1), L, mid, l, r, val);
  insert((stI << 1) + 1, mid + 1, R, l, r, val);
}
void insert(int l, int r, pll val) {
  insert(1, 1, tot_q, l, r, val);
}
ll query(int stI, int L, int R, int at, int x) {
  if (at < L || R < at) return LLONG_MAX;
  if (L == R) return st[stI].query(x);

  ll ret = st[stI].query(x);
  int mid = (L + R) / 2;
  ret = min(ret, query((stI << 1), L, mid, at, x));
  ret = min(ret, query((stI << 1) + 1, mid + 1, R, at, x));
  return ret;
}
ll query(int at, int x, ll c) {
  return query(1, 1, tot_q, at, x) + c;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  qi = 1;
  tot_q = 2 + m * 3;
  line_last_inserted_at.resize(n + 1);
  vector<pll> lines(n + 1);
  st.resize(4 * tot_q + 1);

  for (int i = 1; i <= n; i++) {
    ll s, p;
    cin >> s >> p;
    lines[i] = {-2 * s, s * s + p};
    line_last_inserted_at[i] = qi;
  }
  qi++;

  for (int i = 1; i <= m; i++) {
    ll c, k;
    cin >> c >> k;

    vector<int> d;
    if (k) {
      d.resize(k);
      for (int &i : d) cin >> i;

      for (int i : d) {
        insert(line_last_inserted_at[i], qi, lines[i]);
        line_last_inserted_at[i] = -1;
      }
    }
    qi++;

    queries.push_back({qi, c, c * c});
    qi++;

    if (k > 0) {
      for (int i : d) {
        line_last_inserted_at[i] = qi;
      }
    }
    qi++;
  }

  for (int i = 1; i <= n; i++) {
    insert(line_last_inserted_at[i], qi, lines[i]);
  }

  assert(qi == tot_q);

  build();

  for (auto p : queries) {
    int qi = get<0>(p);
    int x = get<1>(p);
    ll c = get<2>(p);
    ll ans = query(qi, x, c);
    assert(ans < LLONG_MAX);
    cout << ans << "\n";
  }

  return 0;
}