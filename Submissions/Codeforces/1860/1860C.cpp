#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> p(n);
  for (int &i : p) cin >> i;

  int min_lose = INT_MAX;
  int mn = INT_MAX;
  int ans = 0;

  for (int i = 0; i < n; i++) {
    mn = min(mn, p[i]);
    if (p[i] > mn and p[i] < min_lose) {
      min_lose = p[i];
      ans++;
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