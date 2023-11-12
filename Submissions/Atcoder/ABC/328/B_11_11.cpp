#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    string si = to_string(i);
    int d;
    cin >> d;
    for (int j = 1; j <= d; j++) {
      string sj = to_string(j);
      if (si[0] == sj[0] and
          count(si.begin(), si.end(), si[0]) == si.length() and
          count(sj.begin(), sj.end(), sj[0]) == sj.length()
      ) {
        ans++;
      }
    }
  }

  cout << ans << "\n";

  return 0;
}