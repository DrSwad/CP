#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m, k;
  cin >> n >> m >> k;

  string a, b;
  vector<int> cat(26, -1);
  vector<int> cf(26, 0);
  cin >> a >> b;
  for (char c : a) cat[c - 'a'] = 0, cf[c - 'a']++;
  for (char c : b) cat[c - 'a'] = 1, cf[c - 'a']++;

  int na = a.size(), nb = b.size();
  int ka = k, kb = k;
  string ans;
  while (na and nb) {
    for (int c = 0; c < 26; c++) {
      if (cf[c] == 0) continue;
      if (cat[c] == 0) {
        if (ka == 0) continue;
        kb = k;
        ans += char('a' + c);
        cf[c]--;
        na--;
        ka--;
        break;
      }
      else {
        if (kb == 0) continue;
        ka = k;
        ans += char('a' + c);
        cf[c]--;
        nb--;
        kb--;
        break;
      }
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}