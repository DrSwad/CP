#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  int mx = (n - 1) * (n - 2) / 2;
  if (k > mx) cout << "-1\n";
  else {
    cout << (n * (n - 1) / 2 - k) << "\n";
    for (int i = 1; i <= n; i++) {
      for (int j = i + 1; j <= n; j++) {
        if (i == 1 or k == 0) {
          cout << i << " " << j << "\n";
        }
        else k--;
      }
    }
  }

  return 0;
}