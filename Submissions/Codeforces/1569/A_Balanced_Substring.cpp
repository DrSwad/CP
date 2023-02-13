#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  string s;
  cin >> s;

  for (int i = 0; i < (int)s.length() - 1; i++) {
    if (s[i] != s[i + 1]) {
      cout << i + 1 << " " << i + 2 << "\n";
      return;
    }
  }

  cout << "-1 -1\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t;
  cin >> t;

  while (t--) {
    test_case();
  }

  return 0;
}