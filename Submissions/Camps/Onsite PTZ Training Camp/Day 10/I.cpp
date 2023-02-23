#include <bits/stdc++.h>
using namespace std;

const int C = 26;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  cin >> s;
  int n = s.length();

  vector<vector<int>> pos(C);
  vector<vector<int>> prv(n, vector<int>(C));
  for (int i = 0; i < n; i++) {
    int c = s[i] - 'a';
    for (int pc = 0; pc < C; pc++) {
      prv[c][pc] = pos[pc].empty() ? -1 : pos[pc].back();
    }
    pos[c].push_back(i);
  }

  function<int(int)> go = [&](int at) {
    return 1;
  };

  int ans = 0;
  for (int i = n - 1; i >= 0; ) {
    int cnt = go(i);
    i = i - cnt;
  }

  cout << ans << "\n";

  return 0;
}