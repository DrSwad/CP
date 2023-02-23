#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll stringToInt(string s) {
  ll ret = 0;
  for (int i = 0; i < s.size(); i++) {
    ret *= 10LL;
    ret += s[i] - '0';
  }
  return ret;
}

int main() {

  string old;
  cin >> old;

  vector<char> digits;
  for (char c = '0'; c <= '9'; c++) {
    digits.push_back(c);
  }

  int n = old.size();
  ll pow10 = 1LL;
  for (int i = 0; i < n; i++) {
    pow10 *= 10LL;
  }

  ll old_num = stringToInt(old);

  string ans;
  ll score = 0LL;
  do {
    string news = "";
    for (int i = 0; i < n; i++) {
      news += digits[i];
    }
    ll new_num = stringToInt(news);

    ll cur_score = min(abs(old_num - new_num), pow10 - abs(old_num - new_num));

    if (score < cur_score) {
      // cout << cur_score << ' ' << news << endl;
      score = cur_score;
      ans = news;
    }

  } while (next_permutation(digits.begin(), digits.end()));

  cout << ans << '\n';
  // cout << ans << ' ' << score << '\n';

  return 0;
}
