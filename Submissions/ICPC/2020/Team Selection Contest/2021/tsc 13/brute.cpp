#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll solve(int n, int pattern, int patLen) {
  ll ans = 0;
  for (int mask = 0; mask < 1 << n; mask++) {
    bool flag = false;
    for (int i = 0; i + patLen <= n; i++) {
      int _pattern = pattern << i;
      if ((mask & _pattern) == _pattern) { flag = true; }
    }
    ans += flag;
  }
  return ans;
}

int main() {
  int n;
  cin >> n;

  string P;
  cin >> P;
  int mask = 0;
  for (int i = 0; i < P.length(); i++) {
    if (P[i] == '1') { mask |= 1 << i; }
  }

  cout << solve(n, mask, P.length()) << endl;

  return 0;
}