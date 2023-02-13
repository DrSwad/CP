#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string a, b, c;
  cin >> a >> b >> c;

  string ans;
  ans += a[0] + 'A' - 'a';
  ans += b[0] + 'A' - 'a';
  ans += c[0] + 'A' - 'a';
  cout << ans << "\n";

  return 0;
}