#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int need = 1;
  for (int i = 0; i < n; i++) {
    if (a[i] == need) need++;
  }
  int found = need - 1;

  cout << ((n - found) + (k - 1)) / k << "\n";
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