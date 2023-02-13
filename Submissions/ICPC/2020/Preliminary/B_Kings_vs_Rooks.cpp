#include <bits/stdc++.h>
using namespace std;

struct LagrangeInterpolation {
  int deg, mod;
  vector<int> inv, fx, fy, c;
  LagrangeInterpolation(vector<pair<int, int>> points, int mod) {
    deg = points.size() - 1;
    this->mod = mod;

    inv.resize(mod);
    inv[1] = 1;
    for (int i = 2; i < mod; i++) {
      inv[i] = mul(mod - mod / i, inv[mod % i]);
    }

    for (auto [x, y] : points) {
      fx.emplace_back(x);
      fy.emplace_back(y);
    }

    c.resize(deg + 1);
    for (int i = 0; i <= deg; i++) {
      c[i] = 1;
      for (int j = 0; j <= deg; j++) {
        if (j != i) {
          c[i] = mul(c[i], inv[abs(fx[i] - fx[j])]);
          if (fx[i] < fx[j]) c[i] = mod - c[i];
        }
      }
      c[i] = mul(c[i], fy[i]);
    }
  }
  inline int mul(int a, int b) {
    return (a * 1ll * b) % mod;
  }
  int eval(int x) {
    if (find(fx.begin(), fx.end(), x) != fx.end()) {
      return fy[find(fx.begin(), fx.end(), x) - fx.begin()];
    }

    int prod = 1;
    for (int i = 0; i <= deg; i++) {
      prod = mul(prod, x - fx[i]);
    }
    int ret = 0;
    for (int i = 0; i <= deg; i++) {
      int curr = mul(c[i], mul(prod, inv[abs(x - fx[i])]));
      if (x < fx[i]) curr = mod - curr;
      ret = (ret + curr) % mod;
    }
    return ret;
  }
};

int main() {
  vector<pair<int, int>> points{
    {3, 232},
    {4, 1432},
    {5, 5188},
    {6, 14536},
    {7, 34464},
    {8, 72392},
  };
  const int mod = 7340033;

  LagrangeInterpolation li(points, mod);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    int n;
    scanf("%d", &n);
    printf("Case %d: %d\n", cs, n == 1 or n == 2 ? 0 : li.eval(n));
  }

  return 0;
}