#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> s(n), f(n);
  for (int &i: s) cin >> i;
  for (int &i: f) cin >> i;

  for (int i = 0; i < n; i++) {
    if (i > 0) cout << " ";
    int st = i == 0 ? s[i] : max(s[i], f[i - 1]);
    cout << f[i] - st;
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