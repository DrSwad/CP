#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int ans = 0;
  for (int i = 0; i < n; i++) {
    int sum = 0, mul = 1;
    for (int j = i; j < n; j++) {
      sum += a[j];
      mul *= a[j];
      ans += sum == mul;
    }
  }

  cout << ans << "\n";
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