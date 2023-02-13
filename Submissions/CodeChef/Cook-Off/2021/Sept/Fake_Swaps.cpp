#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  string s, p;
  cin >> s >> p;

  vector<int> cnt(2, 0);
  for (char c : p) {
    cnt[c - '0']++;
  }

  cout << ((s == p) or (cnt[0] and cnt[1]) ? "YES" : "NO") << "\n";
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