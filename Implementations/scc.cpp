#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<vii> viii;

class SCC {
private:
	int n;
	viii adj;
	vector<bool> vis;
	stack<int> st;
	vector<int> comp;
	bool foundSCC;

	void dfs(int at, int source, int mode) {
		vis[at] = true;
		if (mode == 1) comp[at] = source;
		for (int to : adj[mode][at]) if (!vis[to]) dfs(to, source, mode);
		if (mode == 0) st.push(at);
	}
public:
	SCC(int _n, viii _adj) {
		n = _n;
		adj = _adj;
		vis.resize(n + 1, false);
		comp.resize(n + 1, 0);
		foundSCC = false;
	}

	vector<int> findComponents() {
		if (foundSCC) return comp;
		for (int i = 1; i <= n; i++) if (!vis[i]) dfs(i, 0, 0);
		fill(vis.begin(), vis.end(), false);
		while (!st.empty()) {
			int source = st.top(); st.pop();
			if (!vis[source]) dfs(source, source, 1);
		}

		foundSCC = true;
		return comp;
	}
};

int main() {
	int n, m;
	cin >> n >> m;
	viii adj(2, vii(n + 1));
	while (m--) {
		int u, v;
		scanf("%d %d", &u, &v);
		adj[0][u].push_back(v);
		adj[1][v].push_back(u);
	}
	SCC scc = SCC(n, adj);
	vector<int> comp = scc.findComponents();
	return 0;
}