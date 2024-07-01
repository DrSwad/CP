#include <bits/stdc++.h>
using namespace std;

pair<long long, long long> ext_gcd(long long a, long long b) {
  bool swapped = false;
  if (a < b) swap(a, b), swapped = true;
  if (b == 0) return {1, 0};
  int q = a / b;
  auto [x, y] = ext_gcd(b, a % b);
  pair ret{y, x - q * y};
  if (swapped) swap(ret.first, ret.second);
  return ret;
}

// Returns smallest integer x in [0, mod) s.t. a * x = r (mod mod).
// Returns -1 if no such x exists.
int get_smallest_solution(int a, int r, int mod, bool positive) {
  int g = gcd(a, mod);
  if (r % g != 0) return -1;
  a /= g, mod /= g, r /= g;

  auto [x, y] = ext_gcd(a, mod);
  x = (x % mod * r % mod + mod) % mod;

  if (positive and x == 0) x += mod;

  return x;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int b, d;
  string a;
  cin >> b >> d >> a;

  int max_digits = a.length();

  int trailing_digits = 0;
  int pow_10 = 1;
  int trailing_rem = 0;
  int trailing_flag = 0;
  int ans = 0;

  while (++trailing_digits <= max_digits) {
    (pow_10 *= 10) %= b;
    ((trailing_rem *= 10) += d) %= b;

    if (d < *(a.end() - trailing_digits) - '0') trailing_flag = -1;
    else if (d > *(a.end() - trailing_digits) - '0') trailing_flag = 1;

    int leading_value = get_smallest_solution(pow_10, (b - trailing_rem) % b, b, d == 0);
    if (leading_value < 0) continue;

    string leading_str = leading_value == 0 ? "" : to_string(leading_value);

    if (a.length() > trailing_digits + leading_str.length()
        or (a.length() == trailing_digits + leading_str.length()
            and (a.substr(0, leading_str.length()) > leading_str
                 or (a.substr(0, leading_str.length()) == leading_str
                     and trailing_flag <= 0)))
    ) {
      ans = trailing_digits;
    }
  }

  cout << ans << "\n";

  return 0;
}