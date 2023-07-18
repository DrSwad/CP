#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  if (k == 1) cout << "0\n";
  else {
    int mx = n - (k - 1);
    int mn = 1;
    cout << mx - mn << "\n";
  }

  return 0;
}