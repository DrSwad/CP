#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll solve(int n, const vector<ll> &a, const vector<ll> &b) {
  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  sort(
    order.begin(),
    order.end(),
    [&](int i, int j) {
    return make_pair(a[i], b[i]) < make_pair(a[j], b[j]);
  }
    );

  vector<ll> r(n, LLONG_MIN);
  ll mx_b = LLONG_MIN;
  for (int i = n - 1; i >= 0; i--) {
    if (mx_b >= a[order[i]]) {
      r[i] = mx_b;
    }
    mx_b = max(mx_b, b[order[i]]);
  }

  set<ll> st;
  for (int i = 0; i < n; i++) {
    auto it = st.lower_bound(a[order[i]]);
    if (it != st.end() and r[i] < a[order[i]]) {
      r[i] =  *it;
    }

    st.insert(b[order[i]]);
  }

  ll ret = LLONG_MAX;
  for (int i = 0; i < n; i++) {
    if (r[i] >= a[order[i]]) {
      ret = min(ret, r[i] - a[order[i]]);
    }
  }

  return ret;
}

void test_case() {
  int n;
  cin >> n;

  vector<ll> a(n), b(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i] >> b[i];
  }

  cout << min(solve(n, a, b), solve(n, b, a)) << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}