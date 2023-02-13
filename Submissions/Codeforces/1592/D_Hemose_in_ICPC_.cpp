#include <bits/stdc++.h>
using namespace std;

int query(const vector<int> &v) {
  cout << "? " << v.size();
  for (int i : v) cout << " " << i;
  cout << endl;
  int res;
  cin >> res;
  return res;
}

void answer(int a, int b) {
  cout << "! " << a << " " << b << endl;
  exit(EXIT_SUCCESS);
}

const int N = 1e3 + 5;

int n;
vector<int> e[N];
int p[N];
vector<int> line;
int G;

void dfs(int at, int from = 0) {
  p[at] = from;
  line.push_back(at);
  for (int to : e[at]) {
    if (to != from) {
      dfs(to, at);
    }
  }
  line.push_back(at);
}

bool check(int till) {
  vector<int> nodes(line.begin(), line.begin() + till + 1);
  sort(nodes.begin(), nodes.end());
  nodes.resize(unique(nodes.begin(), nodes.end()) - nodes.begin());
  return G == query(nodes);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    e[u].push_back(v);
    e[v].push_back(u);
  }

  dfs(1);

  vector<int> all_nodes(n);
  iota(all_nodes.begin(), all_nodes.end(), 1);
  G = query(all_nodes);

  int L = 1, R = (int)line.size() - 1;
  while (L != R) {
    int m = (L + R) / 2;
    if (check(m)) R = m;
    else L = m + 1;
  }

  answer(p[line[L]], line[L]);

  return 0;
}