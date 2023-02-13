#include <bits/stdc++.h>
using namespace std;

int main() {
  int a, b, n;
  cin >> a >> b >> n;

  int rem = a % b;
  string digits = to_string(a);

  bool possible = true;
  while (n--) {
    int take = -1;
    for (int d = 0; d < 10; d++) {
      if ((rem * 10 + d) % b == 0) {
        take = d;
        break;
      }
    }

    if (take == -1) {
      possible = false;
      break;
    } else {
      digits.push_back(take + '0');
      rem = (rem * 10 + take) % b;
    }
  }

  if (!possible) puts("-1");
  else cout << digits << endl;

  return 0;
}