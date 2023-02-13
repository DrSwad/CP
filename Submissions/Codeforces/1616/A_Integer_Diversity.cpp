#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  map<int, int> f;
  int ans = 0;
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;

    if (!f.count(a)) {
      f[a] = 1;
      ans++;
    }
    else if (!f.count(-a)) {
      f[-a] = 1;
      ans++;
    }
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