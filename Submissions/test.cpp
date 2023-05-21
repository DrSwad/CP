#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  auto ans = lower_bound(a.begin(), a.end(), 1);
  if (ans == a.end()) cout << "-1\n";
  else cout << ans - a.begin() << "\n";

  return 0;
}
