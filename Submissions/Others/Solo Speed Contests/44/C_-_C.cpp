#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll h, w;
  cin >> h >> w;

  if (h == 1 or w == 1) cout << "1\n";
  else cout << (((h + 1) / 2) * ((w + 1) / 2)) + ((h / 2) * (w / 2)) << "\n";

  return 0;
}