#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

void test_case() {
  int n;
  cin >> n;

  vector<int> pos(n);
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    pos[a] = i;
  }

  int ans = 1;
  int l = pos[0], r = pos[0];
  for (int i = 1; i < n; i++) {
    if (pos[i] < l) l = pos[i];
    else if (pos[i] > r) r = pos[i];
    else (ans = 1ll * ans * (r - l + 1 - i) % MOD);
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