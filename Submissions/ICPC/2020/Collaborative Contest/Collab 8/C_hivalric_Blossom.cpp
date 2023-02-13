#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, m;
int e[N];
bool vis[N];
vector<int> seq[N];
vector<pair<int, int>> p;
int color[N];
int col;

void color_seq(int from) {
  int prv = 0;
  for (int at : seq[from]) {
    if (prv > at) col++;
    prv = at;
    color[at] = col;
  }
}

int main() {
  cin >> n >> m;

  while (m--) {
    int l, r;
    scanf("%d %d", &l, &r);
    e[l] = r;
  }

  for (int from = 1; from <= n; from++) {
    if (!vis[from]) {
      int to;
      for (to = from; e[to]; to = e[to]) {
        vis[to] = true;
        seq[from].push_back(to);
      }
      vis[to] = true;
      seq[from].push_back(to);
      p.emplace_back(from, to);
    }
  }

  vector<int> order(p.size());
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int i, int j) {
    return p[i].second < p[j].second;
  });

  vector<int> froms;
  for (auto [from, to] : p) froms.push_back(from);
  set<int> available(froms.begin(), froms.end());

  for (int id : order) {
    auto [from, to] = p[id];
    if (!available.count(from)) continue;
    col++;

    color_seq(from);
    available.erase(from);
    auto it = available.upper_bound(to);

    while (it != available.end()) {
      from = *it;
      int to = seq[from].back();
      color_seq(from);
      available.erase(from);
      it = available.upper_bound(to);
    }
  }

  for (int i = 1; i <= n; i++) {
    if (i > 1) printf(" ");
    printf("%d", color[i]);
  }

  return 0;
}