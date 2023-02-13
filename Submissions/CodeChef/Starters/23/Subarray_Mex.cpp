#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k, x;
  cin >> n >> k >> x;

  if (x > k) {
    cout << "-1\n";
    return;
  }

  vector<int> a(n);
  for (int i = 0; i < x; i++) {
    a[i] = i;
  }
  for (int i = x; i < k; i++) {
    a[i] = 0;
  }
  for (int i = k; i < n; i++) {
    a[i] = a[i - k];
  }

  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << a[i];
  }
  cout << "\n";
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