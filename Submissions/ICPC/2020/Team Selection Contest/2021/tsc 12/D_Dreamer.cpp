#include <bits/stdc++.h>
using namespace std;

tuple<int, int, int> parse(vector<int> date) {}

int main() {
  int t;
  cin >> t;

  while (t--) {
    vector<int> digs;
    for (int i = 0; i < 3; i++) {
      string s;
      cin >> s;
      for (char c : s) { digs.push_back(c - '0'); }
    }

    sort(digs.begin(), digs.end());
    vector<vector<int>> valid;

    do {
      int day = 0, month = 0, year = 0;
      for (int at = 0, p10 = 1; at < 2; at++, p10 *= 10) {
        day += digs[at] * p10;
      }
      for (int at = 2, p10 = 1; at < 4; at++, p10 *= 10) {
        month += digs[at] * p10;
      }
      for (int at = 4, p10 = 1; at < 8; at++, p10 *= 10) {
        year += digs[at] * p10;
      }

      if (check(digs)) valid.push_back(digs);
    } while (next_permutation(digs.begin(), digs.end()));

    sort(valid.begin(), valid.end(), [](auto &date1, auto &date2) {

    })
  }

  return 0;
}
