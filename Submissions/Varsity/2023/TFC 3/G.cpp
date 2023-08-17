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

  for (int i = 0; i < n; i++) {
    int cur = a[i];
    auto it = upper_bound(a.begin(), a.end(), cur);
    if (it != a.end()) {
      int nxt = *it;
      if (cur > 1 and nxt < 2 * cur) {
        cout << "YES\n";
        return 0;
      }
    }
  }

  cout << "NO\n";

  return 0;
}