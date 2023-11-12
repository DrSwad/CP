#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
vector<int> mods{int(1e9) + 7, int(1e9) + 9, int(1e9) + 21, int(1e9) + 33, int(1e9) + 87};

int add(int a, int b, int mod) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b, int mod) {
  return 1ll * a * b % mod;
}

int binExp(int a, int e, int m) {
  if (e == -1) e = m - 2;
  int ret = 1;
  while (e) {
    if (e & 1) ret = mul(ret, a, m);
    a = mul(a, a, m), e >>= 1;
  }
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int a, b, c;
  cin >> a >> b >> c;

  bool okay = true;

  for (int mod : mods) {
    if (binExp(a, binExp(b, c, mod - 1), mod) != binExp(a, mul(b, c, mod - 1), mod)) {
      okay = false;
    }
  }

  if (okay) cout << "What an excellent example!\n";
  else cout << "Oh look, a squirrel!\n";

  return 0;
}