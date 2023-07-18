#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  if (n % 2 == 0) cout << "-1\n";
  else {
    for (int it = 0; it < 2; it++) {
      for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << i;
      }
      cout << "\n";
    }
    for (int i = 0; i < n; i++) {
      if (i) cout << " ";
      cout << 2 * i % n;
    }
    cout << "\n";
  }

  return 0;
}