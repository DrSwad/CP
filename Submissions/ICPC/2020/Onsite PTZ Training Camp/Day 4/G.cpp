#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n), p(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    a[i]--;
    p[a[i]] = i;
  }

  int ans = 0;
  for (int at = n - 1; at >= 0; ) {
    ans++;
    if (at == 0) break;

    int nxt = at - 1;
    bool dir = p[at] > p[nxt];
    while (nxt >= 0 and (p[nxt + 1] > p[nxt]) == dir) nxt--;

    at = nxt;
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