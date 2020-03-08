struct MaxFlow {
	const int INF = int(1e6);
	int n;
	vector<vector<int>> adj;

	MaxFlow(int n) : n(n) {
		adj.resize(n, vector<int>(n, 0));
	}

	int findAugmentedPath(vector<vector<int>> &resd) {
		vector<int> from(n, -1);
		vector<bool> vis(n, false);
		queue<int> q;
		q.push(0);
		vis[0] = true;

		while (!q.empty()) {
			int at = q.front(); q.pop();
			if (at == n - 1) break;

			for (int nxt = 0; nxt < n; nxt++) {
				if (!vis[nxt] && resd[at][nxt] > 0) {
					from[nxt] = at;
					vis[nxt] = true;
					q.push(nxt);
				}
			}
		}

		int path_capacity = INF;
		int at = n - 1;
		while (from[at] != -1) {
			path_capacity = min(path_capacity, resd[from[at]][at]);
			at = from[at];
		}

		at = n - 1;
		while (from[at] != -1) {
			resd[from[at]][at] -= path_capacity;
			resd[at][from[at]] += path_capacity;
			at = from[at];
		}

		return path_capacity;
	}

	int solve() {
		vector<vector<int>> resd = adj;

		int flow = 0;
		while (true) {
			int path_capacity = findAugmentedPath(resd);
			if (path_capacity == INF) break;
			flow += path_capacity;
		}

		// flow in edge (i, j) can be found by max(0, adj[i][j] - resd[i][j])

		return flow;
	}
};