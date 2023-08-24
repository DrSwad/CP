#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<long long> a(n);
  for (long long &i : a) cin >> i;

  if (a[0] > n) {
    cout << "NO\n";
    return;
  }

  vector<long long> b(n, 0);
  for (int i = 0; i < n; i++) {
    b[a[i] - 1]++;
  }

  for (int i = n - 2; i >= 0; i--) {
    b[i] += b[i + 1];
  }

  if (a == b) cout << "YES\n";
  else cout << "NO\n";
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