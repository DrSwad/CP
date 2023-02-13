#include <bits/stdc++.h>
using namespace std;

void test_case() {
  string s;
  cin >> s;

  vector<int> cnt(3);
  for (int i = 0; i < 3; i++) {
    cnt[i] = count(s.begin(), s.end(), 'A' + i);
  }

  cout << (cnt[1] == cnt[0] + cnt[2] ? "YES" : "NO") << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}