#include <bits/stdc++.h>

using namespace std;

const int MAX = 100010;
const int INF = 2e9;

vector <int> ed[MAX]; /// adjacency list of the input tree
bool isCentroid[MAX]; /// if the node is already a centroid of some part
int sub[MAX], cpar[MAX], clevel[MAX];
int dis[20][MAX]; /// dis[i][j] = distance of node j from the root of the i'th level of decomposition

void calcSubTree(int s,int p) {
    sub[s] = 1;
    for(int x : ed[s]) {
        if(x == p or isCentroid[x]) continue;
        calcSubTree(x,s);
        sub[s] += sub[x];
    }
}

int nn; /// number of nodes in the part

int getCentroid(int s,int p) {
    for(int x : ed[s]) {
        if(!isCentroid[x] && x!=p && sub[x]>(nn/2)) return getCentroid(x,s);
    }
    return s;
}

void setDis(int s, int from, int p, int lev) {
    dis[from][s] = lev;
    for(int x : ed[s]) {
        if(x == p or isCentroid[x] )  continue;
        setDis(x, from, s, lev+1);
    }
}

///complexity --> O(nlog(n))
void decompose(int s,int p,int lev) {
    calcSubTree(s,p);
    nn = sub[s];
    int c = getCentroid(s,p);
    setDis(c,lev,p,0);

    isCentroid[c] = true;
    cpar[c] = p;
    clevel[c] = lev;

    for(int x : ed[c]) {
        if(!isCentroid[x]) decompose(x,c,lev+1);
    }
}

int ans[MAX];

inline void update(int v) {
    int u = v;
    while(u!=-1) {
        ans[u] = min(ans[u], dis[clevel[u]][v]);
        u = cpar[u];
    }
}

inline int query(int v) {
    int ret = INF;
    int u = v;
    while(u != -1) {
        ret = min(ret, dis[clevel[u]][v]+ans[u]);
        u = cpar[u];
    }
    return ret;
}
int main() {
    decompose(1,-1,0);
    for(int i=1; i<=n; i++) ans[i] = INF;
    update(v);
    query(v));
    return 0;
}
