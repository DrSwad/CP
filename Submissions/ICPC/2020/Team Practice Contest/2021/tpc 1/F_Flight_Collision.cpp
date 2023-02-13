#include <bits/stdc++.h>
using namespace std;

const long double INF = 5e18;
const long double eps = 1e-6;

struct Drone {
  int x, v;
  Drone() {}
};

int main() {
  int n;
  scanf("%d", &n);

  vector<Drone> drone(n);
  for (int i = 0; i < n; i++) {
    scanf("%d %d", &drone[i].x, &drone[i].v);
  }

  vector<int> nxt(n), prv(n);
  iota(nxt.begin(), nxt.end(), 1);
  iota(prv.begin(), prv.end(), -1);

  auto does_collide = [&](int i, int j) {
    if (i > j) swap(i, j);
    if (j == n) return false;
    return drone[j].v < drone[i].v;
  };

  auto cmp = [&](int a, int b) {
    if (!does_collide(a, nxt[a])) return false;
    if (!does_collide(b, nxt[b])) return true;
    int i1 = a, i2 = nxt[a];
    int j1 = b, j2 = nxt[b];
    // bool flag = (drone[i1].v < drone[i2].v) ^ (drone[j1].v < drone[j2].v);
    long long lhs = 1ll * (drone[i2].x - drone[i1].x) * (drone[j1].v - drone[j2].v);
    long long rhs = 1ll * (drone[j2].x - drone[j1].x) * (drone[i1].v - drone[i2].v);
    // if (!flag) return lhs < rhs;
    // else return rhs < lhs;
    return make_pair(lhs, a) < make_pair(rhs, b);
  };
  set<int, decltype(cmp)> st(cmp);
  for (int i = 0; i < n; i++) {
    st.insert(i);
  }

  while (!st.empty()) {
    int i1 = *st.begin();
    int i2 = nxt[i1];
    if (!does_collide(i1, i2)) break;
    st.erase(st.begin());
    st.erase(i2);

    int P = prv[i1], N = nxt[i2];
    if (~P) {
      st.erase(P);
      nxt[P] = N;
      st.insert(P);
    }
    if (N < n) prv[N] = P;
  }

  vector<int> ans;
  for (int at = st.empty() ? n : *st.begin(); at < n; at = nxt[at]) {
    ans.push_back(at + 1);
  }

  printf("%d\n", ans.size());
  for (int i = 0; i < ans.size(); i++) {
    if (i) printf(" ");
    printf("%d", ans[i]);
  }
  puts("");

  return 0;
}