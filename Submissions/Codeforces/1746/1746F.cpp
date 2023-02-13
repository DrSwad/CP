#include <bits/stdc++.h>
using namespace std;

const int TRIES = 30;

template<class T>
class BIT {
public:
  int n;
  vector<T> f;
  BIT(int n) : n(n) {
    f.resize(n + 1, (T)0);
  }
  BIT(const vector<T> &a) { // O(n)
    n = a.size();
    f.assign(n + 1, (T)0);
    for (int i = 1; i <= n; i++) {
      f[i] += a[i - 1];
      if (i + (i & -i) <= n) {
        f[i + (i & -i)] += f[i];
      }
    }
  }
  void update(int p, T v) {
    while (p <= n) f[p] += v, p += p & -p;
  }
  T pref(int p) {
    T ret = 0;
    while (p) ret += f[p], p -= p & -p;
    return ret;
  }
  T range(int l, int r) {
    return pref(r) - pref(l - 1);
  }
};

// Returns a vector of the sorted unique elements
// If update_a is true, then changes the elements in a to the corresponding compressed values
template<typename T>
vector<T> compress(vector<T> &a, bool update_a = true) {
  int n = a.size();
  vector<pair<T, int>> pairs(n);
  for (int i = 0; i < n; ++i) {
    pairs[i] = {a[i], i};
  }
  sort(pairs.begin(), pairs.end());
  vector<T> ret;
  int at = 0;
  for (int i = 0; i < n; i++) {
    if (update_a) a[pairs[i].second] = at;
    if (i == n - 1 or pairs[i].first != pairs[i + 1].first) at++;
    if (i == 0 or pairs[i].first != pairs[i - 1].first) {
      ret.push_back(pairs[i].first);
    }
  }
  return ret;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> uid(0, 1);
auto gen = bind(uid, rng);

struct Query {
  int type;
  int i, x;
  int l, r, k;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<int> coords = a;
  vector<Query> queries(q);
  for (Query &qq : queries) {
    cin >> qq.type;
    if (qq.type == 1) {
      cin >> qq.i >> qq.x;
      qq.i--;
      coords.push_back(qq.x);
    }
    else {
      cin >> qq.l >> qq.r >> qq.k;
    }
  }

  vector<int> vals = compress(coords);
  int sz = vals.size();

  vector<vector<bool>> sets(TRIES, vector<bool>(sz, false));
  for (int i = 0; i < TRIES; i++) {
    for (int j = 0; j < sz; j++) {
      sets[i][j] = gen();
    }
  }

  vector<BIT<int>> bit(TRIES, n);
  for (int i = 0; i < n; i++) {
    a[i] = coords[i];
    for (int j = 0; j < TRIES; j++) {
      if (sets[j][a[i]]) {
        bit[j].update(i + 1, 1);
      }
    }
  }

  int it = n;
  for (int i = 0; i < q; i++) {
    const Query &qq = queries[i];
    if (qq.type == 1) {
      assert(it < coords.size());
      int prv_val = a[qq.i];
      int new_val = coords[it++];
      a[qq.i] = new_val;
      for (int j = 0; j < TRIES; j++) {
        if (sets[j][prv_val]) bit[j].update(qq.i + 1, -1);
        if (sets[j][new_val]) bit[j].update(qq.i + 1, 1);
      }
    }
    else {
      bool ans = true;
      for (int j = 0; j < TRIES; j++) {
        ans = ans and bit[j].range(qq.l, qq.r) % qq.k == 0;
      }
      cout << (ans ? "YES" : "NO") << "\n";
    }
  }

  assert(it == coords.size());

  return 0;
}
