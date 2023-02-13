#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

int n;
string s;
long long ans = 1;

string lex_tree(int at, int level) {
  if (level == 0) return string(1, s[at - 1]);

  string ret;
  ret += s[at - 1];

  string sl = lex_tree(at << 1, level - 1);
  string sr = lex_tree(at << 1 | 1, level - 1);

  if (sr < sl) swap(sl, sr);
  ret += sl;
  ret += sr;

  if (sl != sr) (ans *= 2) %= MOD;
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  cin >> s;

  lex_tree(1, n - 1);

  cout << ans << "\n";

  return 0;
}