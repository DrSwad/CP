#include <bits/stdc++.h>
using namespace std;

typedef double ld;
const int N = 1e5 + 5;
const ld PI = acos(-1);

ld dp[N];

ld theta(int n) {
  return PI * (n - 2) / n;
}

void init() {
  dp[3] = 1;
  for (int n = 4; n < N; n++) {
    ld A = theta(n);
    ld B = (theta(n) - theta(n - 1)) / 2;
    ld C = PI - A - B;
    dp[n] = dp[n - 1] * sin(C) / sin(A);
  }
}

ld area(int n, ld side) {
  ld O = PI - theta(n);
  ld side1 = sqrt(1 + 1 - 2 * cos(O));
  ld radius = side / side1;
  return radius * radius * sin(O) / 2;
}

void test_case() {
  int n, s;
  cin >> n >> s;
  ld side = dp[n] * s;
  cout << area(n, side) * n << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  init();

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}