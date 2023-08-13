#include <bits/stdc++.h>
using namespace std;

struct Trie {
  const int A = 26;
  int N;
  vector<vector<int>> next;
  vector<int> values;

  Trie() : N() {
    node(0);
  }

  int node(int val) {
    values.push_back(val);
    next.emplace_back(A, -1);
    return N++;
  }

  inline int get(char c) {
    return c - 'a';
  }

  inline void insert(string s) {
    int cur = 0;
    for (char c : s) {
      int to = get(c);
      if (next[cur][to] == -1) next[cur][to] = node(to + 1);
      cur = next[cur][to];
    }
  }
};

const int N = 1e5 + 5;
int sz, a[N], lazy[N << 2];
pair<int, int> tree[N << 2];

// build
void init(int u = 1, int b = 1, int e = sz) {
  lazy[u] = 0; // modify
  if (b == e) return void(tree[u] = {a[b], b});
  int mid = b + e >> 1;
  init(u << 1, b, mid), init(u << 1 | 1, mid + 1, e);
  tree[u] = max(tree[u << 1], tree[u << 1 | 1]); // modify
}

// clear lazy value at node u
inline void push(int u, int b, int e) {
  tree[u].first += lazy[u];                                         // modify
  if (b != e) lazy[u << 1] += lazy[u], lazy[u << 1 | 1] += lazy[u]; // modify
  lazy[u] = 0;                                                      // modify
}

// add v on range [l, r]
void update(int l, int r, int v, int u = 1, int b = 1, int e = sz) {
  if (lazy[u]) push(u, b, e); // modify
  if (b > r or e < l) return;
  if (b >= l and e <= r) {
    lazy[u] += v; // modify
    return push(u, b, e);
  }
  int mid = b + e >> 1;
  update(l, r, v, u << 1, b, mid), update(l, r, v, u << 1 | 1, mid + 1, e);
  tree[u] = max(tree[u << 1], tree[u << 1 | 1]); // modify
}

// range [l, r] sum
pair<int, int> query(int l, int r, int u = 1, int b = 1, int e = sz) {
  if (b > r or e < l) return {-1, -1}; // modify
  if (lazy[u]) push(u, b, e); // modify
  if (b >= l and e <= r) return tree[u];
  int mid = b + e >> 1;
  return max(
    query(l, r, u << 1, b, mid),
    query(l, r, u << 1 | 1, mid + 1, e)
  );                                        // modify
}

void test_case() {
  int n, k;
  cin >> n >> k;

  Trie trie;
  while (n--) {
    string s;
    cin >> s;
    trie.insert(s);
  }

  vector<int> l(trie.N), r(trie.N);
  vector<int> parent(trie.N), leaf_nodes, leaf_values;

  function<void(int, int)> dfs =
    [&](int at, int val) {
      val += trie.values[at];
      l[at] = leaf_nodes.size();
      bool is_leaf = true;

      for (int c = 0; c < trie.A; c++) {
        int to = trie.next[at][c];
        if (to != -1) {
          is_leaf = false;
          parent[to] = at;
          dfs(to, val);
        }
      }

      if (is_leaf) {
        leaf_nodes.push_back(at);
        leaf_values.push_back(val);
      }

      r[at] = (int)leaf_nodes.size() - 1;
    };

  parent[0] = -1;
  dfs(0, 0);

  sz = leaf_values.size();
  for (int i = 1; i <= sz; i++) a[i] = leaf_values[i - 1];

  init();

  int ans = 0;
  vector<bool> visited(trie.N, false);

  for (int _ = 0; _ < min(k, sz); _++) {
    auto [sum, at] = query(1, sz);
    ans += sum;
    at = leaf_nodes[at - 1];

    while (at != -1 and !visited[at]) {
      update(l[at] + 1, r[at] + 1, -trie.values[at]);
      visited[at] = true;
      at = parent[at];
    }
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