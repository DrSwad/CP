#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse4.2,bmi,bmi2,popcnt,lzcnt")

#include <bits/stdc++.h>

using ll = int64_t;
using ull = uint64_t;
using ld = long double;

struct identity {
  template<class T>
  constexpr T operator()(const T&x) const {
    return x;
  }
};

// sort strings of different lengths in time O(total length + max value)
// return permutation as well as the sorted string
template<class T, class U, class F = identity>
auto sort_strings(const std::vector<T>&a, U max_value, F&&mapping = {}) {
  static_assert(
    std::is_same<
      std::remove_cv_t<std::remove_reference_t<decltype(a[0][0])>>, U>{}
    );
  using V = std::basic_string<int>;

  int max_length = 0;
  for (const auto&s : a) max_length = std::max(max_length, (int)s.size());
  int total_length = 0;
  for (const auto&s : a) total_length += (int)s.size();
  int max_value_mapped = mapping(max_value);

  std::vector<V> non_empty(max_length);
  {
    std::vector<std::pair<int, int>> pairs;
    pairs.reserve(total_length);
    for (const auto&s : a)
      for (int i = 0; i < (int)s.size(); ++i) pairs.emplace_back(i, mapping(s[i]));
    std::vector<std::pair<int, int>> buf(total_length);
    std::vector<int> cnt(std::max(max_length, max_value_mapped + 1));
    for (auto [l, x] : pairs) ++cnt[x];
    for (int i = 1; i <= max_value_mapped; ++i) cnt[i] += cnt[i - 1];
    for (int i = (int)pairs.size() - 1; i >= 0; --i) {
      const auto&p = pairs[i];
      buf[--cnt[p.second]] = p;
    }
    std::fill(
      cnt.begin(),
      cnt.begin() + std::min(max_length, max_value_mapped + 1),
      0
      );
    for (auto [l, x] : buf) ++cnt[l];
    for (int i = 1; i < max_length; ++i) cnt[i] += cnt[i - 1];
    for (int i = (int)buf.size() - 1; i >= 0; --i) {
      const auto&p = buf[i];
      pairs[--cnt[p.first]] = p;
    }
    int count_unique =
      int(std::unique(pairs.begin(), pairs.end()) - pairs.begin());
    pairs.resize(count_unique);
    for (int i = 0; i < count_unique; ++i) non_empty[pairs[i].first].push_back(pairs[i].second);
  }

  std::vector<V> strings_of_length(max_length + 1);
  for (int i = 0; i < (int)a.size(); ++i) strings_of_length[a[i].size()].push_back(i);

  std::vector<V> q(mapping(max_value) + 1);
  std::queue<int> Q;

  for (int l = max_length; l >= 1; --l) {
    for (auto string_id : strings_of_length[l]) q[mapping(a[string_id][l - 1])].push_back(string_id);
    while (!Q.empty()) {
      int string_id = Q.front();
      Q.pop();
      q[mapping(a[string_id][l - 1])].push_back(string_id);
    }
    for (auto j : non_empty[l - 1]) {
      for (auto string_id : q[j]) Q.push(string_id);
      q[j].clear();
    }
  }

  std::vector<V> ans(a.size());
  std::vector<int> p(a.size());
  int i = 0;
  for ( ; i < (int)strings_of_length[0].size(); ++i) ans[i] = a[strings_of_length[0][i]], p[i] = strings_of_length[0][i];
  while (!Q.empty()) {
    p[i] = Q.front();
    ans[i] = a[Q.front()];
    ++i;
    Q.pop();
  }
  return std::pair{p, ans};
}

