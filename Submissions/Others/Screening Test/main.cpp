#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int p;
  cin >> p;

  vector<int> ans(p, -1);
  for (int sq_root = 0; sq_root < p; sq_root++) {
    int sq = 1ll * sq_root * sq_root % p;
    ans[sq] = sq_root;
  }

  for (int i = 0; i < p; i++) {
    if (i) cout << " ";
    cout << ans[i];
  }
  cout << "\n";

  return 0;
}