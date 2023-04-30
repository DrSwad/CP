#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int W;
  cin >> W;

  int todo = 1;
  int totW = 0;
  while (todo--) {
    int more, w;
    cin >> w >> more;
    totW += w;
    todo += more;
  }

  cout << (totW + W - 1) / W << "\n";

  return 0;
}
