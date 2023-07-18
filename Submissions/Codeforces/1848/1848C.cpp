#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void move(ll &a, ll &b) {
  ll prv_a = a, prv_b = b;
  a = prv_b;
  b = abs(prv_a - prv_b);
}

ll required_moves(ll &a, ll &b) {
  ll moves = 0;
  while (a != 0) {
    ll m = b / (2 * a);
    moves += m * 3;
    b -= (2 * a) * m;
    move(a, b);
    moves++;
  }
  return moves;
}

void test_case() {
  int n;
  cin >> n;

  vector<ll> a(n), b(n);
  for (ll &i : a) cin >> i;
  for (ll &i : b) cin >> i;

  int rem = -1;
  for (int i = 0; i < n; i++) {
    int cur_rem = required_moves(a[i], b[i]) % 3;
    assert(a[i] == 0);
    if (b[i] == 0) continue;
    if (rem != -1 and rem != cur_rem) {
      cout << "NO\n";
      return;
    }
    rem = cur_rem;
  }
  cout << "YES\n";
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