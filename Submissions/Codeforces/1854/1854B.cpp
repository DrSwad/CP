#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 1;

int n;
int a[N];
long long pref[N];
bitset<N> bs;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n; i++) {
    pref[i] = pref[i - 1] + a[i];
  }

  long long ans = 0;

  bs[1] = 1;
  for (int i = 1; i < N; i++) {
    if (bs[i]) {
      ans = max(ans, pref[min(i, n)] - (i - 1));
    }
    if (i <= n) {
      if (bs.any()) {
        bs |= bs << a[i];
        bs[i] = 0;
      }
      else break;
    }
  }

  cout << ans << "\n";

  return 0;
}