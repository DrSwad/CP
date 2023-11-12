#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int mex = 0;
  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    if (a[i] > mex) cout << mex;
    else if (a[i] < mex) cout << a[i];
    else cout << mex, mex++;
  }
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}