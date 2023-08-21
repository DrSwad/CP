#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int m;
  cin >> m;

  vector<int> d(m);
  for (int &i : d) cin >> i;

  int tot = accumulate(d.begin(), d.end(), 0);
  int need = (tot + 1) / 2;

  int a, b;
  for (a = 1; d[a - 1] < need; a++) need -= d[a - 1];
  b = need;

  cout << a << " " << b << "\n";

  return 0;
}