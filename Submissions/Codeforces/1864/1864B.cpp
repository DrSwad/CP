#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k;
  cin >> n >> k;

  string s;
  cin >> s;

  if (k % 2 == 1) {
    string ss[2];
    for (int i = 0; i < n; i++) {
      ss[i & 1] += s[i];
    }
    sort(ss[0].begin(), ss[0].end(), greater<char>());
    sort(ss[1].begin(), ss[1].end(), greater<char>());
    s.erase();
    while (!ss[0].empty() or !ss[1].empty()) {
      if (!ss[0].empty()) s += ss[0].back(), ss[0].pop_back();
      if (!ss[1].empty()) s += ss[1].back(), ss[1].pop_back();
    }
    cout << s << "\n";
  }
  else {
    sort(s.begin(), s.end());
    cout << s << "\n";
  }
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