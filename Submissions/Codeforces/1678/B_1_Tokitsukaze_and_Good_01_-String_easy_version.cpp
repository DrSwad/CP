#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  string s;
  cin >> s;

  vector<int> streaks;
  for (int i = 0; i < n; i++) {
    if (i == 0 or s[i] != s[i - 1]) {
      streaks.push_back(1);
    }
    else {
      streaks.back()++;
    }
  }

  int ans = 0;
  for (int i = 0, last = -1; i < streaks.size(); i++) {
    if (streaks[i] % 2 == 1) {
      if (last != -1) {
        ans += i - last;
        last = -1;
      }
      else {
        last = i;
      }
    }
  }

  cout << ans << "\n";
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