#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t;
  cin >> t;

  while (t--) {
    string s;
    cin >> s;

    bool zero = false;
    bool two_zero = false;
    int last_zero = -1;

    for (int i = 0; i < s.length(); i++) {
      if (s[i] == '0') {
        zero = true;
        if (~last_zero and last_zero != i - 1) two_zero = true;
        last_zero = i;
      }
    }

    if (!zero) cout << "0";
    else if (two_zero) cout << "2";
    else cout << "1";
    cout << "\n";
  }

  return 0;
}