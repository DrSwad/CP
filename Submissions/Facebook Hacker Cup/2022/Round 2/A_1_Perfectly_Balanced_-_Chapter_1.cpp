#include <bits/stdc++.h>
using namespace std;

void test_case() {
  string s;
  cin >> s;
  int n = s.length();

  vector<vector<int>> pref(26, vector<int>(n + 1));
  for (int c = 0; c < 26; c++) {
    pref[c][0] = 0;
    for (int i = 1; i <= n; i++) {
      pref[c][i] = pref[c][i - 1] + (s[i - 1] == 'a' + c);
    }
  }

  int q;
  cin >> q;

  int ans = 0;
  while (q--) {
    int l, r;
    cin >> l >> r;
    l--, r--;

    if ((r - l + 1) % 2 == 0) continue;
    int m = (l + r) / 2;

    vector<int> left_freq(26), right_freq(26), middle_freq(26, 0);
    for (int c = 0; c < 26; c++) {
      left_freq[c] = pref[c][m] - pref[c][l];
      middle_freq[c] = s[m] == 'a' + c;
      right_freq[c] = pref[c][r + 1] - pref[c][m + 1];
    }

    bool possible = false;
    // left
    {
      bool flag = true;
      int cnt = 0;
      for (int c = 0; c < 26; c++) {
        if (left_freq[c] + middle_freq[c] < right_freq[c]) {
          flag = false;
          break;
        }
        else if (left_freq[c] + middle_freq[c] == right_freq[c]) continue;
        else if (left_freq[c] + middle_freq[c] == right_freq[c] + 1) cnt++;
        else {
          flag = false;
          break;
        }
      }
      if (flag and cnt == 1) possible = true;
    }

    // right
    {
      bool flag = true;
      int cnt = 0;
      for (int c = 0; c < 26; c++) {
        if (right_freq[c] + middle_freq[c] < left_freq[c]) {
          flag = false;
          break;
        }
        else if (right_freq[c] + middle_freq[c] == left_freq[c]) continue;
        else if (right_freq[c] + middle_freq[c] == left_freq[c] + 1) cnt++;
        else {
          flag = false;
          break;
        }
      }
      if (flag and cnt == 1) possible = true;
    }

    // middle
    {
      bool flag = true;
      for (int c = 0; c < 26; c++) {
        if (left_freq[c] != right_freq[c]) {
          flag = false;
          break;
        }
      }
      if (flag) possible = true;
    }

    ans += possible;
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}