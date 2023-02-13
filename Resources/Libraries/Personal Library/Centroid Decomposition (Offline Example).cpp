/***
    https://codeforces.com/contest/1156/problem/D

    You are given a tree consisting of n vertices and n−1 edges.
    A number is written on each edge, each number is either 0 or 1.
    Let's call an ordered pair of vertices (x,y) (x≠y) valid if,
    while traversing the simple path from x to y,
    we never go through a 0-edge after going through a 1-edge.
    Your task is to calculate the number of valid pairs in the tree.
***/

const int MAX = 200010;

vector <pii> ed[MAX];
bool isC[MAX];
int sub[MAX];

void calc(int s,int p) {
    sub[s] = 1;
    for(pii x : ed[s]) {
        if(x.xx == p or isC[x.xx]) continue;
        calc(x.xx,s);
        sub[s] += sub[x.xx];
    }
}

int nn;

int getC(int s,int p) {
    for(pii x : ed[s]) {
        if(!isC[x.xx] and x.xx!=p and sub[x.xx]>(nn/2)) return getC(x.xx,s);
    }
    return s;
}


ll cnt0, cnt1, cnt01;
ll ans = 0;

void process(int s,int p,int zp,int op,int fg) {
    if(fg) ans++;
    if(zp and op) ans += cnt1;
    else if(zp) ans += cnt01 + cnt1 + cnt0;
    else if(op) ans += cnt1;
    else assert(false);

    for(pii x : ed[s]) {
        if(x.xx == p or isC[x.xx]) continue;
        if(zp and x.yy==1) continue;
        process(x.xx,s,zp or (x.yy==0),op or (x.yy==1),fg);
    }
}

void add(int s,int p,int zp,int op,int fg) {

    if(fg) ans++;

    if(zp and op) cnt01++;
    else if(zp) cnt0++;
    else if(op) cnt1++;
    else assert(false);

    for(pii x : ed[s]) {
        if(x.xx == p or isC[x.xx]) continue;
        if(op and x.yy==0) continue;
        add(x.xx,s,zp or (x.yy==0),op or (x.yy==1),fg);
    }
}

void decompose(int s,int p,int lev) {
    calc(s,p);
    nn = sub[s];
    int c = getC(s,p);

    cnt1 = cnt01 = cnt0 = 0;
    for(pii x : ed[c]) {
        if(isC[x.xx]) continue;
        process(x.xx,c,x.yy==0,x.yy==1,1);
        add(x.xx,c,x.yy==0,x.yy==1,1);
    }

    cnt1 = cnt01 = cnt0 = 0;
    reverse(all(ed[c]));
    for(pii x : ed[c]) {
        if(isC[x.xx]) continue;
        process(x.xx,c,x.yy==0,x.yy==1,0);
        add(x.xx,c,x.yy==0,x.yy==1,0);
    }
    isC[c] = true;
    for(pii x : ed[c]) {
        if(!isC[x.xx]) decompose(x.xx,c,lev+1);
    }
}

int main() {
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);

    int n,a,b,c;
    si(n);
    for(int i=1;i<n;i++) {
        siii(a,b,c);
        ed[a].pb({b,c});
        ed[b].pb({a,c});
    }
    decompose(1,-1,0);
    cout << ans << endl;
    return 0;
}