template<class G>
auto compute_levelwise_representation(const G&tree, int root) {
  using L = std::basic_string<int>;
  using V = std::vector<L>;

  int n = (int)tree.size();
  std::vector<int> parent(n);

  std::vector<V> level_representation;
  std::vector<L> vertices_at_level;

  auto dfs = [&](const auto&self, int u, int p, int l) -> void {
    if ((int)vertices_at_level.size() == l) vertices_at_level.emplace_back();
    vertices_at_level[l].push_back(u);
    parent[u] = p;
    for (auto v : tree[u])
      if (v != p) self(self, v, u, l + 1);
  };
  dfs(dfs, root, -1, 0);
  level_representation.resize(vertices_at_level.size());

  using U = std::basic_string<int>;
  std::vector<std::pair<int, U>> vertex_representation(n);

  std::vector<int> sorted_level;
  for (int level = (int)vertices_at_level.size() - 1; level >= 0; --level) {
    for (auto u : sorted_level) vertex_representation[parent[u]].second.push_back(
        vertex_representation[u].first
        );

    int max_value = 0;
    for (auto u : vertices_at_level[level]) {
      const auto&v = vertex_representation[u].second;
      level_representation[level].push_back(v);
      max_value = std::max(max_value, *max_element(v.begin(), v.end()));
    }
    auto [permutation, sorted] =
      sort_strings(level_representation[level], max_value);

    sorted_level.clear();
    int rank = -1;
    for (int i = 0; i < (int)permutation.size(); ++i) {
      if (i == 0 || sorted[i] != sorted[i - 1]) ++rank;
      int v = vertices_at_level[level][permutation[i]];
      vertex_representation[v].first = rank;
      sorted_level.push_back(v);
    }
    level_representation[level] = std::move(sorted);
  }

  return std::pair{vertex_representation[root].first, level_representation};
}

using namespace std;

vector<int> centroids(const vector<vector<int>> &g) {
  int n = (int)g.size();
  vector<int> centroid;
  vector<int> sz(n);
  auto dfs = [&](const auto&self, int u, int p) -> void {
    sz[u] = 1;
    bool is_centroid = true;
    for (auto v : g[u])
      if (v != p) {
        self(self, v, u);
        sz[u] += sz[v];
        if (sz[v] > n / 2) is_centroid = false;
      }
    if (n - sz[u] > n / 2) is_centroid = false;
    if (is_centroid) centroid.push_back(u);
  };
  dfs(dfs, 0, -1);
  return centroid;
}

bool check_isomorphism(int n, const vector<vector<int>> &a, const vector<vector<int>> &b) {
  auto c_a = centroids(a);
  auto c_b = centroids(b);
  assert(c_a.size() <= 2);
  assert(c_b.size() <= 2);
  if (c_a.size() != c_b.size()) {
    return false;
  } else if (compute_levelwise_representation(a, c_a[0]) ==
             compute_levelwise_representation(b, c_b[0])
             ) {
    return true;
  } else if (c_a.size() == 2 &&
             compute_levelwise_representation(a, c_a[1]) ==
             compute_levelwise_representation(b, c_b[0])
             ) {
    return true;
  } else {
    return false;
  }
}

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

// For windows system use getchar() instead of getchar_unlocked()
inline int input_int() {
  int ret = 0, flag = 1, ip = getchar();
  for ( ; ip < 48 || ip > 57; ip = getchar()) {
    if (ip == 45) {
      flag = -1;
      ip = getchar();
      break;
    }
  }
  for ( ; ip > 47 && ip < 58; ip = getchar()) ret = ret * 10 + ip - 48;
  return flag * ret;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAX_CHECKS = 15;

void test_case() {
  int n = input_int(), m = input_int();

  vector<pair<int, int>> e(m);
  for (auto & [u, v] : e) {
    u = input_int(), v = input_int();
    u--, v--;
  }

  function<vector<vector<int>>()> make_tree = [&]() {
    shuffle(e.begin(), e.end(), rng);
    vector<vector<int>> adj(n);
    DSU dsu(n);
    for (auto [u, v] : e) {
      if (!dsu.same(u, v)) {
        dsu.merge(u, v);
        adj[u].push_back(v);
        adj[v].push_back(u);
      }
    }
    return adj;
  };

  vector<vector<int>> t1 = make_tree();
  for (int it = 0; it < MAX_CHECKS; it++) {
    vector<vector<int>> t2 = make_tree();
    if (!check_isomorphism(n, t1, t2)) {
      printf("NO\n");
      return;
    }
  }
  printf("YES\n");
}

int main() {
  // ios::sync_with_stdio(false);
  // cin.tie(nullptr);

  int t = input_int();

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}