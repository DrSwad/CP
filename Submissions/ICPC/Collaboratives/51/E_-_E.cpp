#include <bits/stdc++.h>
using namespace std;

const int MX = 100;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int x0, yl, yr;
  cin >> x0 >> yl >> yr;

  vector<int> ks;
  double x = x0;
  for (int k = 0; k <= MX; k++) {
    int y = x;
    if (x > y) y++;
    if (yl <= y and y <= yr) ks.push_back(k);
    x = 10 * sqrt(x);
  }

  if (ks.empty()) cout << "impossible\n";
  else if (yr == 100) cout << ks[0] << " inf\n";
  else cout << ks[0] << " " << ks.back() << "\n";

  return 0;
}