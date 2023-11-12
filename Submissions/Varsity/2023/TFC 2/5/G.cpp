#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int ans = 0;
  for (int l = 0; l < n; ) {
    int r = l;
    while (r < n and a[r] == a[l]) r++;
    int cnt = r - l;
    ans += cnt / 2;
    l = r;
  }

  cout << ans << "\n";

  return 0;
}