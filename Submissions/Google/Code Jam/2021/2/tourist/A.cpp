/**
 *    author:  tourist
 *    created: 15.05.2021 17:06:50       
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt, n;
  cin >> tt >> n;
  for (int qq = 1; qq <= tt; qq++) {
    for (int i = 1; i < n; i++) {
      cout << "M " << i << " " << n << endl;
      int x;
      cin >> x;
      if (x != i) {
        cout << "S " << i << " " << x << endl;
        cin >> x;
      }
    }
    cout << "D" << endl;
    int x;
    cin >> x;
    if (x == -1) {
      break;
    }
  }
  return 0;
}
