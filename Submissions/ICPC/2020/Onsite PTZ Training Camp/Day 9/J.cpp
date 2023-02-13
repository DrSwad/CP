#include <bits/stdc++.h>

using namespace std;

const int N = 8e3 + 5;

vector<int> g[N];
int match[N];
int _match[N];
bool vis[N];
int n, m;

int convert(int x) {
  return n + x;
}

void dfs(int u) {
  vis[u] = 1;
  if (u <= n) {
    for (auto v : g[u]) {
      if (v != match[u] and !vis[v]) dfs(v);
    }
  } else {
    if (_match[u] and !vis[_match[u]]) dfs(_match[u]);
  }
}

int main() {
  cin >> n >> m;

  for (int i = 1; i <= n; i++) {

    int d, x;
    cin >> d;

    for (int k = 0; k < d; k++) {
      cin >> x;
      x = convert(x);
      g[i].push_back(x);
      g[x].push_back(i);
    }
  }

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    cin >> match[i];

    if (match[i]) {
      ans++;
      match[i] = convert(match[i]);
      _match[match[i]] = i;
    }
    else if (match[i] == 0) vis[i] = 1;
  }

  for (int i = 1; i <= n; i++) {
    if (vis[i]) {
      dfs(i);
    }
  }

  vector<int> ansL, ansR;
  for (int i = 1; i <= n; i++) {
    if (vis[i]) continue;
    ansL.push_back(i);
  }

  for (int i = n + 1; i <= n + m; i++) {
    if (vis[i]) ansR.push_back(i - n);
  }

  cout << ans << '\n';

  cout << ansL.size() << ' ';
  for (int i = 0; i < ansL.size(); i++) cout << ansL[i] << " \n"[i == ansL.size()];
  cout << '\n';
  cout << ansR.size() << ' ';
  for (int i = 0; i < ansR.size(); i++) cout << ansR[i] << " \n"[i == ansR.size()];

}