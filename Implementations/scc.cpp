#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, m;
vector<int> adj[N][2];

bool vis[N];
stack<int> st;
int comp[N];

void dfs(int at, int source, int mode) {
	vis[at] = true;

	if (mode == 1) comp[at] = source;

	for (int to : adj[at][mode])
		if (!vis[to])
			dfs(to, source, mode);

	if (mode == 0) st.push(at);
}

int main() {
	cin >> n >> m;

	while (m--) {
		int u, v;
		scanf("%d %d", &u, &v);

		adj[u][0].push_back(v);
		adj[v][1].push_back(u);
	}

	for (int i = 1; i <= n; i++)
		if (!vis[i])
			dfs(i, 0, 0);

	memset(vis, 0, sizeof vis);

	while (!st.empty()) {
		int source = st.top();
		st.pop();
		if (!vis[source])
			dfs(source, source, 1);
	}

	return 0;
}