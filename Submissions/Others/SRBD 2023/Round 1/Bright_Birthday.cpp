#include <bits/stdc++.h>
using namespace std;

vector<string> colors{"blue", "green", "yellow", "red", "purple", "orange", "pink", "grey", "cyan", "brown", "ash", "silver", "gold", "white", "black"};
const int C = 26;

void test_case() {
  string s;
  cin >> s;

  vector<int> freq(C, 0);
  for (char c : s) freq[c - 'a']++;

  int sz = colors.size();
  int ans = 0;

  for (int mask = 0; mask < 1 << sz; mask++) {
    vector<int> need(C, 0);
    for (int i = 0; i < sz; i++) {
      if (mask >> i & 1) {
        for (char c : colors[i]) {
          need[c - 'a']++;
        }
      }
    }

    bool okay = true;
    for (int c = 0; c < C and okay; c++) {
      okay = okay and need[c] <= freq[c];
    }

    if (okay) ans = max(ans, (int)__builtin_popcount(mask));
  }

  cout << ans << "\n";
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