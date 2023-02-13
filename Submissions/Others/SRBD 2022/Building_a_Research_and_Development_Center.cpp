#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, q;
struct employee {
  int id, seniority;
  employee() {}
  employee(int id, int seniority) : id(id), seniority(seniority) {}
  bool operator<(const employee &other) const {
    if (seniority != other.seniority) return seniority < other.seniority;
    return id < other.id;
  }
};
string to_string(const employee &e) {
  return to_string(e.id) + ", " + to_string(e.seniority);
}
vector<employee> e;
vector<set<employee>> teams;

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
    for (const employee &i : teams[y]) {
      teams[x].insert(i);
    }
    teams[y].clear();
    p[x] += p[y];
    p[y] = x;
    return true;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> q;
  e.resize(n), teams.resize(n);

  for (int i = 0; i < n; i++) {
    int id;
    cin >> id;
    e[i].id = i;
    e[id].seniority = (n - 1) - i;
  }

  for (int i = 0; i < n; i++) {
    teams[i].insert(e[i]);
  }

  DSU dsu(n);

  while (q--) {
    int type;
    cin >> type;

    if (type == 1) {
      int a, b;
      cin >> a >> b;
      dsu.merge(a, b);
    }
    else if (type == 2) {
      int x;
      cin >> x;
      int p = dsu.root(x);
      teams[p].erase(e[x]);
      e[x].seniority++;
      teams[p].insert(e[x]);
    }
    else {
      int y;
      cin >> y;
      int p = dsu.root(y);
      cout << (*teams[p].rbegin()).id << "\n";
    }

    /* DB();
       for (int i = 0; i < n; i++) {
       cerr << i << endl;
       for (auto it = teams[i].begin(); it != teams[i].end(); it++) {
        cerr << to_string(*it) << "\n";
       }
       } */
  }

  return 0;
}