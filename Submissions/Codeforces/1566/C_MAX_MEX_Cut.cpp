#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    string s1, s2;
    cin >> s1 >> s2;

    bool zero = false, one = false;
    int ans = 0;

    for (int i = 0; i < n; i++) {
      if (s1[i] == '0' and s2[i] == '0') {
        if (one == true) ans += 2, zero = false, one = false;
        else if (zero == true) ans++, zero = true, one = false;
        else zero = true, one = false;
      }
      else if (s1[i] == '1' and s2[i] == '1') {
        if (zero == true) ans += 2, zero = false, one = false;
        else zero = false, one = true;
      }
      else {
        if (zero == true) ans += 3, zero = one = false;
        else ans += 2, zero = one = false;
      }
    }

    if (zero and one) ans += 2;
    else if (zero) ans++;

    cout << ans << "\n";
  }

  return 0;
}