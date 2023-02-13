#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int X = 3001;
const int MOD = 1e9 + 7;

void test_case() {
  int n;
  cin >> n;

  vector<int> x_freq(X, 0), y_freq(X, 0);
  for (int i = 0; i < n; i++) {
    int a, b;
    cin >> a >> b;
    x_freq[a]++, y_freq[b]++;
  }

  int q;
  cin >> q;
  ll ans = 0;

  while (q--) {
    int x, y;
    cin >> x >> y;
    for (int px = 0; px < X; px++) {
      (ans += 1ll * x_freq[px] % MOD * (x - px) % MOD * (x - px) % MOD) %= MOD;
    }
    for (int py = 0; py <= X; py++) {
      (ans += 1ll * y_freq[py] % MOD * (y - py) % MOD * (y - py) % MOD) %= MOD;
    }
  }
  (ans += MOD) %= MOD;

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}