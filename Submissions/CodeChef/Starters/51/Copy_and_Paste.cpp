#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n, m;
  cin >> n >> m;

  string s;
  cin >> s;

  if (count(s.begin(), s.end(), '0') == n) {
    cout << (ll)n * m << "\n";
    return;
  }

  if (m % 2 == 0) {
    int ans = 1;
    ans += find(s.begin(), s.end(), '1') - s.begin();
    ans += find(s.rbegin(), s.rend(), '1') - s.rbegin();
    cout << ans << "\n";
    return;
  }

  if (count(s.begin(), s.end(), '1') % 2 == 1) {
    cout << "0\n";
    return;
  }

  int rem = count(s.begin(), s.end(), '1') / 2;
  int i;
  for (i = 0; i < n; i++) {
    if (s[i] == '1') {
      rem--;
      if (rem == 0) break;
    }
  }

  int j = find(s.begin() + (i + 1), s.end(), '1') - s.begin();
  cout << j - i << "\n";
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