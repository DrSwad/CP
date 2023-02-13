#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int a, b, c, d;
  cin >> a >> b >> c >> d;

  int tak = a * 60 * 60 + b * 60;
  int aok = c * 60 * 60 + d * 60 + 1;

  cout << (tak <= aok ? "Takahashi" : "Aoki") << "\n";

  return 0;
}