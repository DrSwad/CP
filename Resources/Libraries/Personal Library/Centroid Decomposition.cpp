const int MAX = 1e5 + 5;
int nn; bool isCentroid[MAX]; int sub[MAX]; // internal, won't need anymore
vector<int> ed[MAX]; // original graph adjacency list
int cpar[MAX]; // parent node in CD graph
int clevel[MAX]; // level in CD graph
int dis[20][MAX]; // distance of node from the centroid at i'th level
void calcSubTree(int s, int p) {
	sub[s] = 1;
	for(int x : ed[s]) {
		if(x == p or isCentroid[x]) continue;
		calcSubTree(x, s);
		sub[s] += sub[x];
	}
}
int getCentroid(int s, int p) {
	for(int x : ed[s]) {
		if(!isCentroid[x] && x != p && sub[x] > (nn / 2)) return getCentroid(x, s);
	}
	return s;
}
void setDis(int s, int from, int p, int lev) {
	dis[from][s] = lev;
	for(int x : ed[s]) {
		if(x == p or isCentroid[x]) continue;
		setDis(x, from, s, lev + 1);
	}
}
void decompose(int s, int p, int lev) {
	calcSubTree(s, p); nn = sub[s];
	int c = getCentroid(s, p);
	setDis(c, lev, p, 0);
	/*
		for offline setDis() not needed,
		query() a child of c, add() that
		child to the global ds, reverse the
		edge list and do the same thing
		again, query and add are two dfs
		basically
	*/
	isCentroid[c] = true; cpar[c] = p; clevel[c] = lev;
	for(int x : ed[c]) {
		if(!isCentroid[x]) decompose(x, c, lev + 1);
	}
}
// nn = n; decompose(1, -1, 0)