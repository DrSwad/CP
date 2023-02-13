#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  int k;
  cin >> k;

  vector<int> x(k);
  for (int &i : x) cin >> i;

  sort(x.begin(), x.end());

  int ans = 0, cat = 0;
  for (int i = k - 1; i >= 0 and cat < n; i--) {
    if (x[i] <= cat) break;
    ans++;
    cat += n - x[i];
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