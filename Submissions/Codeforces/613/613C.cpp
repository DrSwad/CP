#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int g = a[0];
  for (int i = 1; i < n; i++) {
    g = gcd(g, a[i]);
  }

  vector<int> factors{g};
  if (g % 2 == 0) factors.push_back(g / 2);

  for (int factor : factors) {
    vector<int> b(n);
    int odd = -1;
    bool okay = true;
    for (int i = 0; i < n and okay; i++) {
      b[i] = a[i] / factor;
      if (b[i] % 2 == 1) {
        if (odd != -1) okay = false;
        odd = i;
      }
    }
    if (!okay) continue;

    string pattern;
    for (int i = 0; i < n; i++) {
      pattern += string(b[i] / 2, 'a' + i);
    }
    if (odd != -1) pattern += 'a' + odd;
    for (int i = n - 1; i >= 0; i--) {
      pattern += string(b[i] / 2, 'a' + i);
    }

    string ans;
    for (int i = 0; i < factor; i++) {
      ans += pattern;
    }

    cout << g << "\n";
    cout << ans << "\n";
    return 0;
  }

  cout << "0\n";
  for (int i = 0; i < n; i++) {
    cout << string(a[i], 'a' + i);
  }
  cout << "\n";

  return 0;
}