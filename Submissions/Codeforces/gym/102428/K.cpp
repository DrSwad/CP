#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
const ull mx = LLONG_MAX;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  cin >> s;

  vector<int> changes;
  for (int i = 1; i < s.length(); i++) {
    if (s[i] != s[i - 1]) {
      changes.push_back(2 * (i + 1));
    }
  }

  vector<int> roots;
  for (int i = 0; i < changes.size(); i++) {
    roots.push_back(changes[i] - 1);
  }

  vector<ull> poly{1};
  for (int root : roots) {
    poly.push_back(0);
    for (int deg = (int)poly.size() - 1; deg >= 0; deg--) {
      poly[deg] = (deg > 0 ? poly[deg - 1] : 0) - root * poly[deg];
    }
  }

  cout << (int)poly.size() - 1 << "\n";
  for (int deg = (int)poly.size() - 1; deg >= 0; deg--) {
    long long val = poly[deg] <= mx ? poly[deg] : (poly[deg] - ULLONG_MAX - 1);
    if ((s[0] == 'A') != roots.size() % 2) val *= -1;
    cout << val;
    if (deg > 0) cout << " ";
  }

  cout << "\n";

  return 0;
}