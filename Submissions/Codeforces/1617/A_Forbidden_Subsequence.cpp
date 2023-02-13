#include <bits/stdc++.h>
using namespace std;

void test_case() {
  string s;
  cin >> s;

  string t;
  cin >> t;

  if (count(begin(s), end(s), 'a') != 0 and
      count(begin(s), end(s), 'b') != 0 and
      count(begin(s), end(s), 'c') != 0 and
      t == "abc"
      ) {
    for (auto &c : s) {
      if (c == 'b') c = 'c';
      else if (c == 'c') c = 'b';
    }
    sort(begin(s), end(s));
    for (auto &c : s) {
      if (c == 'b') c = 'c';
      else if (c == 'c') c = 'b';
    }
  }
  else sort(begin(s), end(s));

  cout << s << "\n";
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