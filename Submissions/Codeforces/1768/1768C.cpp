#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  sort(
    order.begin(),
    order.end(),
    [&](int i, int j) {
    return a[i] < a[j];
  }
    );

  set<int> st[2];
  for (int i = 1; i <= n; i++) {
    st[0].insert(i);
    st[1].insert(i);
  }

  vector<int> p[2];
  for (int i = 0, it = 0; i < n; i++, it ^= 1) {
    int v = a[order[i]];
    if (!st[it].count(v)) {
      cout << "NO\n";
      return;
    }
    st[it].erase(v);
    p[it].push_back(v);

    if (*st[it ^ 1].begin() > v) {
      cout << "NO\n";
      return;
    }
    p[it ^ 1].push_back(*st[it ^ 1].begin());
    st[it ^ 1].erase(st[it ^ 1].begin());
  }

  vector<int> q[2];
  for (int it = 0; it < 2; it++) {
    q[it].resize(n);
    for (int i = 0; i < n; i++) {
      q[it][order[i]] = p[it][i];
    }
  }

  cout << "YES\n";
  for (int it = 0; it < 2; it++) {
    for (int i = 0; i < n; i++) {
      if (i) cout << " ";
      cout << q[it][i];
    }
    cout << "\n";
  }
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