#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int sum = 0;
  for (int i = 0; i < n - 1; i++) {
    sum += a[i];
    if (sum <= 0) {
      cout << "NO\n";
      return 0;
    }
  }
  cout << "YES\n";

  return 0;
}