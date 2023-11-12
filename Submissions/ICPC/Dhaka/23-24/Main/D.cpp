#include <bits/stdc++.h>

using namespace std;

int main() {
  double inp;
  while (scanf("%lf", &inp) and inp > 0) {
    long double c = inp, ans = sqrtl(c * c * c / 2) / 12;
    printf("%0.4f\n", (double) ans);
  }
  return 0;
}