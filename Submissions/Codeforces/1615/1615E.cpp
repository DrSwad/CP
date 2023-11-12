#include <bits/stdc++.h>
using namespace std;

template<typename T, typename U,
  typename TAssociativeCombineFunction = function<T(const T&, const T&)>,
  typename UAssociativeCombineFunction = function<U(const U&, const U&)>,
  typename UApplicator = function<T(const U&, const T&)>>
struct segment_tree_lazy {
  int SZ;
  T t_identity;
  U u_identity;
  TAssociativeCombineFunction TT;
  UAssociativeCombineFunction UU;
  UApplicator UT;

  std::vector<T> data;
  std::vector<bool> has_update;
  std::vector<U> updates;

  segment_tree_lazy() {}

  segment_tree_lazy(int _SZ,
                    T _t_identity,
                    U _u_identity,
                    TAssociativeCombineFunction _TT,
                    UAssociativeCombineFunction _UU,
                    UApplicator _UT
  )
    : SZ(_SZ), t_identity(_t_identity), u_identity(_u_identity), TT(_TT), UU(_UU), UT(_UT) {
    data.assign(2 * SZ, t_identity);
    has_update.assign(SZ, false);
    updates.assign(SZ, u_identity);
  }

  template<typename Function>
  void assign(Function fn) {
    for (int i = 0; i < SZ; i++) data[SZ + i] = fn(i);
    for (int i = SZ - 1; i; i--) data[i] = TT(data[2 * i], data[2 * i + 1]);
    has_update.assign(SZ, false);
    updates.assign(SZ, u_identity);
  }

private:
  void apply_update(int i, const U &u) {
    data[i] = UT(u, data[i]);
    if (i < SZ) {
      has_update[i] = true;
      updates[i] = UU(u, updates[i]);
    }
  }

  void propagate_ancestor_updates(int i) {
    for (int ht = 31 - __builtin_clz(i); ht > 0; ht--) {
      int anc = i >> ht;
      if (has_update[anc]) {
        apply_update(2 * anc, updates[anc]);
        apply_update(2 * anc + 1, updates[anc]);
        has_update[anc] = false;
        updates[anc] = u_identity;
      }
    }
  }

  void recompute_ancestors(int i) {
    for (i /= 2; i; i /= 2) data[i] = UT(updates[i], TT(data[2 * i], data[2 * i + 1]));
  }

  void modify_leaf(int i, T v, bool overwrite) {
    i += SZ;
    propagate_ancestor_updates(i);
    data[i] = overwrite ? v : TT(data[i], v);
    recompute_ancestors(i);
  }

public:
  // Assigns v at index i
  void assign(int i, T v) {
    modify_leaf(i, v, true);
  }

  // Replaces the current value at index i with TT(current value, v)
  void combine_and_assign(int i, T v) {
    modify_leaf(i, v, false);
  }

  // Applies update u to the elements at indices in [first, last)
  void apply_update(int first, int last, U u) {
    assert(0 <= first && last <= SZ);
    first += SZ, last += SZ;

    propagate_ancestor_updates(first);
    propagate_ancestor_updates(last - 1);

    for (int i = first, j = last; i < j; i /= 2, j /= 2) {
      if (i & 1) apply_update(i++, u);
      if (j & 1) apply_update(--j, u);
    }

    recompute_ancestors(first);
    recompute_ancestors(last - 1);
  }

  // Accumulates the elements at indices in [first, last)
  T accumulate(int first, int last) {
    assert(0 <= first && last <= SZ);
    first += SZ, last += SZ;

    propagate_ancestor_updates(first);
    propagate_ancestor_updates(last - 1);

    T left = t_identity, right = t_identity;
    for (int i = first, j = last; i < j; i /= 2, j /= 2) {
      if (i & 1) left = TT(left, data[i++]);
      if (j & 1) right = TT(data[--j], right);
    }
    return TT(left, right);
  }

  // Returns the current value at index i
  T read(int i) {
    i += SZ;
    propagate_ancestor_updates(i);
    return data[i];
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector adj(n, vector<int>());
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<int> st(n), en(n);
  vector<int> leaves;
  vector<int> depth(n);
  vector<int> parent(n);

  function<void(int, int)> dfs =
    [&](int at, int from) {
      st[at] = leaves.size();
      parent[at] = from;
      depth[at] = from == -1 ? 0 : depth[from] + 1;

      bool is_leaf = true;
      for (int to : adj[at]) {
        if (to != from) {
          is_leaf = false;
          dfs(to, at);
        }
      }

      if (is_leaf) leaves.push_back(at);

      en[at] = leaves.size();
    };

  dfs(0, -1);

  segment_tree_lazy<pair<int, int>, int> tree(
    leaves.size(),
    make_pair(0, -1),
    0,
    [&](pair<int, int> p1, pair<int, int> p2) { return max(p1, p2); },
    [&](int v1, int v2) { return v1 + v2; },
    [&](int v, pair<int, int> p) { return make_pair(p.first + v, p.second); }
  );

  tree.assign([&](int i) { return make_pair(depth[leaves[i]] + 1, leaves[i]); });

  vector<bool> vis(n, false);
  vector<int> max_blue(k + 1);
  max_blue[0] = n;

  for (int red = 1; red <= k; red++) {
    auto [_, leaf] = tree.accumulate(0, leaves.size());

    max_blue[red] = max_blue[red - 1];
    int at = leaf;

    while (at != -1 and !vis[at]) {
      max_blue[red]--;
      vis[at] = true;
      tree.apply_update(st[at], en[at], -1);
      at = parent[at];
    }
  }

  function<long long(int)> get_score =
    [&](int red) {
      int blue = min(max_blue[red], n / 2);
      long long ret = 1ll * (n - red - blue) * (red - blue);
      return ret;
    };

  long long ans = get_score(0);
  for (int red = 1; red <= k; red++) {
    ans = max(ans, get_score(red));
  }

  cout << ans << "\n";

  return 0;
}