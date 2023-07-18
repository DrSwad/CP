#include <bits/stdc++.h>
using namespace std;

void no() {
  cout << "No\n";
  exit(EXIT_SUCCESS);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n = 8;
  vector<int> a(n);
  for (int &i : a) cin >> i;
  for (int i = 0, prv = 0; i < n; prv = a[i], i++) {
    if (a[i] < prv) no();
    if (a[i] < 100 or 675 < a[i]) no();
    if (a[i] % 25 != 0) no();
  }

  cout << "Yes\n";

  return 0;
}