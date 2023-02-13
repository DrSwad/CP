#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n = 1e5;
  cout << n << "\n";

  for (int l = 1; l <= n - 1; l++) {
    if (l % 2 == 1) {
      cout << l << " " << 1 << " " << 1 << " " << l << "\n";
    }
    else {
      cout << l << " " << l << " " << l << " " << l << "\n";
    }
  }

  cout << 1 << "\n";
  cout << "1 1 " << n << " " << n << "\n";

  return 0;
}