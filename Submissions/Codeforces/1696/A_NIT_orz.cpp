#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, z;
  cin >> n >> z;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int ans = *max_element(a.begin(), a.end());
  for (int i : a) {
    ans = max(ans, i | z);
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