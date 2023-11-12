#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m;
  cin >> n >> m;

  string s, t;
  cin >> s >> t;

  bool good_s = true, good_t = true;
  for (int i = 0; i < n - 1; i++) {
    if (s[i] == s[i + 1]) {
      good_s = false;
    }
  }
  for (int i = 0; i < m - 1; i++) {
    if (t[i] == t[i + 1]) {
      good_t = false;
    }
  }

  if (good_s) cout << "Yes\n";
  else if (!good_t) cout << "No\n";
  else if (t[0] != t[m - 1]) cout << "No\n";
  else {
    for (int i = 0; i < n - 1; i++) {
      if (s[i] == s[i + 1]) {
        if (s[i] == t[0]) {
          cout << "No\n";
          return;
        }
      }
    }
    cout << "Yes\n";
  }
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