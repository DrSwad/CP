#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll binExp(ll a, ll e, ll m) {
  if (e == -1) e = m - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % m;
    a = a * a % m, e >>= 1;
  }
  return ret;
}

const int MAX_ORDER = 1e7;
const int MAX_Y = 1000;
int p, q;
int order;
unordered_map<int, int> e2;

int solve(int a, int b, int c, int d) {
  int s = (a + b);
  if (s >= p) s -= p;

  int s2 = (c + d);
  if (s2 >= p) s2 -= p;

  int ans = -1;

  if (s == s2) {
    if (p == 2) ans = a != c;
    else {
      if (a == 0) swap(a, b), swap(c, d);
      int inv_a = binExp(a, -1, p);

      int corner = 1ll * c * inv_a % p;
      if (e2.find(corner) != e2.end()) ans = e2[corner];

      for (int y = 0, yys = s; y < order and y < MAX_Y; y++) {
        int right = yys + c;
        if (right >= p) right -= p;
        right = 1ll * right * inv_a % p;

        if (e2.find(right) != e2.end()) {
          int x = e2[right];
          if (x <= y) x += order;
          ans = ans == -1 ? x : min(ans, x);
        }

        yys <<= 1;
        if (yys >= p) yys -= p;
      }
    }
  }

  return ans;
}

int s, c, d;
int call(int a, int d = 0) {
  if (d >= 20) return 123456789;
  // cout << a << '\n';
  if (a == c) return 0;
  return 1 + min(call((a + a) % p, d + 1), call((a + a - s + p) % p, d + 1));
}
int brute(int a, int b, int c, int d) {
  if ((a + b) % p != (c + d) % p) {
    return -1;
  } else {
    s = a + b;
    int ans = call(a);
    // if(ans >= 10) cout << "-1\n";
    return ans;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> p >> q;

  e2[1] = 0;
  for (int i = 1, v = 1; i <= MAX_ORDER; i++) {
    v <<= 1;
    if (v >= p) v -= p;

    if (v == 1) {
      order = i;
      break;
    }

    e2[v] = i;
  }

  assert(p == 2 or order);

  while (q--) {
    int a, b;
    cin >> a >> b >> c >> d;

    int ans = solve(a, b, c, d);
    // int bans = brute(a, b, c, d);
    // assert(ans == bans);

    cout << ans << "\n";
  }

  return 0;
}