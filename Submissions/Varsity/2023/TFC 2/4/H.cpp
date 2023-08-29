#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i, i--;

  int mx = 0;
  for (int i = 0; i < n; i++) {
    if (a[i] == mx) mx++;
  }

  if (mx == 0) cout << "-1\n";
  else cout << n - mx << "\n";

  return 0;
}