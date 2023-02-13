#include <bits/stdc++.h>
using namespace std;

// const int N = 2e5 + 5;
const int N = 2e5 + 5;

vector<int> adj[N];

int dp[N], pth[N];

int dfs(int u)
{
  if (dp[u] != -1) return dp[u];
  dp[u] = 1;
  for (int i = 0; i < adj[u].size(); i++)
  {
    int v = adj[u][i];
    printf("%d %d\n", u, v);
    if (1 + dfs(v) > dp[u])
    {
      dp[u] = 1 + dp[v];
      pth[u] = v;
    }
  }
  return dp[u];
}

int top_sorted[N];

void topsort(int n) {
  vector<int> out_deg(n, 0);
  vector<vector<int>> in_edges(n);
  for (int i = 0; i < n; i++) {
    out_deg[i] = adj[i].size();
    for (int j : adj[i]) {
      in_edges[j].push_back(i);
    }
  }

  vector<int> ret;

  queue<int> q;
  for (int i = 0; i < n; i++) {
    if (out_deg[i] == 0) {
      q.push(i);
    }
  }

  while (!q.empty()) {
    int i = q.front(); q.pop();
    ret.push_back(i);
    for (int j : in_edges[i]) {
      out_deg[j]--;
      if (out_deg[j] == 0) {
        q.push(j);
      }
    }
  }

  for (int i = 0; i < n; i++) {
    top_sorted[i] = ret[i];
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  scanf("%d", &n);
  int ar1[n + 5], ar2[n + 5], br[n + 5];
  memset(br, -1, sizeof(br));
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &ar1[i]);
    if (br[ar1[i]] != -1)
    {
      adj[i].push_back(br[ar1[i]]);
    }
    if (br[ar1[i] - 1] != -1)
    {
      adj[br[ar1[i] - 1]].push_back(i);
    }
    if (br[ar1[i] + 1] != -1)
    {
      adj[i].push_back(br[ar1[i] + 1]);
    }
    br[ar1[i]] = i;
  }
  memset(br, -1, sizeof(br));
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &ar2[i]);
  }
  for (int i = n - 1; i >= 0; i--)
  {
    if (br[ar2[i]] != -1)
    {
      adj[i].push_back(br[ar2[i]]);
    }
    if (br[ar2[i] - 1] != -1)
    {
      adj[br[ar2[i] - 1]].push_back(i);
    }
    if (br[ar2[i] + 1] != -1)
    {
      adj[i].push_back(br[ar2[i] + 1]);
    }
    br[ar2[i]] = i;
  }
  topsort(n);
  int ans[n + 5];
  for (int i = n - 1; i >= 0; i--)
  {
    ans[top_sorted[i]] = n - i;
  }
  for (int i = 0; i < n; i++)
  {
    if (i == n - 1)
    {
      printf("%d\n", ans[i]);
      exit(0);
    }
    printf("%d ", ans[i]);
  }
  return 0;
}