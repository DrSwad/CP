#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int ans = 0;
  for (int i = n - 2; i >= 0; i--) {
    while (a[i] > 0 and a[i] >= a[i + 1]) {
      ans++;
      a[i] /= 2;
    }
    if (a[i] >= a[i + 1]) {
      ans = -1;
      break;
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