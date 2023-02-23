#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int DAY = 24 * 60LL;

int main() {

  int t;
  cin >> t;

  while (t--) {

    ll a, b;
    string s;
    å
      cin >> a >> b >> s;

    int sign = (s[3] == '+') ? 1 : -1;

    ll num = 0LL, div = 1LL; bool decimalPoint = false;
    for (int i = 4; i < s.size(); i++) {
      if (s[i] == '.') {
        decimalPoint = true; continue;
      }

      num *= 10LL;
      num += s[i] - '0';

      if (decimalPoint) div *= 10LL;
    }

    ll add_minutes = sign * num * 60LL - 8LL * 60 * div;
    add_minutes /= div;

    // cout << add_minutes << '\n';

    ll cur_min = 60 * a + b;
    ll ans_min = add_minutes + cur_min;

    ans_min %= DAY;
    ans_min += DAY;
    ans_min %= DAY;

    int ans_a = ans_min / 60, ans_b = ans_min % 60;
    printf("%02d:%02d\n", ans_a, ans_b);
  }

  return 0;
}