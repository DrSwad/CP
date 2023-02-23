#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

int n;
int a[N];
bool vis[N];

void test_case() {
  cin >> n;

  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    vis[a[i]] = true;
  }

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int d = 1; ; d++) {
      long long b = 2ll * a[i] * d + 1ll * d * d;
      if (b >= N) break;
      ans += vis[b];
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}