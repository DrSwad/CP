#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n, m, k;
  cin >> n >> m >> k;

  vector<int> h(n);
  for (int &i : h) cin >> i;

  vector<vector<int>> parents(n), children(n);
  vector<int> in_degree(n, 0);

  for (int i = 0; i < m; i++) {
    int from, to;
    cin >> from >> to;
    from--, to--;
    in_degree[to]++;
    parents[to].push_back(from);
    children[from].push_back(to);
  }

  vector<ll> H(n);
  vector<int> roots;
  queue<int> q;

  for (int i = 0; i < n; i++) {
    if (in_degree[i] == 0) {
      H[i] = h[i];
      roots.push_back(i);
      q.push(i);
    }
  }

  while (!q.empty()) {
    int at = q.front();
    q.pop();

    for (int to : children[at]) {
      in_degree[to]--;
      if (in_degree[to] == 0) {
        ll max_parent_H = 0;
        for (int p : parents[to]) {
          max_parent_H = max(max_parent_H, H[p]);
        }

        ll div = max_parent_H / k * k;
        int r = max_parent_H % k;

        if (r <= h[to]) H[to] = div + h[to];
        else H[to] = div + k + h[to];

        q.push(to);
      }
    }
  }

  vector<int> update_at(n, -1);
  vector<vector<int>> updates_at_root(n);
  for (int i = 0; i < n; i++) {
    in_degree[i] = parents[i].size();
    if (in_degree[i] == 0) {
      update_at[i] = i;
      updates_at_root[i].push_back(i);
      q.push(i);
    }
  }

  while (!q.empty()) {
    int at = q.front();
    q.pop();

    for (int to : children[at]) {
      in_degree[to]--;
      if (in_degree[to] == 0) {
        vector<pair<int, ll>> parent_updates;
        for (int p : parents[to]) {
          parent_updates.emplace_back(update_at[p], H[p]);
        }

        sort(
          parent_updates.begin(),
          parent_updates.end(),
          [&](const auto &i1, const auto &i2) {
            auto [root1, H1] = i1;
            auto [root2, H2] = i2;
            return make_pair(H[root1], H1) < make_pair(H[root2], H2);
          }
        );

        for (auto [root, parent_H] : parent_updates) {
          ll new_parent_H = parent_H + k;
          ll div = new_parent_H / k * k;
          int r = new_parent_H % k;
          ll new_H;
          if (r <= h[to]) new_H = div + h[to];
          else new_H = div + k + h[to];
          if (new_H > H[to]) {
            update_at[to] = root;
            updates_at_root[root].push_back(to);
            break;
          }
        }

        assert(update_at[to] != -1);

        q.push(to);
      }
    }
  }

  sort(
    roots.begin(),
    roots.end(),
    [&](int root1, int root2) {
      return H[root1] < H[root2];
    }
  );

  multiset<ll> ms;
  for (int i = 0; i < n; i++) ms.insert(H[i]);

  ll ans = LLONG_MAX;
  for (int root : roots) {
    ans = min(ans, *ms.rbegin() - H[root]);
    for (int i : updates_at_root[root]) {
      ms.erase(ms.find(H[i]));
      ms.insert(H[i] + k);
    }
  }

  cout << ans << "\n";
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