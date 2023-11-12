#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, p;
  cin >> n >> m >> p;

  if (n < m) cout << "0\n";
  else cout << (n - m) / p + 1 << "\n";

  return 0;
}