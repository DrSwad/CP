#include <bits/stdc++.h>
using namespace std;

void test_case() {
  string s;
  cin >> s;

  int n = s.length();
  vector<bool> can_be_thief(n, true);

  bool flag = true;
  for (int i = 0; i < n; i++) {
    can_be_thief[i] = can_be_thief[i] and flag;
    flag = flag and s[i] != '0';
  }

  flag = true;
  for (int i = n - 1; i >= 0; i--) {
    can_be_thief[i] = can_be_thief[i] and flag;
    flag = flag and s[i] != '1';
  }

  cout << accumulate(can_be_thief.begin(), can_be_thief.end(), 0) << "\n";
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