#include <bits/stdc++.h>
using namespace std;

void __print(int x) {cerr << x;}
void __print(bool x) {cerr << (int)x;}
void __print(long long x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template<typename T, typename ... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v ...);}
#ifndef ONLINE_JUDGE
#define debug(x ...) cerr << "[" <<#x << "] = ["; _print(x)
#else
#define debug(x ...)
#endif

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const int M = 2e5 + 3;

void solve() {

  int n;
  cin >> n;

  ll a[n + 1];
  vector<ll> pre(n + 1, 0);

  vector<int> v;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    if (a[i] != 1) v.push_back(i);
    pre[i] = a[i] + pre[i - 1];
  }

  if (v.empty()) {
    cout << "1 1\n";
    return;
  }

  if (v.size() > 20) {
    cout << v[0] << " " << v.back() << "\n";
    return;
  }

  ll mx = 0;
  int l, r;

  for (int i = 0; i < v.size(); i++) {
    for (int j = i; j < v.size(); j++) {
      ll prod = 1;
      int L = v[i], R = v[j];
      for (int k = L; k <= R; k++) {
        prod *= a[k];
      }
      ll cur = prod + pre[L - 1] + pre[n] - pre[R];
      if (cur > mx) {
        l = L, r = R;
        mx = cur;
      }
    }
  }
  cout << l << " " << r << "\n";
}

int main() {

  ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

  int t;
  cin >> t;

  while (t--) {
    solve();
  }

}
