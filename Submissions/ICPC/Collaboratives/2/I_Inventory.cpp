#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
#pragma GCC target( \
    "fma,sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#pragma GCC optimize("unroll-loops")

const int MAGIC = 30;
const double eps = 1e-6;

double getRatio(int a, int b) {
  double l = eps, r = 1 - eps;
  while (r - l > eps) {
    double m1 = l + (r - l) / 3;
    double m2 = r - (r - l) / 3;
    double f1 = a / m1 + b / (1 - m1);
    double f2 = a / m2 + b / (1 - m2);
    if (f1 > f2) l = m1;
    else
      r = m2;
  }
  return (1 - l) / l;
}

int main() {
  int t;
  cin >> t;

  for (int i = 1; i <= 10; i++) {
    int a = 1, b = i;
    double r = getRatio(a, b);
    debug() << name(a) name(b) name(r) name(a);
  }

  /* for (int cs = 1; cs <= t; cs++) {
    int n, v;
    scanf("%d %d", &n, &v);

    vector<int> a(n);
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    vector<double> ratios(n);
    ratios[0] = 1;
    double ratioSum = 1;

    for (int i = 1; i < n; i++) {
      ratios[i] = getRatio(a[i - 1], a[i]);
      ratioSum += ratios[i];
    }

    double curr = v / ratioSum;
    double ans = a[0] / curr;

    for (int i = 1; i < n; i++) {
      curr *= ratios[i];
      ans += a[i] / curr;
    }

    printf("Case %d: %.7lf\n", cs, ans);
  } */

  return 0;
}
