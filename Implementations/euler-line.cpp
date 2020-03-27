vector<int> line;
int h[N], s[N], e[N];

void dfs(int at, int p) {
	h[at] = h[p] + 1;

	line.push_back(at);
	s[at] = line.size();

	for (int to : adj[at]) {
		if (to != p) dfs(to, at);
	}

	line.push_back(at);
	e[at] = line.size();
}