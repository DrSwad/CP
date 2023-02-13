#include <bits/stdc++.h>
using namespace std;

int brute(string s) {
  s = s.substr(8);
  int n = s.length();
  int ret = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] != 'h') continue;
    int cnt = 0;
    for (int j = i + 1; j < n; j++) {
      cnt += s[i] == 'a';
    }
    ret += (1 << cnt) - 1;
  }
  return ret;
}

void test_case() {
  int n;
  cin >> n;

  cout << "nunhehhe";
  if (n == 0) {
    cout << "\n";
    return;
  }

  vector<int> cnth(31, 0);
  cnth[1] += __builtin_popcount(n);

  for (int i = 30; i >= 1; i--) {
    if (n >> i & 1) cnth[i]++;
  }

  int at = 30;
  while (!cnth[at]) at--;

  while (at >= 1) {
    while (cnth[at]--) cout << "h";
    cout << "a";
    at--;
  }
  cout << "\n";
}

int main() {
  // ios::sync_with_stdio(false);
  // cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}