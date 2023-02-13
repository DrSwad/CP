#include <bits/stdc++.h>
using namespace std;

void test_case() {
  string n;
  cin >> n;

  int d = n.size();
  int ans = d;

  vector<int> p(d + 1, 0);
  for (int i = 1; i <= d; i++) {
    p[i] = p[i - 1] + (n[i - 1] != 0);
  }

  for (int i = 0; i < d; i++) {
    for (int j = i + 1; j < d; j++) {
      int m = (n[i] - '0') * 10 + (n[j] - '0');
      if (m % 25 != 0) continue;
      if (m == 0 and p[i] == 0) continue;
      ans = min(ans, (p[j] - p[i + 1]) + (p[d] - p[j + 1]));
    }
  }

  cout << ans << "\n";
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