#include <bits/stdc++.h>
using namespace std;

void answer(string ans = "") {
  cout << (ans.empty() ? "IMPOSSIBLE" : ans) << "\n";
}

void test_case() {
  int n;
  cin >> n;

  vector<string> vs(n);
  for (string &s : vs) cin >> s;

  vector<int> middle_freq(26, 0);

  for (int i = 0; i < n; i++) {
    vector<int> left_freq(26, 0);
    vector<int> right_freq(26, 0);
    for (int j = 1; j < vs[i].length() - 1; j++) {
      if (vs[i][j] != vs[i][j - 1]) left_freq[vs[i][j] - 'A']++;
      if (vs[i][j] != vs[i][j + 1]) right_freq[vs[i][j] - 'A']++;
    }

    for (int c = 0; c < 26; c++) {
      if (left_freq[c] > 1 or right_freq[c] > 1) {
        return answer();
      }
      if (left_freq[c] == 1 and right_freq[c] == 1) {
        middle_freq[c]++;
      }
    }
  }

  for (int c = 0; c < 26; c++) {
    if (middle_freq[c] > 1) return answer();
  }

  vector<int> char_at_start_of(26, -1), char_at_end_of(26, -1);
  vector<vector<int>> char_at_all_of(26);

  for (int i = 0; i < n; i++) {
    const string&s = vs[i];

    if (count(s.begin(), s.end(), s[0]) == s.length()) {
      char_at_all_of[s[0] - 'A'].push_back(i);
    }
    else {
      if (char_at_start_of[s[0] - 'A'] != -1) return answer();
      char_at_start_of[s[0] - 'A'] = i;

      if (char_at_end_of[s.back() - 'A'] != -1) return answer();
      char_at_end_of[s.back() - 'A'] = i;
    }
  }

  for (int c = 0; c < 26; c++) {
    if (middle_freq[c] > 0) {
      if (char_at_start_of[c] != -1 or char_at_end_of[c] != -1 or !char_at_all_of[c].empty()) {
        return answer();
      }
    }
  }

  string ans;
  vector<bool> visited(26, false);

  for (int c = 0; c < 26; c++) {
    if (char_at_end_of[c] == -1) {
      int at_char = c;

      while (true) {
        if (visited[at_char]) return answer();
        visited[at_char] = true;

        for (int i : char_at_all_of[at_char]) ans += vs[i];
        if (char_at_start_of[at_char] != -1) {
          int nxt_i = char_at_start_of[at_char];
          ans += vs[nxt_i];
          at_char = vs[nxt_i].back() - 'A';
        }
        else break;
      }
    }
  }

  int tot_size = 0;
  for (const string &s : vs) tot_size += s.size();
  if (tot_size != ans.size()) return answer();
  else return answer(ans);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}