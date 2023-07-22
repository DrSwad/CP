#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int EXP = 60;

string p[EXP], inv_p[EXP];

void init() {
  cout << EXP + (EXP - 1) << endl;
  p[0] = "R0";
  for (int i = 1; i < EXP; i++) {
    p[i] = "R" + to_string(i);
    cout << "S(" << p[i - 1] << ", " << p[i - 1] << ")" << endl;
  }
  inv_p[0] = "R0";
  for (int i = 1; i < EXP; i++) {
    inv_p[i] = "R" + to_string(EXP + i - 1);
    cout << "P(" << inv_p[i - 1] << ", " << inv_p[i - 1] << ")" << endl;
  }
}

void serial(ll up, ll down);
void parallel(ll up, ll down);

void serial(ll up, ll down) {
  assert(up > 0 and down > 0);
  ll q = up / down;
  ll r = up % down;
  assert(q != 0 or r != 0);
  if (q == 0) parallel(up, down);
  else if (r == 0) {
    int lsb = __builtin_ctzll(q);
    if (q == 1ll << lsb) {
      cout << p[lsb];
    }
    else {
      cout << "S(" << p[lsb] << ", ";
      serial(q - (1ll << lsb), 1);
      cout << ")";
    }
  }
  else {
    cout << "S(";
    serial(q, 1);
    cout << ", ";
    parallel(r, down);
    cout << ")";
  }
}

void parallel(ll val) {
  assert(val > 0);
  int lsb = __builtin_ctzll(val);
  if (val == 1ll << lsb) {
    cout << inv_p[lsb];
  }
  else {
    cout << "P(" << inv_p[lsb] << ", ";
    parallel(val - (1ll << lsb));
    cout << ")";
  }
}

void parallel(ll up, ll down) {
  assert(up > 0 and down > 0);
  assert(up < down);
  swap(up, down);
  ll q = up / down;
  ll r = up % down;
  assert(q != 0);
  if (r == 0) {
    assert(q > 1);
    cout << "P(";
    parallel(1ll);
    cout << ", ";
    parallel(q - 1);
    cout << ")";
  }
  else {
    cout << "P(";
    parallel(q);
    cout << ", ";
    serial(down, r);
    cout << ")";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  int q;
  cin >> q;
  while (q--) {
    ll up, down;
    cin >> up >> down;
    serial(up, down);
    cout << endl;
  }

  ll x = 0, y = 1;
  while (y <= 1e18) {
    debug(x, y);
    ll prv_y = y;
    y = 2 * y + x;
    x = prv_y;
  }

  return 0;
}