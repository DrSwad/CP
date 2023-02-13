#include <bits/stdc++.h>
using namespace std;

void test_case() {
  string s;
  cin >> s;
  for (char &c : s) c = 'a' + (c - 'a' + 13) % 26;
  cout << s << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}