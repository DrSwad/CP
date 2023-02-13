#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;

  vector<int> a(n), b(n);
  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;

  int ans = 0;
  for (int i : a) {
    for (int j : b) {
      ans ^= i + j;
    }
  }

  cout << ans << "\n";

  return 0;
}