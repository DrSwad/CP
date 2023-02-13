#include <bits/stdc++.h>
using namespace std;

const int N = 2500;
const int W = 80;
const int MAX_TOTAL_LENGTH = N * W + N + 2;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<string> words(n);
  for (string &word : words) cin >> word;

  int max_word_length = 0;
  for (string &word : words) {
    max_word_length = max(max_word_length, (int)word.length());
  }

  int ans_line_length = 0, ans_canal_length = -1;
  vector<int> prev_line_spaces, current_line_spaces;
  vector<int> prev_line_space_dp(MAX_TOTAL_LENGTH, 0), current_line_space_dp(MAX_TOTAL_LENGTH, 0);

  for (int line_length = max_word_length; line_length <= MAX_TOTAL_LENGTH; line_length++) {
    for (int at_word = 0, current_line_length = 0; at_word < n; at_word++) {
      int new_line_length = current_line_length + (current_line_length > 0) + words[at_word].length();

      if (current_line_length > 0 and new_line_length <= line_length) {
        current_line_spaces.push_back(current_line_length);
        int current_dp = 1;
        current_dp = max(current_dp, 1 + prev_line_space_dp[current_line_length - 1]);
        current_dp = max(current_dp, 1 + prev_line_space_dp[current_line_length]);
        current_dp = max(current_dp, 1 + prev_line_space_dp[current_line_length + 1]);
        current_line_space_dp[current_line_length] = current_dp;
        if (current_dp > ans_canal_length) {
          ans_canal_length = current_dp;
          ans_line_length = line_length;
        }
      }

      if (new_line_length >= line_length) {
        for (int i : prev_line_spaces) {
          prev_line_space_dp[i] = 0;
        }
        prev_line_spaces.clear();
        swap(prev_line_space_dp, current_line_space_dp);
        swap(prev_line_spaces, current_line_spaces);
        current_line_length = 0;
      }

      if (new_line_length > line_length) {
        at_word--;
      }

      if (new_line_length < line_length) {
        current_line_length = new_line_length;
      }
    }

    for (int i : prev_line_spaces) {
      prev_line_space_dp[i] = 0;
    }
    prev_line_spaces.clear();
    for (int i : current_line_spaces) {
      current_line_space_dp[i] = 0;
    }
    current_line_spaces.clear();
  }

  cout << ans_line_length << " " << ans_canal_length << "\n";

  return 0;
}