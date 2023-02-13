#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 22;

int main() {
  int n;
  cin >> n;
  ll nn = 1ll << n;

  int x;
  for (x = 0; ; x++) {
    ll x2 = 1ll << x;
    ll x22 = 1ll << x2;
    if (x2 * x22 > nn) break;
  }

  x--;
  ll x2 = 1ll << x;
  ll x22 = 1ll << x2;
  string ans;

  for (ll num = 0; num < x22; num++) {
    string str = bitset<N>(num).to_string();
    str = str.substr(N - x2);
    ans += str;
  }

  x++;
  x2 = 1ll << x;
  x22 = 1ll << x2;
  map<ll, int> mp;
  ll num_at = 0;

  for (int at = 0; at < nn; at += x2) {
    if (at >= ans.length()) {
      while (mp[num_at]) num_at++;
      string str = bitset<N>(num_at).to_string();
      str = str.substr(N - x2);
      ans += str;
    }

    ll num = bitset<N>(ans.substr(at, x2)).to_ullong();
    mp[num] = 1;
  }

  cout << ans << endl;

  return 0;
}