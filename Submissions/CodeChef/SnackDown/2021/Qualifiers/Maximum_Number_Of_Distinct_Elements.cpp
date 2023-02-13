#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> b(n);
  for (int &i : b) cin >> i;

  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int i, int j) {
    return b[i] < b[j];
  });

  vector<int> a(n);
  int mxr = -1;

  for (int i : order) {
    int r = min(mxr + 1, b[i] - 1);
    a[i] = r;
    mxr = r;
  }

  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << a[i];
  }
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}