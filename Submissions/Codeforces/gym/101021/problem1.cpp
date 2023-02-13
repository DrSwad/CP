#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  int L = 1, R = n + 1;
  while (R - L > 1) {
    int m = (R + L) / 2;
    cout << "? " << m << endl;

    string res;
    cin >> res;

    if (res == ">=") L = m;
    else R = m;
  }

  cout << "! " << L << endl;
}

int main() {
  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}