#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
string s, ans_s;
int k;
vector<int> q_pos;
vector<vector<int>> possibilities;
vector<int> dp;

void construct_ans(int pos, int last) {
  if (pos == q_pos.size()) {
    k--;
    return;
  }

  vector<int> cur_possibility = possibilities[pos];

  if (possibilities[pos].empty()) {
    assert(q_pos[pos] > 0 and s[q_pos[pos] - 1] == '?');
    for (int i = last == 2 ? 6 : 9; i >= 1; i--) {
      cur_possibility.push_back(i);
    }
  }

  for (int i : cur_possibility) {
    ans_s[q_pos[pos]] = i + '0';
    construct_ans(pos + 1, i);
    if (k == 0) return;
  }
}

void test_case() {
  cin >> s >> k;

  q_pos.clear();
  possibilities.clear();

  for (int i = 0; i < s.length(); i++) {
    if (s[i] == '?') {
      q_pos.push_back(i);

      possibilities.push_back({});

      if (i + 1 < s.length() and s[i + 1] == '0') {
        possibilities.back() = {2, 1};
      }
      else if (
        (i + 1 == s.length())
        or (i + 2 < s.length() and s[i + 2] == '0')
      ) {
        if (
          (i == 0)
          or (s[i - 1] == '0')
          or (s[i - 1] != '?' and s[i - 1] != '2')
        ) {
          for (int i = 9; i >= 1; i--) {
            possibilities.back().push_back(i);
          }
        }
        else if (s[i - 1] == '2') {
          for (int i = 6; i >= 1; i--) {
            possibilities.back().push_back(i);
          }
        }
        else {
          assert(i > 0 and s[i - 1] == '?');
        }
      }
      else {
        if (s[i + 1] != '?' and s[i + 1] > '6') {
          possibilities.back() = {1};
        }
        else {
          possibilities.back() = {2, 1};
        }
      }
    }
  }

  ans_s = s;
  construct_ans(0, -1);

  int n = s.length();

  dp.assign(n + 1, 0);
  dp[n] = 1;

  for (int i = n - 1; i >= 0; i--) {
    if (ans_s[i] == '0') dp[i] = 0;
    else {
      dp[i] = dp[i + 1];
      if (
        i + 1 < n
        and (10 * (ans_s[i] - '0') + (ans_s[i + 1] - '0')) <= 26
      ) {
        dp[i] = (dp[i] + dp[i + 2]) % mod;
      }
    }
  }

  cout << ans_s << " " << dp[0] << "\n";
}

int main() {
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}