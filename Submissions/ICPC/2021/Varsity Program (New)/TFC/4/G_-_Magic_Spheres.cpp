#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int a, b, c;
  cin >> a >> b >> c;
  int x, y, z;
  cin >> x >> y >> z;

  int extra = max(0, a - x) / 2 * 2 + max(0, b - y) / 2 * 2 + max(0, c - z) / 2 * 2;
  int need = max(0, x - a) + max(0, y - b) + max(0, z - c);

  if (need * 2 <= extra) cout << "Yes\n";
  else cout << "No\n";

  return 0;
}