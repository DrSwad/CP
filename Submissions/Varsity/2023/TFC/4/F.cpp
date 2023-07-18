#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  function<int(int, int, vector<int>)> min_needed =
    [&](int m, int len, vector<int> indices) {
      int last_used = -1;
      int last_seen = -1;
      int need = 0;
      for (int i : indices) {
        if (i - last_used > m) {
          last_used = last_seen;
          need++;
          if (i - last_used > m) return -1;
        }
        last_seen = i;
      }
      int i = len;
      if (i - last_used > m) {
        last_used = last_seen;
        need++;
        if (i - last_used > m) return -1;
      }
      return need;
    };

  int m;
  cin >> m;

  string s;
  cin >> s;
  int n = s.length();

  string ans;

  for (char c = 'a'; c <= 'z'; c++) {
    bool done = true;
    int need = 0;

    for (int l = 0; l < n; ) {
      if (s[l] < c) {
        l++;
        continue;
      }
      int r = l;
      vector<int> indices;
      while (r < n and s[r] >= c) {
        if (s[r] == c) indices.push_back(r - l);
        r++;
      }
      int len = r - l;

      need += min_needed(m, len, indices);
      if (need == -1) {
        done = false;
        need = count(s.begin(), s.end(), c);
        break;
      }

      l = r;
    }

    while (need--) ans += c;
    if (done) break;
  }

  cout << ans << "\n";

  return 0;
}