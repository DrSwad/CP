#include <bits/stdc++.h>
using namespace std;

void test_case() {
    string s;
    cin >> s;

    vector<int> freq(26, 0);
    for (char c : s) freq[c - 'a']++;

    string ans;
    for (int c = 0; c < 26; c++) {
        while (freq[c]--) {
            ans += 'a' + c;
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