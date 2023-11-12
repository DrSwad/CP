#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> ip(n);
  for (int i = 0; i < n; i++) {
    int p;
    cin >> p;
    ip[p - 1] = i;
  }

  int ans = 0;
  for (int i = 0; i < n - 1; i++) {
    ans += ip[i] > ip[i + 1];
  }

  cout << ans << "\n";
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