#include <bits/stdc++.h>
using namespace std;

void test_case() {
  const int tot = 365;
  vector<int> freq(tot);

  int n;
  cin >> n;

  while (n--) {
    int l, r;
    cin >> l >> r;
    for (int i = l - 1; i < r; i++) {
      freq[i]++;
    }
  }

  int ans = 0;
  for (int i = 0; i < tot; i++) {
    ans += freq[i] > 0;
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}