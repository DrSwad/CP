#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, a, q;
  cin >> n >> a >> q;

  string s;
  cin >> s;

  int cnt = a;
  if (cnt == n) {
    cout << "YES\n";
    return;
  }
  for (int i = 0; i < q; i++) {
    if (s[i] == '-') cnt--;
    else cnt++;
    assert(cnt >= 0);
    if (cnt == n) {
      cout << "YES\n";
      return;
    }
  }

  if (a + count(s.begin(), s.end(), '+') >= n) cout << "MAYBE\n";
  else cout << "NO\n";
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