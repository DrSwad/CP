#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k;
  cin >> n >> k;

  string s;
  cin >> s;

  int final_color = (s[0] - '0') ^ (k & 1);

  for (int at = 1, prv = 0; at < n and k; at++) {
    if (s[at] != s[prv]) {
      k--;
      prv = at;
    }
  }

  if (k) cout << "-1\n";
  else {
    while (s.back() - '0' != final_color) {
      s.pop_back();
      n--;
    }
    cout << n << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}