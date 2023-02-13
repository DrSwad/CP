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

    string s;
    cin >> s;

    string ss(n, ' ');
    for (int i = 0; i < n; ) {
      if (s[i] == 'U' or s[i] == 'D') {
        ss[i] = 'D' ^ 'U' ^ s[i];
        i++;
      } else {
        ss[i] = 'L';
        ss[i + 1] = 'R';
        i += 2;
      }
    }

    cout << ss << "\n";
  }

  return 0;
}