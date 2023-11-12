#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, from, to;
  cin >> n >> from >> to;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int ans = 0;
  for (int i = from; i <= to; i++) ans += a[i];

  cout << ans << "\n";

  return 0;
}