#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int m;
  cin >> m;

  vector<int> b(m);
  for (int &i : b) cin >> i;

  int at = 0;
  for (int i = m - 1; i >= 0; i--) {
    int c = n - b[i];
    int prv = at < c ? (b[i] + at) : (at - c);
    at = prv;
  }

  cout << a[at] << "\n";
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