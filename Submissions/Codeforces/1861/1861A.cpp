#include <bits/stdc++.h>
using namespace std;

void test_case() {
  string s;
  cin >> s;

  int pos3 = find(s.begin(), s.end(), '3') - s.begin();
  int pos7 = find(s.begin(), s.end(), '7') - s.begin();
  if (pos3 >= pos7) cout << "73\n";
  else cout << "37\n";
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