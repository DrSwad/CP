#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;
  sort(a.begin(), a.end());

  double mn = 1;
  for (int i = 0; i < n; i++) {
    if (a[i] > i + 1) {
      cout << "-1\n";
      return 0;
    }
    mn = min(mn, (double)a[i] / (i + 1));
  }

  cout << fixed << setprecision(10) << mn << "\n";

  return 0;
}