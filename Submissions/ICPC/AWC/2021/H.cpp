#include <bits/stdc++.h>
using namespace std;

template<typename T, typename U,
  typename TAssociativeCombineFunction,
  typename UAssociativeCombineFunction,
  typename UApplicator>
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

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i, i--;

  segment_tree_lazy tree(
    n,
    pair<int, int>{INT_MAX, 0},
    0,
    [&](pair<int, int> t1, pair<int, int> t2) {
      if (t1.first < t2.first) return t1;
      else if (t2.first < t1.first) return t2;
      else return pair<int, int>{t1.first, t1.second + t2.second};
    },
    [&](int u1, int u2) {
      return u1 + u2;
    },
    [&](int u, pair<int, int> t) {
      return pair<int, int>{t.first + u, t.second};
    }
  );

  tree.assign([&](int i) { return pair<int, int>(0, 1); });

  vector pos(n, vector(1, -1));
  long long ans = 0;

  for (int i = 0; i < n; i++) {
    int sz = pos[a[i]].size();
    int p2 = 1;
    while (sz - p2 - 1 >= 0) {
      tree.apply_update(pos[a[i]][sz - p2 - 1] + 1, pos[a[i]][sz - p2] + 1, 1);
      p2 *= 2;
    }

    pos[a[i]].push_back(i);
    sz = pos[a[i]].size();
    p2 = 1;
    tree.apply_update(pos[a[i]][sz - p2 - 1] + 1, pos[a[i]][sz - p2] + 1, 1);

    p2 = 1;
    while (sz - p2 - 1 >= 0) {
      tree.apply_update(pos[a[i]][sz - p2 - 1] + 1, pos[a[i]][sz - p2] + 1, -1);
      p2 *= 2;
    }

    auto [mn, freq] = tree.accumulate(0, i + 1);
    if (mn == 0) ans += freq;
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}