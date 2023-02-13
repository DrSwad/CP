//Li Chao Tree for minimum case

struct Line {
  ll m, c;
  Line(ll m = 0, ll c = 0) : m(m), c(c) {};
  inline ll f(ll x) { return m * x + c; }
};
 
Line tree[4 * N];
 
void insert(int rt, int l, int r, Line v){
  if(l == r){
    if(tree[rt].f(l) > v.f(l)) tree[rt] = v; //change to < for max
    return;
  }
  int m = l + r >> 1, lc = rt << 1, rc = lc | 1;
  bool lft = v.f(l) < tree[rt].f(l); //change to > for max
  bool mid = v.f(m) < tree[rt].f(m); //change to > for max
 
  if(mid) swap(tree[rt], v);
  if(lft != mid) insert(lc, l, m, v);
  else insert(rc, m + 1, r, v);
}
 
ll query(int rt, int l, int r, int x){
  if(l == r) return tree[rt].f(x);
  int m = l + r >> 1, lc = rt << 1, rc = lc | 1;
  //replace min with max for max query
  if(x <= m) return min(tree[rt].f(x), query(lc, l, m, x)); 
  else return min(tree[rt].f(x), query(rc, m + 1, r, x));
}