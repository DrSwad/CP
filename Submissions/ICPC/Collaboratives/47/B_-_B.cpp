#include <bits/stdc++.h>
using namespace std;

const int C = 26;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s, t;
  cin >> s >> t;
  int s_len = s.length(), t_len = t.length();

  vector<vector<int>> nxt(C, vector<int>(s_len + 1));
  vector<int> last(C, s_len + 1);

  for (int i = s_len; i >= 0; i--) {
    for (int c = C - 1; c >= 0; c--) {
      nxt[c][i] = last[c];
    }

    if (i) last[s[i - 1] - 'a'] = i;
  }

  int ans = 1;
  for (int ti = 0, si = 0; ti < t_len; ti++) {
    if (nxt[t[ti] - 'a'][si] <= s_len) si = nxt[t[ti] - 'a'][si];
    else ans++, si = nxt[t[ti] - 'a'][0];
  }

  cout << ans << "\n";

  return 0;
}