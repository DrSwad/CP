#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int l, r;
  cin >> l >> r;

  if (r <= 3) cout << "-1\n";
  else {
    l = max(l, 4);
    if (l % 2 == 1 and r > l) l++;

    int div = -1;
    for (int i = 2; i * i <= l; i++) {
      if (l % i == 0) {
        div = i;
        break;
      }
    }

    if (div == -1) cout << "-1\n";
    else cout << div << " " << l - div << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}