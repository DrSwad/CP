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

  int ans1 = 0, ans2 = streaks.size();
  int prev_vanished = -2;
  if (streaks[0] == 1) {
    int count2 = 0;
    for (int i = 1; streaks[i] == 2; i++) {
      count2++;
    }
    if (count2 % 2 == 1) prev_vanished = -1;
  }

  for (int i = 0, last = -1; i < streaks.size(); i++) {
    if (streaks[i] % 2 == 1) {
      if (last == -1) {
        last = i;
      }
    }

    if (last != -1) {
      if (streaks[i] <= 2 and prev_vanished != i - 1) {
        prev_vanished = i;
        ans2 -= (i == 0 ? 1 : 2);
      }
    }

    if (streaks[i] % 2 == 1) {
      if (last != -1 and last != i) {
        ans1 += i - last;
        last = -1;
      }
    }
  }

  cout << ans1 << " " << ans2 << "\n";
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