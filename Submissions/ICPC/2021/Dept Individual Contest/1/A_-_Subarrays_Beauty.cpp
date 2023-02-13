#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  long long ans = 0;

  for (int b = 0; b < 25; b++) {
    for (int l = 0; l < n; ) {
      if (!(a[l] >> b & 1)) l++;
      else {
        int r = l;
        while (r < n and (a[r] >> b & 1)) r++;

        int len = r - l;
        ans += (long long)len * (len + 1) / 2 * (1 << b);

        l = r;
      }
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