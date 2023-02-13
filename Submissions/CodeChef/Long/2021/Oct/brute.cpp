#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 5;

int n, q;
tuple<ll, ll, ll> v[N];
int ans;

void dfs(int at, ll k, ll took = 0) {
  if (at > n) {
    /* cerr << endl;
       for (int i = 1; i <= n; i++) {
       debug(i, v[i]);
       } */

    int rank = 1;
    for (int i = 2; i <= n; i++) {
      rank += v[i] > v[1];
    }
    ans = min(ans, rank);
    return;
  }

  ll *from1, *from2, *to;
  if (at == 1) {
    from1 = &get<2>(v[at]);
    from2 = &get<1>(v[at]);
    to = &get<0>(v[at]);
  }
  else {
    from1 = &get<0>(v[at]);
    from2 = &get<1>(v[at]);
    to = &get<2>(v[at]);
  }

  for (ll kk = k == 0 ? 0 : at > 2 ? took : 0; kk <= min(k, *from1 + *from2); kk++) {
    ll rem = kk;
    ll pfrom1 = *from1, pfrom2 = *from2, pto = *to;

    if (rem) {
      ll take = min(rem, *from1);
      rem -= take;
      *from1 -= take;
      *to += take;
    }
    if (rem) {
      ll take = min(rem, *from2);
      rem -= take;
      *from2 -= take;
      *to += take;
    }

    k -= kk;

    dfs(at + 1, k, kk);

    *from1 = pfrom1, *from2 = pfrom2, *to = pto;
    k += kk;
  }
}

void brute() {
  for (int i = 1; i <= n; i++) {
    auto & [g, s, b] = v[i];
    ll &from1 = s;
    ll &from2 = i == 1 ? b : g;
    ll &to = i == 1 ? g : b;
    to += from1 + from2;
    from1 = from2 = 0;
  }

  ans = n - (upper_bound(v + 2, v + n + 1, v[1]) - (v + 2));
}

void test_case() {
  cin >> n >> q;

  for (int i = 1; i <= n; i++) {
    auto & [g, s, b] = v[i];
    cin >> g >> s >> b;
  }

  sort(v + 2, v + n + 1);

  int mxk = 0;
  for (int i = 1; i <= n; i++) {
    auto [g, s, b] = v[i];
    mxk += s + (i == 1 ? b : g);
  }

  while (q--) {
    ll k;
    cin >> k;

    if (k >= mxk) {
      brute();
    }
    else {
      ans = n;
      dfs(1, k);
    }

    cout << ans << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    // cerr << cs << "\n";
    test_case();
  }

  return 0;
}