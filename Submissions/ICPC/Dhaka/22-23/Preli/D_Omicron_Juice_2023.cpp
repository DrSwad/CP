#include <bits/stdc++.h>
using namespace std;

void yes() {
  cout << "Peaceful\n";
}

void no() {
  cout << "Fight\n";
}

void test_case() {
  int a, b, c, k;
  cin >> a >> b >> c >> k;

  {
    int cnt = (a >= k) + (b >= k) + (c >= k);
    if (cnt < 2) {
      if (a == b and b == c) return yes();
      else return no();
    }
  }

  if ((a + b + c) % 3 == 0 and a % k == b % k and b % k == c % k and c % k == ((a + b + c) / 3) % k) {
    return yes();
  }
  else {
    return no();
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}