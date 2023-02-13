#include <bits/stdc++.h>
using namespace std;

const int A = 3e5 + 5;

int xor_pref[A];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  for (int i = 1; i < A; i++) {
    xor_pref[i] = xor_pref[i - 1] ^ i;
  }

  int t;
  cin >> t;

  while (t--) {
    int a, b;
    cin >> a >> b;

    int x = xor_pref[a - 1];
    int need = x ^ b;
    int ans = a + (need == 0 ? 0 : need == a ? 2 : 1);

    cout << ans << "\n";
  }

  return 0;
}