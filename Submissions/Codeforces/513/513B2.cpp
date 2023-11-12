#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  long long m;
  cin >> n >> m;

  vector<int> p(n);
  int l = 0, r = n - 1;

  for (int i = 1; i <= n; i++) {
    if (i == n) p[l] = i;
    else if (m <= (1ll << (n - i - 1))) p[l++] = i;
    else p[r--] = i, m -= 1ll << (n - i - 1);
  }

  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << p[i];
  }
  cout << "\n";

  return 0;
}