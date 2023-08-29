#include <bits/stdc++.h>
using namespace std;

bool is_winning(int at, vector<vector<int>> edge_cnt) {
  for (int to = 0; to < 3; to++) {
    if (edge_cnt[at][to]) {
      edge_cnt[at][to]--;
      if (!is_winning(to, edge_cnt)) return true;
      edge_cnt[at][to]++;
    }
  }

  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector edge_cnt(3, vector(3, 0));
  map<char, int> char_id;
  while (n--) {
    string s;
    cin >> s;
    if (char_id.find(s[0]) == char_id.end()) char_id[s[0]] = char_id.size();
    if (char_id.find(s.back()) == char_id.end()) char_id[s.back()] = char_id.size();
    int from = char_id[s[0]];
    int to = char_id[s.back()];
    edge_cnt[from][to]++;
  }

  int ans = 0;
  for (int from = 0; from < 3; from++) {
    for (int to = 0; to < 3; to++) {
      if (edge_cnt[from][to]) {
        edge_cnt[from][to]--;
        ans += !is_winning(to, edge_cnt) * (edge_cnt[from][to] + 1);
        edge_cnt[from][to]++;
      }
    }
  }

  cout << ans << "\n";

  return 0;
}