#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> l(n), r(n), a(n), b(n);
  for (int i = 0; i < n; i++) {
    cin >> l[i] >> r[i] >> a[i] >> b[i];
  }

  vector<int> l_order(n), b_order(n);
  iota(l_order.begin(), l_order.end(), 0);
  sort(
    l_order.begin(),
    l_order.end(),
    [&](int i, int j) { return l[i] < l[j]; }
  );
  iota(b_order.begin(), b_order.end(), 0);
  sort(
    b_order.begin(),
    b_order.end(),
    [&](int i, int j) { return b[i] < b[j]; }
  );

  vector<int> nxt_bi(n);
  for (int li = 0, bi = 0, mx_bi = -1; bi < n; bi++) {
    while (li < n and l[l_order[li]] <= b[b_order[bi]]) {
      if (mx_bi == -1 or b[l_order[li]] > b[mx_bi]) {
        mx_bi = l_order[li];
      }
      li++;
    }
    nxt_bi[b_order[bi]] = mx_bi;
  }

  vector<int> mx_b(n, 0);
  for (int bi = n - 1; bi >= 0; bi--) {
    int i = b_order[bi];
    mx_b[i] = max(b[i], mx_b[nxt_bi[i]]);
  }

  int q;
  cin >> q;

  vector<int> x(q);
  for (int &i : x) cin >> i;

  vector<int> q_order(q);
  iota(q_order.begin(), q_order.end(), 0);
  sort(
    q_order.begin(),
    q_order.end(),
    [&](int i, int j) {
      return x[i] < x[j];
    }
  );

  vector<int> ans(q, 0);
  for (int li = 0, qi = 0, mx = 0; qi < q; qi++) {
    while (li < n and l[l_order[li]] <= x[q_order[qi]]) {
      mx = max(mx, mx_b[l_order[li]]);
      li++;
    }
    ans[q_order[qi]] = max(x[q_order[qi]], mx);
  }

  for (int i = 0; i < q; i++) {
    if (i) cout << " ";
    cout << ans[i];
  }
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}